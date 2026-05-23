/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>  // printf/sprintf需要
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 原有宏定义保留
#define INMP441_WS_PIN    GPIO_PIN_4
#define INMP441_WS_PORT   GPIOA
#define HC_SR501_PIN      GPIO_PIN_0
#define HC_SR501_PORT     GPIOA

// 采样参数（优化后）
#define SAMPLE_RATE       16000
#define INMP441_BIT_DEPTH 16
#define AUDIO_BUF_SIZE    1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// 原有全局变量保留
uint8_t human_detected = 0;    // 人体检测状态（0：无人，1：有人）
int16_t audio_data = 0;        // INMP441音频采样值
uint8_t uart_tx_buf[8] = {0};  // 串口发送缓冲区

// 新增：音频缓冲区（对应ESP32的循环缓冲区）
AudioBuffer audio_buf = {0};
// 新增：WS引脚状态（由定时器中断控制）
uint8_t ws_state = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// 原有函数声明保留
uint8_t HC_SR501_Read_State(void);       // 读取人体红外状态
int16_t INMP441_Read_Audio(void);        // 读取INMP441音频数据
void USART2_Send_Data(uint8_t *buf, uint16_t len); // 串口发送数据
// 移除原WS生成函数：INMP441_WS_Generate(void);
// 新增函数声明
uint16_t INMP441_ReadBuf(int16_t *dest, uint16_t len); // 读取音频缓冲区
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// 原有HC-SR501读取函数保留
uint8_t HC_SR501_Read_State(void)
{
  uint8_t state1 = HAL_GPIO_ReadPin(HC_SR501_PORT, HC_SR501_PIN);
  HAL_Delay(10); // 消抖10ms
  uint8_t state2 = HAL_GPIO_ReadPin(HC_SR501_PORT, HC_SR501_PIN);
  return (state1 == state2) ? state1 : 0;
}

// 原有SPI读取函数保留（优化超时时间）
static uint8_t SPI_Read_Byte(void)
{
  uint8_t rx_data = 0;
  HAL_SPI_Receive(&hspi1, &rx_data, 1, 10); // 超时从100ms缩短为10ms，提升响应
  return rx_data;
}

// 新增：定时器2中断回调（生成精确16kHz WS信号，替代原HAL_GetTick模拟）
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    // 翻转WS引脚状态
    ws_state = !ws_state;
    HAL_GPIO_WritePin(INMP441_WS_PORT, INMP441_WS_PIN, ws_state);

    // WS高电平时读取音频采样（INMP441左声道数据）
    if (ws_state == GPIO_PIN_SET) {
      audio_data = INMP441_Read_Audio();
      // 将采样值写入循环缓冲区（对应ESP32的缓存逻辑）
      uint16_t next_write_idx = (audio_buf.write_idx + 1) % AUDIO_BUF_SIZE;
      if (next_write_idx != audio_buf.read_idx) { // 缓冲区未满
        audio_buf.buf[audio_buf.write_idx] = audio_data;
        audio_buf.write_idx = next_write_idx;
      }
    }
  }
}

// 优化INMP441音频读取函数（适配定时器WS信号）
int16_t INMP441_Read_Audio(void)
{
  uint8_t data_h = 0, data_l = 0;
  int16_t audio = 0;

  // 仅在WS高电平时读取（由定时器中断触发）
  if (ws_state == GPIO_PIN_SET)
  {
    data_h = SPI_Read_Byte(); // 高8位
    data_l = SPI_Read_Byte(); // 低8位
    // 修正INMP441数据格式（高位在前，符号位处理）
    audio = (int16_t)((data_h << 8) | data_l);
    // 对齐ESP32的数据范围（可选）
    audio = audio >> 1; // INMP441是24位数据，取高16位
  }
  return audio;
}

// 新增：读取音频缓冲区（对应ESP32的i2s_read逻辑）
uint16_t INMP441_ReadBuf(int16_t *dest, uint16_t len)
{
  uint16_t read_len = 0;
  while (read_len < len && audio_buf.read_idx != audio_buf.write_idx) {
    dest[read_len++] = audio_buf.buf[audio_buf.read_idx];
    audio_buf.read_idx = (audio_buf.read_idx + 1) % AUDIO_BUF_SIZE;
  }
  return read_len;
}

// 原有USART2发送函数保留
void USART2_Send_Data(uint8_t *buf, uint16_t len)
{
  HAL_UART_Transmit(&huart2, buf, len, 100);
}

// 原有串口重定向保留
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 100);
  return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  // 原有初始化提示保留
  uint8_t init_msg[] = "STM32F103 Init OK\r\n";
  USART2_Send_Data(init_msg, strlen((char*)init_msg));

  // 新增：启动TIM2中断（生成16kHz WS信号）
  HAL_TIM_Base_Start_IT(&htim2);
  // 初始化WS引脚为低电平
  HAL_GPIO_WritePin(INMP441_WS_PORT, INMP441_WS_PIN, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 1. 读取人体红外状态（原有逻辑保留）
    human_detected = HC_SR501_Read_State();

    // 2. 从音频缓冲区读取数据（替代原直接读取，对应ESP32的缓存逻辑）
    int16_t buf[32] = {0};
    uint16_t read_len = INMP441_ReadBuf(buf, 32);
    if (read_len > 0) {
      audio_data = buf[0]; // 取第一个采样值用于原有帧格式发送
    }

    // 3. 原有帧格式发送逻辑保留（发给F407）
    uart_tx_buf[0] = 0xAA;          // 帧头
    uart_tx_buf[1] = human_detected;// 人体状态
    uart_tx_buf[2] = (audio_data >> 8) & 0xFF; // 音频高8位
    uart_tx_buf[3] = audio_data & 0xFF;        // 音频低8位
    uart_tx_buf[4] = 0x55;          // 帧尾
    USART2_Send_Data(uart_tx_buf, 5);

    // 4. 原有F407指令接收逻辑保留
    uint8_t uart_rx_buf[1] = {0};
    if (HAL_UART_Receive(&huart2, uart_rx_buf, 1, 10) == HAL_OK)
    {
      if (uart_rx_buf[0] == 0x01)
      {
        // 优化：读取缓冲区并批量发送（对应ESP32的实时输出）
        char msg[128] = {0};
        uint16_t len = snprintf(msg, 128, "Human:%d, AudioBufLen:%d, FirstSample:%d\r\n",
                                human_detected, read_len, audio_data);
        USART2_Send_Data((uint8_t*)msg, len);
      }
    }

    HAL_Delay(10); // 主循环延时，降低CPU占用
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

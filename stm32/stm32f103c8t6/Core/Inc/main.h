/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>  // 引入标准整数类型定义（uint8_t/int16_t等）
#include <stddef.h>  // 可选，补充size_t等类型
#include <string.h>  // 新增：memset/strlen等函数
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
// 新增：音频缓冲区结构体（对应ESP32的循环缓冲区）
typedef struct {
    int16_t buf[1024];  // 16位音频数据缓冲区（大小与ESP32示例一致）
    uint16_t write_idx; // 缓冲区写指针
    uint16_t read_idx;  // 缓冲区读指针
} AudioBuffer;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
// 新增：定时器参数（16kHz WS信号）
#define TIM2_PRESCALER     63    // 预分频器
#define TIM2_AUTORELOAD    62    // 自动重装值（64MHz/(63+1)/(62+1)≈16kHz）
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
// 新增：定时器中断回调声明
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
// 新增：音频缓冲区读取函数声明
uint16_t INMP441_ReadBuf(int16_t *dest, uint16_t len);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
// 原有宏定义保留
#define INMP441_WS_PIN    GPIO_PIN_4
#define INMP441_WS_PORT   GPIOA
#define HC_SR501_PIN      GPIO_PIN_0
#define HC_SR501_PORT     GPIOA

// 采样参数（优化后）
#define SAMPLE_RATE       16000
#define INMP441_BIT_DEPTH 16
#define AUDIO_BUF_SIZE    1024  // 新增：音频缓冲区大小
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

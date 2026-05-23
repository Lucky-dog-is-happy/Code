#include "esp8266.h"
#include <string.h>
#include <stdio.h>

static ESP8266_State_t esp_state = ESP_STATE_INIT;
static uint32_t last_action_time = 0;
static uint8_t retry_count = 0;
static uint8_t wifi_connected = 0;

#define RESP_BUFFER_SIZE 512
static char response_buffer[RESP_BUFFER_SIZE];
static uint16_t resp_index = 0;

#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASSWORD "Your_WiFi_Password"
#define TCP_SERVER_IP "192.168.1.100"
#define TCP_SERVER_PORT "8080"

void ESP8266_Init(void)
{
    esp_state = ESP_STATE_INIT;
    last_action_time = HAL_GetTick();
    retry_count = 0;
    wifi_connected = 0;
    memset(response_buffer, 0, RESP_BUFFER_SIZE);
}

void ESP8266_Process(void)
{
    uint32_t current_time = HAL_GetTick();
    if (current_time - last_action_time < 500) return;

    switch (esp_state) {
        case ESP_STATE_INIT:
            printf("ESP8266: Initializing...\r\n");
            if (ESP8266_SendCommand("AT")) {
                esp_state = ESP_STATE_TEST;
                last_action_time = current_time;
            }
            break;
        case ESP_STATE_TEST:
            printf("ESP8266: Testing module...\r\n");
            if (ESP8266_WaitResponse("OK", 1000)) {
                esp_state = ESP_STATE_WIFI_MODE;
                retry_count = 0;
            } else {
                retry_count++;
                if (retry_count > 3) esp_state = ESP_STATE_ERROR;
            }
            last_action_time = current_time;
            break;
        case ESP_STATE_WIFI_MODE:
            if (ESP8266_SendCommand("AT+CWMODE=1")) {
                if (ESP8266_WaitResponse("OK", 2000)) {
                    esp_state = ESP_STATE_WIFI_CONNECT;
                }
            }
            last_action_time = current_time;
            break;
        case ESP_STATE_WIFI_CONNECT: {
            char wifi_cmd[128];
            snprintf(wifi_cmd, sizeof(wifi_cmd), "AT+CWJAP=\"%s\",\"%s\"", WIFI_SSID, WIFI_PASSWORD);
            if (ESP8266_SendCommand(wifi_cmd)) {
                if (ESP8266_WaitResponse("WIFI GOT IP", 15000)) {
                    wifi_connected = 1;
                    esp_state = ESP_STATE_TCP_CONNECT;
                    retry_count = 0;
                } else {
                    retry_count++;
                    if (retry_count > 3) esp_state = ESP_STATE_ERROR;
                }
            }
            last_action_time = current_time;
            break;
        }
        case ESP_STATE_TCP_CONNECT: {
            if (wifi_connected) {
                char tcp_cmd[128];
                snprintf(tcp_cmd, sizeof(tcp_cmd), "AT+CIPSTART=\"TCP\",\"%s\",%s", TCP_SERVER_IP, TCP_SERVER_PORT);
                if (ESP8266_SendCommand(tcp_cmd)) {
                    if (ESP8266_WaitResponse("CONNECT", 10000)) {
                        esp_state = ESP_STATE_TRANSPARENT;
                    }
                }
            }
            last_action_time = current_time;
            break;
        }
        case ESP_STATE_TRANSPARENT:
            if (ESP8266_SendCommand("AT+CIPMODE=1")) {
                if (ESP8266_WaitResponse("OK", 1000)) {
                    if (ESP8266_SendCommand("AT+CIPSEND")) {
                        if (ESP8266_WaitResponse(">", 1000)) {
                            esp_state = ESP_STATE_READY;
                            ESP8266_SendData((uint8_t*)"ESP8266 Ready\r\n", 15);
                        }
                    }
                }
            }
            last_action_time = current_time;
            break;
        case ESP_STATE_READY:
            if (current_time - last_action_time > 5000) {
                ESP8266_SendData((uint8_t*)"Heartbeat\r\n", 11);
                last_action_time = current_time;
            }
            break;
        case ESP_STATE_ERROR:
            // handle error
            break;
    }

    ESP8266_UpdateLEDs();
}

void ESP8266_UpdateLEDs(void)
{
    static uint32_t last_blink = 0;
    uint32_t current_time = HAL_GetTick();
    switch (esp_state) {
        case ESP_STATE_READY:
            break;
        case ESP_STATE_ERROR:
            if (current_time - last_blink > 200) {
                last_blink = current_time;
            }
            break;
        default:
            if (current_time - last_blink > 500) {
                last_blink = current_time;
            }
            break;
    }
}

uint8_t ESP8266_SendCommand(const char* cmd)
{
    char cmd_buffer[256];
    uint16_t len = snprintf(cmd_buffer, sizeof(cmd_buffer), "%s\r\n", cmd);
    HAL_UART_Transmit(&huart3, (uint8_t*)cmd_buffer, len, 1000);
    return 1;
}

uint8_t ESP8266_WaitResponse(const char* expected, uint32_t timeout)
{
    uint32_t start_time = HAL_GetTick();
    uint8_t ch;
    resp_index = 0;
    memset(response_buffer, 0, RESP_BUFFER_SIZE);
    while ((HAL_GetTick() - start_time) < timeout) {
        if (HAL_UART_Receive(&huart3, &ch, 1, 10) == HAL_OK) {
            if (resp_index < RESP_BUFFER_SIZE - 1) {
                response_buffer[resp_index++] = ch;
                if (strstr(response_buffer, expected) != NULL) return 1;
                if (strstr(response_buffer, "ERROR") != NULL || strstr(response_buffer, "FAIL") != NULL) return 0;
            }
        }
    }
    return 0;
}

uint8_t ESP8266_SendData(uint8_t* data, uint16_t length)
{
    if (esp_state != ESP_STATE_READY) return 0;
    if (HAL_UART_Transmit(&huart3, data, length, 1000) == HAL_OK) return 1;
    return 0;
}

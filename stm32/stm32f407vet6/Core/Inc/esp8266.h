/* USER CODE BEGIN Header */
/*
 * esp8266.h
 */
#ifndef __ESP8266_H
#define __ESP8266_H

#include "main.h"

typedef enum {
    ESP_STATE_INIT,
    ESP_STATE_TEST,
    ESP_STATE_WIFI_MODE,
    ESP_STATE_WIFI_CONNECT,
    ESP_STATE_TCP_CONNECT,
    ESP_STATE_TRANSPARENT,
    ESP_STATE_READY,
    ESP_STATE_ERROR
} ESP8266_State_t;

void ESP8266_Init(void);
void ESP8266_Process(void);
void ESP8266_UpdateLEDs(void);
uint8_t ESP8266_SendCommand(const char* cmd);
uint8_t ESP8266_WaitResponse(const char* expected, uint32_t timeout);
uint8_t ESP8266_SendData(uint8_t* data, uint16_t length);

#endif /* __ESP8266_H */

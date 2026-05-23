#include "k210_protocol.h"
#include "esp8266.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

typedef enum {
    K210_STATE_WAIT_HEADER,
    K210_STATE_READ_LEN_HI,
    K210_STATE_READ_LEN_LO,
    K210_STATE_READ_TYPE,
    K210_STATE_READ_PAYLOAD,
    K210_STATE_READ_CHECKSUM,
    K210_STATE_VALIDATE_TAIL
} K210_ParseState_t;

static K210_ParseState_t parse_state = K210_STATE_WAIT_HEADER;
static uint8_t frame_buffer[1024];
static uint16_t frame_index = 0;
static uint16_t payload_length = 0;
static uint8_t expected_length = 0;
static uint8_t calculated_checksum = 0;

uint8_t K210_ParseByte(uint8_t byte, uint8_t* complete_frame, uint16_t* frame_len)
{
    static uint8_t checksum = 0;

    switch (parse_state) {
        case K210_STATE_WAIT_HEADER:
            if (byte == 0xAA) {
                frame_index = 0;
                frame_buffer[frame_index++] = byte;
                checksum = 0xAA;
                parse_state = K210_STATE_READ_LEN_HI;
            }
            break;
        case K210_STATE_READ_LEN_HI:
            frame_buffer[frame_index++] = byte;
            checksum ^= byte;
            payload_length = byte << 8;
            parse_state = K210_STATE_READ_LEN_LO;
            break;
        case K210_STATE_READ_LEN_LO:
            frame_buffer[frame_index++] = byte;
            checksum ^= byte;
            payload_length |= byte;
            if (payload_length > 1024) {
                parse_state = K210_STATE_WAIT_HEADER;
                return 0;
            }
            expected_length = 6 + payload_length;
            parse_state = K210_STATE_READ_TYPE;
            break;
        case K210_STATE_READ_TYPE:
            frame_buffer[frame_index++] = byte;
            checksum ^= byte;
            parse_state = K210_STATE_READ_PAYLOAD;
            break;
        case K210_STATE_READ_PAYLOAD:
            frame_buffer[frame_index++] = byte;
            checksum ^= byte;
            if (frame_index >= (4 + payload_length)) {
                parse_state = K210_STATE_READ_CHECKSUM;
            }
            break;
        case K210_STATE_READ_CHECKSUM:
            frame_buffer[frame_index++] = byte;
            calculated_checksum = checksum;
            parse_state = K210_STATE_VALIDATE_TAIL;
            break;
        case K210_STATE_VALIDATE_TAIL:
            frame_buffer[frame_index++] = byte;
            if (byte == 0x55 && calculated_checksum == frame_buffer[frame_index - 2]) {
                memcpy(complete_frame, frame_buffer, frame_index);
                *frame_len = frame_index;
                parse_state = K210_STATE_WAIT_HEADER;
                return 1;
            } else {
                parse_state = K210_STATE_WAIT_HEADER;
            }
            break;
    }
    return 0;
}

void K210_ProcessFrame(uint8_t* frame, uint16_t length)
{
    if (length < 6) return;
    uint8_t msg_type = frame[3];
    switch (msg_type) {
        case K210_MSG_WAKEUP:
            printf("K210: Wakeup command\r\n");
            Beeper_Beep(50, 1);
            break;
        case K210_MSG_SLEEP:
            printf("K210: Sleep command\r\n");
            Beeper_Beep(50, 2);
            break;
        case K210_MSG_AI_RESULT:
            if (length >= 6 + 14) {
                K210_AI_Result_t ai_result;
                uint8_t* payload = &frame[4];
                ai_result.detection_type = payload[0];
                ai_result.confidence = payload[1];
                ai_result.x1 = payload[2] | (payload[3] << 8);
                ai_result.y1 = payload[4] | (payload[5] << 8);
                ai_result.x2 = payload[6] | (payload[7] << 8);
                ai_result.y2 = payload[8] | (payload[9] << 8);
                ai_result.timestamp = payload[10] | (payload[11] << 8) | (payload[12] << 16) | (payload[13] << 24);
                printf("AI Result: type=%d, conf=%d, x1=%d, y1=%d, x2=%d, y2=%d, ts=%lu\r\n",
                       ai_result.detection_type, ai_result.confidence,
                       ai_result.x1, ai_result.y1, ai_result.x2, ai_result.y2,
                       ai_result.timestamp);
                char ai_msg[128];
                snprintf(ai_msg, sizeof(ai_msg), "AI: type=%d conf=%d%% area=[%d,%d,%d,%d]\r\n",
                         ai_result.detection_type, ai_result.confidence,
                         ai_result.x1, ai_result.y1, ai_result.x2, ai_result.y2);
                ESP8266_SendData((uint8_t*)ai_msg, strlen(ai_msg));
            }
            break;
    }
}

void K210_SendWakeup(void)
{
    uint8_t wakeup_frame[] = {0xAA, 0x00, 0x00, K210_MSG_WAKEUP, 0xBA, 0x55};
    HAL_UART_Transmit(&huart2, wakeup_frame, sizeof(wakeup_frame), 100);
}

void K210_SendSleep(void)
{
    uint8_t sleep_frame[] = {0xAA, 0x00, 0x00, K210_MSG_SLEEP, 0xBB, 0x55};
    HAL_UART_Transmit(&huart2, sleep_frame, sizeof(sleep_frame), 100);
}

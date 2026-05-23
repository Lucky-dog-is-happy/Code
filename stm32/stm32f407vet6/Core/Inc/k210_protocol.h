#ifndef __K210_PROTOCOL_H
#define __K210_PROTOCOL_H

#include "main.h"

#define K210_MSG_WAKEUP     0x10
#define K210_MSG_SLEEP      0x11
#define K210_MSG_AI_RESULT  0x32

typedef struct {
    uint8_t detection_type;
    uint8_t confidence;
    uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;
    uint32_t timestamp;
} K210_AI_Result_t;

uint8_t K210_ParseByte(uint8_t byte, uint8_t* frame_buffer, uint16_t* frame_len);
void K210_ProcessFrame(uint8_t* frame, uint16_t length);
void K210_SendWakeup(void);
void K210_SendSleep(void);

#endif /* __K210_PROTOCOL_H */

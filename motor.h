#ifndef MOTOR_H
#define MOTOR_H

#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"

typedef struct{
    float speed; // pos: forward neg: backward
    uint32_t duty;
    uint8_t stop; // 0: normal 1: break
} Motor_t;

Motor_t left_wheel, right_wheel;

void Motor_Init();
void Motor_Handler();

#endif

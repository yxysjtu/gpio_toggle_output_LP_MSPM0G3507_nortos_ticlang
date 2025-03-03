#include "motor.h"

void Motor_Init(){
    DL_TimerG_startCounter(PWM_1_INST);
    DL_TimerG_startCounter(PWM_2_INST);
    DL_TimerG_setCaptureCompareValue(PWM_1_INST, 0, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_1_INST, 0, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_2_INST, 0, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_2_INST, 0, DL_TIMER_CC_1_INDEX);
}

void Motor_Handler(){
    if (left_wheel.stop){
        DL_TimerG_setCaptureCompareValue(PWM_1_INST, 0, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_1_INST, 0, DL_TIMER_CC_1_INDEX);
    } else if (left_wheel.speed > 0){
        left_wheel.duty = (uint32_t)(left_wheel.speed * 2000.0f);
        DL_TimerG_setCaptureCompareValue(PWM_1_INST, left_wheel.duty, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_1_INST, 0, DL_TIMER_CC_1_INDEX);
    } else if (left_wheel.speed <= 0){
        left_wheel.duty = (uint32_t)(-left_wheel.speed * 2000.0f);
        DL_TimerG_setCaptureCompareValue(PWM_1_INST, 0, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_1_INST, left_wheel.duty, DL_TIMER_CC_1_INDEX);
    }

    if (right_wheel.stop){
        DL_TimerG_setCaptureCompareValue(PWM_2_INST, 0, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_2_INST, 0, DL_TIMER_CC_1_INDEX);
    } else if (right_wheel.speed > 0){
        right_wheel.duty = (uint32_t)(right_wheel.speed * 2000.0f);
        DL_TimerG_setCaptureCompareValue(PWM_2_INST, 0, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_2_INST, right_wheel.duty, DL_TIMER_CC_1_INDEX);
    } else if (right_wheel.speed <= 0){
        right_wheel.duty = (uint32_t)(-right_wheel.speed * 2000.0f);
        DL_TimerG_setCaptureCompareValue(PWM_2_INST, right_wheel.duty, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_2_INST, 0, DL_TIMER_CC_1_INDEX);
    }
}

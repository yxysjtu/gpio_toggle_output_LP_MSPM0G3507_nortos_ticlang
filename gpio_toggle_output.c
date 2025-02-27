/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

/* This results in approximately 0.5s of delay assuming 32MHz CPU_CLK */
#define DELAY (40000000)


int main(void)
{
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();

    /* Default: LED1 and LED3 ON, LED2 OFF */
    // DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_2_PIN);
    // DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN |
    //                                     GPIO_LEDS_USER_LED_3_PIN |
    //                                     GPIO_LEDS_USER_TEST_PIN);
    for(int i = 0; i < 8; i++){
        delay_cycles(DELAY/8);
        DL_GPIO_togglePins(LED_PORT, LED_LED1_PIN);
    }

    //pwm测试
    // DL_TimerG_setCaptureCompareValue(PWM_1_INST, 2000, DL_TIMER_CC_0_INDEX);
    // DL_TimerG_setCaptureCompareValue(PWM_2_INST, 2000, DL_TIMER_CC_0_INDEX);

    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
   // NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    //NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
     NVIC_EnableIRQ(COMP0_INT_IRQn);
     NVIC_EnableIRQ(COMP1_INT_IRQn);
    //DL_TimerG_startCounter(TIMER_0_INST);
    
    while (1) {
        /*
         * Call togglePins API to flip the current value of LEDs 1-3. This
         * API causes the corresponding HW bits to be flipped by the GPIO HW
         * without need for additional R-M-W cycles by the processor.
         */
        //delay_cycles(DELAY);
        // DL_GPIO_togglePins(GPIO_OUT_PORT, GPIO_OUT_LED1_PIN);
    }
}


unsigned int utick = 0;//滴答定时器中断计数

void SysTick_Handler(void){

    SysTick->CTRL &= ~(1 << 16); /*清除滴答定时器中断标志位*/
    utick++;//滴答定时器中断计数

    if(utick % 500 == 0){
        DL_GPIO_togglePins(LED_PORT, LED_LED1_PIN);

    }
}

//ADC采集逻辑
//对于40k的正弦波，用400k连续采(timer trig)，采集一次触发中断
//脉冲的检测方法：
//0. 阈值vth，低于这个阈值的小脉冲忽略（状态0），决定通信的范围。初始化pulse_t1=0
//1. 按照通道0触发，过了这个阈值之后进入状态1，初始为时间adc_t=0，记录脉冲的最高值以及对应的时间戳pulse_t0
//2. 下降过了vth后进入状态2，之前的脉冲间隔=pulse_t0+pulse_t1，判断脉冲间隔是否合理，更新数据序号以及更新数据；
//   adc_t继续增长，直到上升过了vth，脉冲间隔更新pulse_t1=adc_t-pulse_t0，然后回到状态1

uint32_t adc_t = 0;
uint32_t pulse_t0 = 0, pulse_t1 = 0;
int state = 0;
int16_t vth = 100, vmid = 2000;
int16_t adc0_0 = 0, adc0_1 = 0;

// void ADC12_0_INST_IRQHandler(void)
// {
//     switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
//         case DL_ADC12_IIDX_MEM1_RESULT_LOADED:
//         {
//             adc0_0 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
//             adc0_1 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_1);
//             DL_GPIO_togglePins(TEST_PORT, TEST_PIN_0_PIN);
//         }
//             break;
//         default:
//             break;
//     }
    
// }

// void TIMER_0_INST_IRQHandler(void)
// {
//     switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
//         case DL_TIMER_IIDX_ZERO:
//             //DL_GPIO_togglePins(TEST_PORT, TEST_PIN_0_PIN);
//             break;
//         default:
//             break;
//     }
// }

// void TIMER_1_INST_IRQHandler(void)
// {
//     switch (DL_TimerG_getPendingInterrupt(TIMER_1_INST)) {
//         case DL_TIMER_IIDX_ZERO:
//             //NVIC_EnableIRQ(COMP0_INT_IRQn);
            
//             //DL_GPIO_togglePins(TEST_PORT, TEST_PIN_0_PIN);
//             break;
//         default:
//             break;
//     }
// }

uint32_t comp_t0 = 0, comp_t1 = 0;

void GROUP1_IRQHandler(void)
{
    switch (DL_COMP_getPendingInterrupt(COMP_0_INST)) {
        case DL_COMP_IIDX_OUTPUT_EDGE:{
            if(utick - comp_t0 >= 4){
                comp_t0 = utick;
                DL_GPIO_togglePins(TEST_PORT, TEST_PIN_0_PIN);
            }

        }break;
        case DL_COMP_IIDX_OUTPUT_EDGE_INV:
            break;
        default:
            break;
    }
    switch (DL_COMP_getPendingInterrupt(COMP_1_INST)) {
        case DL_COMP_IIDX_OUTPUT_EDGE:{
            if(utick - comp_t1 >= 4){
                comp_t1 = utick;
                DL_GPIO_togglePins(TEST_PORT, TEST_PIN_1_PIN);
            }

        }break;
        case DL_COMP_IIDX_OUTPUT_EDGE_INV:
            break;
        default:
            break;
    }
}
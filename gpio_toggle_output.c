#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timera.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"
//#include <cstdint>

/* This results in approximately 0.5s of delay assuming 80MHz CPU_CLK */
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
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_2_INST_INT_IRQN);
     NVIC_EnableIRQ(COMP0_INT_IRQn);
     NVIC_EnableIRQ(COMP1_INT_IRQn);
    DL_TimerA_startCounter(TIMER_1_INST);
    
    while (1) {
        //delay_cycles(DELAY);
        // DL_GPIO_togglePins(GPIO_OUT_PORT, GPIO_OUT_LED1_PIN);
    }
}


unsigned int utick = 0;//滴答定时器中断计数


// 找峰值逻辑
// * 比较器中断触发DMA采集，采集时间为1ms
// * 采集完成触发中断，找到最大值

// 测时间间隔逻辑
// * 中断读取定时器值，并将定时器清零
// * 判断数据是否有效，更新数据和数据index
// * 如果是最后一个数据，进入测距任务

// 测距逻辑
// * 切换到850mV阈值4ms
// * 如果1-4ms内触发了，测量触发时间，并标志为检测到；否则标志为没检测到
// * 4ms后切换回原来阈值，回到state 0

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


uint32_t comp_t0 = 0, comp_t1 = 0;
int32_t pulse_width;

#define data_n 5
int32_t data[data_n];
int data_i = 0;
int recv0 = 0, recv1 = 0;

// 状态：
// 0. 等待数据
// 1. 接收数据包
// 2. 测距
int remote_state = 0;
uint32_t dac0 = 113, dac_th = (uint32_t)(850*256/3300);
int detected = 0, detect_t = 0;

void GROUP1_IRQHandler(void)
{
    switch (DL_COMP_getPendingInterrupt(COMP_0_INST)) {
        case DL_COMP_IIDX_OUTPUT_EDGE:{
            if(utick - comp_t0 >= 4){
                comp_t0 = utick;
                DL_GPIO_togglePins(TEST_PORT, TEST_PIN_0_PIN);

                // 测时间间隔逻辑
                // * 中断读取定时器值，并将定时器清零
                // * 判断数据是否有效，更新数据和数据index
                // * 如果是最后一个数据，进入测距任务
                pulse_width = DL_TimerA_getTimerCount(TIMER_1_INST);
                DL_TimerA_setTimerCount(TIMER_1_INST, 0);

                switch (remote_state) {
                    case 0:{
                        if(pulse_width > 30000 && pulse_width < 50000){
                            data_i = 0;
                            remote_state = 1;   
                        }
                    } break;
                    case 1:{
                        if(data_i < 5){
                            if(pulse_width < 20000){
                                data[data_i++] = pulse_width;
                            }else{
                                remote_state = 0;
                            }
                        }

                        
                        if(data_i >= 5){
                            DL_TimerG_setCaptureCompareValue(PWM_0_INST, 500, DL_TIMER_CC_0_INDEX);
                            DL_TimerG_startCounter(TIMER_2_INST);
                            remote_state = 2;
                            DL_COMP_setDACCode0(COMP_0_INST, dac0+dac_th);
                        } 

                    } break;
                    case 2:{
                        // 测距逻辑
                        // * 切换到850mV阈值4ms
                        // * 如果1-4ms内触发了，测量触发时间，并标志为检测到；否则标志为没检测到
                        // * 4ms后切换回原来阈值，回到state 0


                    } break;
                    default: break;
                }

            }else if(DL_TimerA_getTimerCount(TIMER_1_INST) >= 1000 && remote_state == 2){
                detected = 1;
                detect_t = DL_TimerA_getTimerCount(TIMER_1_INST);
                remote_state = 3;
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

void TIMER_1_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_1_INST)) {
        case DL_TIMER_IIDX_OVERFLOW:
            remote_state = 0;
            break;
        default:
            break;
    }
}

void TIMER_2_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_2_INST)) {
        case DL_TIMER_IIDX_ZERO:
            DL_TimerG_setCaptureCompareValue(PWM_0_INST, 999, DL_TIMER_CC_0_INDEX);
            break;
        default:
            break;
    }
}

void SysTick_Handler(void){

    SysTick->CTRL &= ~(1 << 16); /*清除滴答定时器中断标志位*/
    utick++;//滴答定时器中断计数

    if(utick % 500 == 0){
        DL_GPIO_togglePins(LED_PORT, LED_LED1_PIN);

    }

    if(utick - comp_t0 >= 4){
        if(remote_state == 2){ //没检测到
            detected = 0;
            remote_state = 0;
            DL_COMP_setDACCode0(COMP_0_INST, dac0);
        }else if(remote_state == 3){ //检测到
            remote_state = 0;
            DL_COMP_setDACCode0(COMP_0_INST, dac0);
        }
    }
}
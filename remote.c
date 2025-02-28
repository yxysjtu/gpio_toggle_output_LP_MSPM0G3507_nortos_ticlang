#include "remote.h"

Remote_t remote;

void Remote_init(){
    remote.mode = 0;

    /* Setup interrupts on device */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
   // NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_2_INST_INT_IRQN);
     NVIC_EnableIRQ(COMP0_INT_IRQn);
     NVIC_EnableIRQ(COMP1_INT_IRQn);
    DL_TimerA_startCounter(TIMER_1_INST);
    DL_TimerA_startCounter(TIMER_0_INST);
}

// 找峰值逻辑
// * 比较器中断触发DMA采集（就第一个脉冲就够了），采集时间为1ms，采集频率1MHZ，共1000个点
// * 采集完成触发中断，找到最大值

// 测时间间隔逻辑
// * 中断读取定时器值，并将定时器清零
// * 判断数据是否有效，更新数据和数据index
// * 如果是最后一个数据，进入测距任务

// 测距逻辑
// * 切换到850mV阈值4ms
// * 如果1-4ms内触发了，测量触发时间，并标志为检测到；否则标志为没检测到
// * 4ms后切换回原来阈值，回到state 0

//乱七八糟的局部变量懒得整理了
extern unsigned int utick;

#define ADC_SAMPLE_N 2000
uint32_t adc_data[ADC_SAMPLE_N];
uint16_t adc0_peak = 0, adc1_peak = 0;
int adc_channel = 0;

uint32_t comp_t0 = 0, comp_t1 = 0;
int32_t pulse_width;

int32_t data[data_n];
int data_i = 0;
volatile int recv0 = 0, recv1 = 0;

// 状态：
// 0. 等待数据
// 1. 接收数据包
// 2. 测距
int remote_state = 0;
uint32_t dac0 = 113, dac_th = (uint32_t)(850*256/3300);
int detected = 0, detect_t = 0;
int detected1 = 0, detect_t1 = 0;

//检测相位差
int phase_diff = 0;
int phase_comp1 = 0;

void Remote_Handler(){
    if(utick - comp_t0 >= 5){
        if(remote_state == 2){ //没检测到
            detected = 0;
            remote_state = 0;
            DL_COMP_setDACCode0(COMP_0_INST, dac0);
            DL_COMP_setDACCode1(COMP_1_INST, dac0);
        }else if(remote_state == 3){ //检测到
            remote_state = 0;
            DL_COMP_setDACCode0(COMP_0_INST, dac0);
            DL_COMP_setDACCode1(COMP_1_INST, dac0);
        }
    }

    if(utick - comp_t0 >= 60 && recv0 == 1){
        recv0 = 0;
    }
    if(utick - comp_t1 >= 60 && recv1 == 1){
        recv1 = 0;
    }

    if(!(data[0] < 9000 && data[1] > 11000)){
        recv0 = 0;
        recv1 = 0;
    }

    if(recv0) DL_GPIO_setPins(RECV_INDICATOR_PORT, RECV_INDICATOR_RECV0_PIN);
    else DL_GPIO_clearPins(RECV_INDICATOR_PORT, RECV_INDICATOR_RECV0_PIN);

    if(recv1) DL_GPIO_setPins(RECV_INDICATOR_PORT, RECV_INDICATOR_RECV1_PIN);
    else DL_GPIO_clearPins(RECV_INDICATOR_PORT, RECV_INDICATOR_RECV1_PIN);

    if(detected) DL_GPIO_setPins(RECV_INDICATOR_PORT, RECV_INDICATOR_DETECTED_PIN);
    else DL_GPIO_clearPins(RECV_INDICATOR_PORT, RECV_INDICATOR_DETECTED_PIN);

    remote.state = recv0;
    for(int i = 0; i < data_n; i++){
        remote.data[i] = data[i] - 5000;
    }
    remote.recv_left = recv1;
    remote.recv_right = recv0;
    remote.left_strength = adc0_peak;
    remote.right_strength = adc1_peak;
    remote.recv_strength = (adc0_peak + adc1_peak) / 2;
    remote.direction = phase_diff;

    // remote.detected = detected | detected1;
    // remote.detected_left = detected1;
    // remote.detected_right = detected;
    // remote.detect_left_distance = detect_t1;
    // remote.detect_right_distance = detect_t;
    remote.detected = detected;
    remote.detect_distance = detect_t;
    
    if(remote.state){
        if(remote.data[2] < 5000) remote.mode = 0;
        else remote.mode = 1;
    }
    remote.vrx = remote.data[4];
    remote.vry = remote.data[3];
}

void dma_start(int channel){
    adc_channel = channel;
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,
        (uint32_t) DL_ADC12_getFIFOAddress(ADC12_0_INST));

    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &adc_data[0]);
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, ADC_SAMPLE_N);

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            //gCheckADC = true;
        {
            uint16_t adc_max = 0, temp = 0;
            for(int i = 0; i < ADC_SAMPLE_N; i++){
                if(adc_channel == 0){
                    temp = adc_data[i] & 0xffff;
                }else{
                    temp = adc_data[i] >> 16;
                }
                if(temp > adc_max) adc_max = temp;
            }

            if(adc_channel == 0){
                adc0_peak = adc_max;
            }else{
                adc1_peak = adc_max;
            }
            //DL_ADC12_stopConversion(ADC12_0_INST);

        }
            break;
        default:
            break;
    }
}



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

                        if(data_i == 1){
                            recv0 = 1;
                            dma_start(0);
                        }

                        if(data_i == 2){
                            if(phase_comp1 > pulse_width / 2){
                                phase_diff = phase_comp1 - pulse_width;
                            }else{
                                phase_diff = phase_comp1;
                            }
                        }

                        if(data_i >= 5){
                            DL_TimerG_setCaptureCompareValue(PWM_0_INST, 500, DL_TIMER_CC_0_INDEX);
                            DL_TimerG_startCounter(TIMER_2_INST);
                            remote_state = 2;
                            DL_COMP_setDACCode0(COMP_0_INST, dac0+dac_th);
                            DL_COMP_setDACCode1(COMP_1_INST, dac0+dac_th);
                            detected1 = 0;
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
                phase_comp1 = DL_TimerA_getTimerCount(TIMER_1_INST);

                comp_t1 = utick;
                DL_GPIO_togglePins(TEST_PORT, TEST_PIN_1_PIN);

                if(data_i == 2){
                    recv1 = 1;
                    dma_start(1);
                }
            }else if(DL_TimerA_getTimerCount(TIMER_1_INST) >= 1000 && DL_TimerA_getTimerCount(TIMER_1_INST) < 4000 && detected == 0 && data_i == 5){
                //TODO 有Bug会一直触发
                if(detected1 < 10){
                    detected1++;
                    //detected1 = 1;
                    detect_t1 = DL_TimerA_getTimerCount(TIMER_1_INST);
                }
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
        case DL_TIMER_IIDX_OVERFLOW:{
            remote_state = 0;
        }
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
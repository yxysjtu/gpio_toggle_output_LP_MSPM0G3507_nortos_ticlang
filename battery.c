#include "battery.h"

float battery_voltage;
const float alarm_voltage = 10.5f;

void Battery_Init(){
    /* Setup interrupts on device */
    NVIC_EnableIRQ(ADC12_1_INST_INT_IRQN);
}

void Battery_Handler(){
    static uint32_t tick = 0;
    if (tick % 1000 == 0) {
        DL_ADC12_startConversion(ADC12_1_INST);
    }

    if (battery_voltage <= alarm_voltage && tick > 1000) {
        if (tick % 100 == 0){
            DL_GPIO_togglePins(BEEP_PORT, BEEP_BEEP1_PIN);
        }
    } else {
        DL_GPIO_clearPins(BEEP_PORT, BEEP_BEEP1_PIN);
    }
    tick++;
}

void ADC12_1_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_1_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
        {
            uint16_t gAdcResult;
            gAdcResult = DL_ADC12_getMemResult(ADC12_1_INST, DL_ADC12_MEM_IDX_0);
            DL_ADC12_enableConversions(ADC12_1_INST);
            battery_voltage = gAdcResult * (3.3f / 4096.0f) * 7.98f;  // (69.8KR+10KR)/10KR=7.98
        }
            break;
        default:
            break;
    }
}

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_adc12.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timera.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"
#include "remote.h"
#include "battery.h"
#include "chassis.h"

/* This results in approximately 0.5s of delay assuming 80MHz CPU_CLK */
#define DELAY (40000000)

// 找峰值逻辑
// * 比较器中断触发DMA采集（就第一个脉冲就够了），采集时间为1ms，采集频率1MHZ，共1000个点
// * 采集完成触发中断，找到最大值



int main(void)
{
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();

    Remote_init();
    Battery_Init();
    Chassis_Init();
    
    while (1) {
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

    Remote_Handler();
    Battery_Handler();
    Chassis_Handler();
}
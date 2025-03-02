#ifndef BATTERY_H
#define BATTERY_H

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_adc12.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

void Battery_Init();
void Battery_Handler();

#endif

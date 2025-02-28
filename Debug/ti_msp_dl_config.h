/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMG0
#define PWM_0_INST_IRQHandler                                   TIMG0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMG0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             40000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_12
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM34)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX

/* Defines for PWM_1 */
#define PWM_1_INST                                                         TIMG6
#define PWM_1_INST_IRQHandler                                   TIMG6_IRQHandler
#define PWM_1_INST_INT_IRQN                                     (TIMG6_INT_IRQn)
#define PWM_1_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_1_C0_PORT                                                 GPIOB
#define GPIO_PWM_1_C0_PIN                                          DL_GPIO_PIN_6
#define GPIO_PWM_1_C0_IOMUX                                      (IOMUX_PINCM23)
#define GPIO_PWM_1_C0_IOMUX_FUNC                     IOMUX_PINCM23_PF_TIMG6_CCP0
#define GPIO_PWM_1_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_1_C1_PORT                                                 GPIOB
#define GPIO_PWM_1_C1_PIN                                          DL_GPIO_PIN_7
#define GPIO_PWM_1_C1_IOMUX                                      (IOMUX_PINCM24)
#define GPIO_PWM_1_C1_IOMUX_FUNC                     IOMUX_PINCM24_PF_TIMG6_CCP1
#define GPIO_PWM_1_C1_IDX                                    DL_TIMER_CC_1_INDEX

/* Defines for PWM_2 */
#define PWM_2_INST                                                         TIMG7
#define PWM_2_INST_IRQHandler                                   TIMG7_IRQHandler
#define PWM_2_INST_INT_IRQN                                     (TIMG7_INT_IRQn)
#define PWM_2_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_2_C0_PORT                                                 GPIOB
#define GPIO_PWM_2_C0_PIN                                         DL_GPIO_PIN_15
#define GPIO_PWM_2_C0_IOMUX                                      (IOMUX_PINCM32)
#define GPIO_PWM_2_C0_IOMUX_FUNC                     IOMUX_PINCM32_PF_TIMG7_CCP0
#define GPIO_PWM_2_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_2_C1_PORT                                                 GPIOB
#define GPIO_PWM_2_C1_PIN                                         DL_GPIO_PIN_16
#define GPIO_PWM_2_C1_IOMUX                                      (IOMUX_PINCM33)
#define GPIO_PWM_2_C1_IOMUX_FUNC                     IOMUX_PINCM33_PF_TIMG7_CCP1
#define GPIO_PWM_2_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                            (39U)
#define TIMER_0_INST_PUB_0_CH                                                (1)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMA1)
#define TIMER_1_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                         (64999U)
/* Defines for TIMER_2 */
#define TIMER_2_INST                                                     (TIMG8)
#define TIMER_2_INST_IRQHandler                                 TIMG8_IRQHandler
#define TIMER_2_INST_INT_IRQN                                   (TIMG8_INT_IRQn)
#define TIMER_2_INST_LOAD_VALUE                                          (4999U)




/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC0
#define ADC12_0_INST_IRQHandler                                  ADC0_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC0_INT_IRQn)
#define ADC12_0_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_1                                      DL_ADC12_MEM_IDX_1
#define ADC12_0_ADCMEM_1_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_1_REF_VOLTAGE_V                                       3.3
#define ADC12_0_INST_SUB_CH                                                  (1)
#define GPIO_ADC12_0_C0_PORT                                               GPIOA
#define GPIO_ADC12_0_C0_PIN                                       DL_GPIO_PIN_27
#define GPIO_ADC12_0_C1_PORT                                               GPIOA
#define GPIO_ADC12_0_C1_PIN                                       DL_GPIO_PIN_26



/* Defines for COMP_0 */
#define COMP_0_INST                                                        COMP0
#define COMP_0_INST_INT_IRQN                                      COMP0_INT_IRQn

/* Defines for COMP_0 DACCODE0 */
#define COMP_0_DACCODE0                                                    (113)


/* Defines for COMP_1 */
#define COMP_1_INST                                                        COMP1
#define COMP_1_INST_INT_IRQN                                      COMP1_INT_IRQn

/* Defines for COMP_1 DACCODE1 */
#define COMP_1_DACCODE1                                                    (113)


/* GPIO configuration for COMP_0 */


#define GPIO_COMP_0_OUT_PORT                                               GPIOA
#define GPIO_COMP_0_OUT_PIN                                       DL_GPIO_PIN_11
#define GPIO_COMP_0_IOMUX_OUT                                    (IOMUX_PINCM22)
#define GPIO_COMP_0_IOMUX_OUT_FUNC                    IOMUX_PINCM22_PF_COMP0_OUT
/* GPIO configuration for COMP_1 */
#define GPIO_COMP_1_IN1P_PORT                                            (GPIOB)
#define GPIO_COMP_1_IN1P_PIN                                    (DL_GPIO_PIN_24)
#define GPIO_COMP_1_IOMUX_IN1P                                   (IOMUX_PINCM52)
#define GPIO_COMP_1_IOMUX_IN1P_FUNC               (IOMUX_PINCM52_PF_UNCONNECTED)


#define GPIO_COMP_1_OUT_PORT                                               GPIOA
#define GPIO_COMP_1_OUT_PIN                                        DL_GPIO_PIN_3
#define GPIO_COMP_1_IOMUX_OUT                                     (IOMUX_PINCM8)
#define GPIO_COMP_1_IOMUX_OUT_FUNC                     IOMUX_PINCM8_PF_COMP1_OUT


/* Defines for VREF */
#define VREF_VOLTAGE_MV                                                     1400
#define GPIO_VREF_VREFPOS_PORT                                             GPIOA
#define GPIO_VREF_VREFPOS_PIN                                     DL_GPIO_PIN_23
#define GPIO_VREF_IOMUX_VREFPOS                                  (IOMUX_PINCM53)
#define GPIO_VREF_IOMUX_VREFPOS_FUNC                IOMUX_PINCM53_PF_UNCONNECTED



/* Defines for OPA_0 */
#define OPA_0_INST                                                          OPA0
#define GPIO_OPA_0_IN1NEG_PORT                                             GPIOA
#define GPIO_OPA_0_IN1NEG_PIN                                     DL_GPIO_PIN_24
#define GPIO_OPA_0_IOMUX_IN1NEG                                  (IOMUX_PINCM54)
#define GPIO_OPA_0_IOMUX_IN1NEG_FUNC                IOMUX_PINCM54_PF_UNCONNECTED
#define GPIO_OPA_0_OUT_PORT                                                GPIOA
#define GPIO_OPA_0_OUT_PIN                                        DL_GPIO_PIN_22
#define GPIO_OPA_0_IOMUX_OUT                                     (IOMUX_PINCM47)
#define GPIO_OPA_0_IOMUX_OUT_FUNC                   IOMUX_PINCM47_PF_UNCONNECTED
/* Defines for OPA_1 */
#define OPA_1_INST                                                          OPA1
#define GPIO_OPA_1_IN1NEG_PORT                                             GPIOA
#define GPIO_OPA_1_IN1NEG_PIN                                     DL_GPIO_PIN_17
#define GPIO_OPA_1_IOMUX_IN1NEG                                  (IOMUX_PINCM39)
#define GPIO_OPA_1_IOMUX_IN1NEG_FUNC                IOMUX_PINCM39_PF_UNCONNECTED
#define GPIO_OPA_1_OUT_PORT                                                GPIOA
#define GPIO_OPA_1_OUT_PIN                                        DL_GPIO_PIN_16
#define GPIO_OPA_1_IOMUX_OUT                                     (IOMUX_PINCM38)
#define GPIO_OPA_1_IOMUX_OUT_FUNC                   IOMUX_PINCM38_PF_UNCONNECTED



/* Defines for DMA_CH0 */
#define DMA_CH0_CHAN_ID                                                      (0)
#define ADC12_0_INST_DMA_TRIGGER                      (DMA_ADC0_EVT_GEN_BD_TRIG)



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for LED1: GPIOA.7 with pinCMx 14 on package pin 13 */
#define LED_LED1_PIN                                             (DL_GPIO_PIN_7)
#define LED_LED1_IOMUX                                           (IOMUX_PINCM14)
/* Port definition for Pin Group TEST */
#define TEST_PORT                                                        (GPIOB)

/* Defines for PIN_0: GPIOB.8 with pinCMx 25 on package pin 22 */
#define TEST_PIN_0_PIN                                           (DL_GPIO_PIN_8)
#define TEST_PIN_0_IOMUX                                         (IOMUX_PINCM25)
/* Defines for PIN_1: GPIOB.9 with pinCMx 26 on package pin 23 */
#define TEST_PIN_1_PIN                                           (DL_GPIO_PIN_9)
#define TEST_PIN_1_IOMUX                                         (IOMUX_PINCM26)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_PWM_1_init(void);
void SYSCFG_DL_PWM_2_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_TIMER_2_init(void);
void SYSCFG_DL_ADC12_0_init(void);
void SYSCFG_DL_COMP_0_init(void);
void SYSCFG_DL_COMP_1_init(void);
void SYSCFG_DL_VREF_init(void);
void SYSCFG_DL_OPA_0_init(void);
void SYSCFG_DL_OPA_1_init(void);
void SYSCFG_DL_DMA_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

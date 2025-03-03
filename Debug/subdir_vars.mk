################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../gpio_toggle_output.syscfg 

C_SRCS += \
../battery.c \
../chassis.c \
../gpio_toggle_output.c \
./ti_msp_dl_config.c \
/Applications/ti/mspm0_sdk_2_03_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c \
../motor.c \
../remote.c 

GEN_CMDS += \
./device_linker.cmd 

GEN_FILES += \
./device_linker.cmd \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./battery.d \
./chassis.d \
./gpio_toggle_output.d \
./ti_msp_dl_config.d \
./startup_mspm0g350x_ticlang.d \
./motor.d \
./remote.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./battery.o \
./chassis.o \
./gpio_toggle_output.o \
./ti_msp_dl_config.o \
./startup_mspm0g350x_ticlang.o \
./motor.o \
./remote.o 

GEN_MISC_FILES += \
./device.cmd.genlibs \
./ti_msp_dl_config.h \
./Event.dot 

OBJS__QUOTED += \
"battery.o" \
"chassis.o" \
"gpio_toggle_output.o" \
"ti_msp_dl_config.o" \
"startup_mspm0g350x_ticlang.o" \
"motor.o" \
"remote.o" 

GEN_MISC_FILES__QUOTED += \
"device.cmd.genlibs" \
"ti_msp_dl_config.h" \
"Event.dot" 

C_DEPS__QUOTED += \
"battery.d" \
"chassis.d" \
"gpio_toggle_output.d" \
"ti_msp_dl_config.d" \
"startup_mspm0g350x_ticlang.d" \
"motor.d" \
"remote.d" 

GEN_FILES__QUOTED += \
"device_linker.cmd" \
"device.opt" \
"ti_msp_dl_config.c" 

C_SRCS__QUOTED += \
"../battery.c" \
"../chassis.c" \
"../gpio_toggle_output.c" \
"./ti_msp_dl_config.c" \
"/Applications/ti/mspm0_sdk_2_03_00_07/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c" \
"../motor.c" \
"../remote.c" 

SYSCFG_SRCS__QUOTED += \
"../gpio_toggle_output.syscfg" 



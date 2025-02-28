#ifndef REMOTE_H
#define REMOTE_H

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_adc12.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_timera.h"
#include "ti/driverlib/dl_timerg.h"
#include "ti_msp_dl_config.h"

#define data_n 5

typedef struct{
    //通信
    int state; //0通信失败，1通信成功
    int data[data_n]; //0-10000 左右，有误差

    //跟随
    int recv_left; //左接收头是否接收到
    int recv_right; //右接收头是否接收到
    int recv_strength; //接收强度平均
    int left_strength; //左接收头接收强度
    int right_strength; //右接收头接收强度
    int direction; //声源方向，大于0为偏右

    //避障
    int detected; //是否有障碍物
    // int detected_left;
    // int detected_right;
    int detect_distance; //障碍物距离，1000大致对应10cm
    // int detect_right_distance;


} Remote_t;

extern Remote_t remote;

void Remote_init();
void Remote_Handler();


#endif

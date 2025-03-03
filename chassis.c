#include "chassis.h"
#include "motor.h"
#include "remote.h"

const float rotation_speed_coefficient = 0.002f;
const float translation_speed_coefficient = 0.001f;

float limit(float val, const float min, const float max) {
  if (min > max)
    return val;
  else if (val < min)
    val = min;
  else if (val > max)
    val = max;
  return val;
}

int deadBand(int val, const int min, const int max) {
  if (val < max && val > min) {
    val = 0;
  }
  return val;
}

void Chassis_Init(){
    Motor_Init();
}

void Chassis_Handler(){
    if (remote.mode == 0 && remote.state == 1){
        left_wheel.stop = 0;
        right_wheel.stop = 0;
        remote.direction = limit(remote.direction, -300, 300);
        // Speed are normalized. Go to motor.c and find the speed->duty part to change the max speed.
        if (remote.direction <= -150 || remote.direction >= 150){
            left_wheel.speed = limit(rotation_speed_coefficient * remote.direction, -1, 1);
            right_wheel.speed = limit(-rotation_speed_coefficient * remote.direction, -1, 1);
        } else{
            left_wheel.speed = limit(-translation_speed_coefficient * deadBand(remote.recv_strength - 2000, -200, 100), -1, 1);
            right_wheel.speed = limit(-translation_speed_coefficient * deadBand(remote.recv_strength - 2000, -200, 100), -1, 1);
        }
    } else if (remote.mode == 0 && remote.state == 0){
		left_wheel.stop = 0;
        right_wheel.stop = 0;
		left_wheel.speed = 0.5f;
        right_wheel.speed = -0.5f;
	} else if (remote.mode == 1 && remote.state == 1){
		left_wheel.stop = 0;
        right_wheel.stop = 0;
        float vx, vy;
        vx = deadBand((4200.0f - (float)remote.vrx), -400, 400) / 4200.0f;
        vy = deadBand((4200.0f - (float)remote.vry), -400, 400) / 4200.0f;
        // Speed are normalized. Go to motor.c and find the speed->duty part to change the max speed.
        if (vx != 0){
            left_wheel.speed = limit(vx, -1, 1);
            right_wheel.speed = limit(-vx, -1, 1);
        } else if (vy != 0){
            left_wheel.speed = limit(vy, -1, 1);
            right_wheel.speed = limit(vy, -1, 1);
        } else{
            left_wheel.speed = 0;
            right_wheel.speed = 0;
        }
    } else{
        left_wheel.stop = 1;
        right_wheel.stop = 1;
    }
    Motor_Handler();
}

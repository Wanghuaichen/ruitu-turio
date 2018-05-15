/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_gpio.h
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        –æ∆¨ ‰≥ˆøÿ÷∆Õ∑Œƒº˛
**************************************************************************************************
*/
#ifndef _APP_GPIO_H_
#define _APP_GPIO_H_
#include "include.h"
/*--------------- ∫Í∂®“Â --------------*/
#define OUT_CONTROL_ON                0
#define OUT_CONTROL_OFF               1
#define OUT_CONTROL_BLINKING          2
#define LED_OAS_LEFT_BLINKING         0x01   // ◊Û±‹’œ±®æØµ∆…¡À∏
#define LED_OAS_RIGHT_BLINKING        0x02   // ”“±‹’œ±®æØµ∆…¡À∏
#define LED_RUN_BLINKING              0x04   // ‘À––µ∆…¡À∏
#define LED_BATTERY_BLINKING          0x08   // µÁ≥ÿµ∆…¡À∏
#define LED_ETHERNET_BLINKING         0x10   // Õ¯¬Áµ∆…¡À∏
#define RSV_OUT1_BLINKING             0x20   // ‘§¡Ù ‰≥ˆ1…¡À∏
#define RSV_OUT2_BLINKING             0x40   // ‘§¡Ù ‰≥ˆ2…¡À∏
#define RSV_OUT3_BLINKING             0x80   // ‘§¡Ù ‰≥ˆ3…¡À∏
/*--------------- ±‰¡ø∂®“Â --------------*/

/*--------------- ∫Ø ˝∂®“Â --------------*/

void control_blinking(void);
void control_ethernet_led(uint8_t onoff);
void control_battery_led(uint8_t onoff);
void control_fan2_power(uint8_t onoff);
void control_fan1_power(uint8_t onoff);
void control_route_power(uint8_t onoff);
void control_lidar_power(uint8_t onoff);
void control_motort_enable(uint8_t onoff);
void control_imu_power(uint8_t onoff);
void control_run_led(uint8_t onoff);
void control_reserved_out1(uint8_t onoff);
void control_reserved_out2(uint8_t onoff);
void control_reserved_out3(uint8_t onoff);
void control_right_oas_led(uint8_t onoff);
void control_left_oas_led(uint8_t onoff);
void control_init(void);
void control_all_off(void);
void control_all_on(void);
#endif

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





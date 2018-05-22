/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_gpio.h
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        芯片输出控制头文件
**************************************************************************************************
*/
#ifndef _APP_GPIO_H_
#define _APP_GPIO_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
#define OUT_CONTROL_ON                0
#define OUT_CONTROL_OFF               1
#define OUT_CONTROL_BLINKING          2
#define LED_OAS_LEFT_BLINKING         0x01   // 左避障报警灯闪烁
#define LED_OAS_RIGHT_BLINKING        0x02   // 右避障报警灯闪烁
#define LED_RUN_BLINKING              0x04   // 运行灯闪烁
#define LED_BATTERY_BLINKING          0x08   // 电池灯闪烁
#define LED_ETHERNET_BLINKING         0x10   // 网络灯闪烁
#define RSV_OUT1_BLINKING             0x20   // 预留输出1闪烁
#define RSV_OUT2_BLINKING             0x40   // 预留输出2闪烁
#define RSV_OUT3_BLINKING             0x80   // 预留输出3闪烁
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/

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

//设备控制-开启或者关闭激光雷达等等
void SetFan(uint8_t fan,uint8_t state); //打开或关闭 fan：fan1或者fan2 state：ENABLE/DISABLE
void SetRadar(uint8_t state);    //打开雷达 or DISABLE默认只有一个雷达
void SetRoute(uint8_t state);    //打路由器 or DISABL
void SetIMU(uint8_t state);      //打开IMU or DISABLE

//  //设置LED灯状态，本次只有三个LED灯
//  void SetTopLed(choice);//常亮on-2、闪烁 blinking-1、关闭off-0 提前define
//  void SetMidLed(choice);//常亮2、闪烁1、关闭0
//  void SetRgbLed(color,choice);//常亮2（选择R/G/B?）、闪烁1、关闭0  貌似要两个IO去控
/*------------------- 传感器信号及控制 -------------------------------*/
uint8_t GetLeftObstacleSensor(void);     // 1为有障碍 ，0为无障碍
uint8_t GetRightObstacleSensor(void);    // 1为有障碍 ， 0为无障碍
void SetLeftObstacleLed(uint8_t state);  // LED_ON/LED_OFF/LED_BLINKING
void SetRightObstacleLed(uint8_t state); // LED_ON/LED_OFF/LED_BLINKING
uint8_t GetIRLoactionSensor(void);    // 1为有障碍 ， 0为无障碍

void task_sensors_init(void);
void task_sensors(void);
#endif

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





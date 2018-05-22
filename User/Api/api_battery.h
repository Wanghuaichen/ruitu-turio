/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_battery.h
* @author       zhou
* @version      V1.0
* @date         2018/5/17
* @brief        电池接口程序头文件
**************************************************************************************************
*/
#ifndef _API_BATTERY_H_
#define _API_BATTERY_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
#define   FAN1          0
#define   FAN2          1
// LED状态
#define   LED_ON        2
#define   LED_OFF       0
#define   LED_BLINKING  1
// 定义电池状态
#define   BATTERY_FLAG_GET_PARAM       0x01
//
#define   BATTERY_ADDR                  0x01 // 定义电池地址
#define   BATTERY_FUN_CODE              0x03 // 定义功能码
// 寄存器地址定义
#define   BATTERY_REG_OVER_VOLTAGE         0x00 // 定义单体过压寄存器地址
#define   BATTERY_REG_RELEASE_OVER         0x01 // 定义单体过压寄存器地址
#define   BATTERY_REG_UNDER_VOLTAGE        0x02 // 定义单体过压寄存器地址
#define   BATTERY_REG_RELEASE_UNDER        0x03 // 定义单体过压寄存器地址
#define   BATTERY_REG_VOTAGE               0x12 // 定义单体过压寄存器地址
#define   BATTERY_REG_VOTAGE_PERCENT       0x28 // 定义单体过压寄存器地址
#define   BATTERY_REG_CURRENT              0x13 // 定义单体过压寄存器地址
/*--------------- 变量定义 --------------*/
typedef struct
{
  uint16_t batteryVoltage; // 电压
  uint16_t batteryCurrent; // 电流
  uint16_t batteryPercent; // 百分比
}sBATTERY;
/*--------------- 函数定义 --------------*/
void battery_control(uint8_t regAddr);
void battery_tx_processing(uint8_t addr,uint8_t funCode, uint8_t regAddr);
void battery_rx_processing(uint8_t *buf, uint16_t len);
void task_battery_init(void);
void task_battery(void);
void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus);
void set_robot_command(E_MOTOR_STATE eRobotStatus ,char *buf);
E_MOTOR_STATE get_robot_command(char *buf);
E_WORK_MODE get_robot_run_mode(char *buf);
uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd);
#endif



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/






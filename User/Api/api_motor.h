/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_motor.h
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        电机接口函数头文件
**************************************************************************************************
*/
#ifndef _API_MOTOR_H_
#define _API_MOTOR_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
// 针对canopen定义
// nmt令指定义
#define START_REMOTE_NODE              1 // 开启远程节点
#define STOP_REMOTE_NODE               2 // 关闭远程节点
#define ENTER_PREOPERATIONAL_STATE     128 // 进入预运行状态
#define RESET_NODE                     129 // 复位结点
#define RESET_COMMUNICTION             130 // 复位通信

// ID定义
#define SYNCHRONIZATION_CYCLE_ID       0x000601 // 同步两个电机的周期 Cycle synchronization
#define SYNCHRONIZATION_START_ID       0x000601 // 启动周期同步
#define NMT_BROADCAST_ID               0x000000 // NMT用的广播ID
#define NMT_BROADCAST_ID               0x000000 // NMT用的广播ID
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/

#endif


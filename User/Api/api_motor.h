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
#define DEVICE_ID                      0x01 // 设备ID
// nmt令指定义
#define NMT_START_REMOTE_NODE              1 // 开启远程节点
#define NMT_STOP_REMOTE_NODE               2 // 关闭远程节点
#define NMT_ENTER_PREOPERATIONAL_STATE     128 // 进入预运行状态
#define NMT_RESET_NODE                     129 // 复位结点
#define NMT_RESET_COMMUNICTION             130 // 复位通信

// ID定义
#define SYNCHRONIZATION_CYCLE_ID       0x000600 // 同步两个电机的周期 Cycle synchronization
#define SYNCHRONIZATION_START_ID       0x000600 // 启动周期同步
#define NMT_BROADCAST_ID               0x000000 // NMT用的广播ID
#define NMT_NODE_GUARDING_ID           0x000700 // NMT用的节点保护ID
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/

void motor_start_node(void);
void motor_stop_node(void);
void motor_set_syn_cycle(void);
void motor_start_syn(void);
uint8_t motor_get_state(uint8_t *buf,uint8_t len);
uint8_t motor_set_position(uint32_t position);
uint8_t motor_set_velocity(uint32_t velocity);
void motor_start_position_mode(void);
#endif


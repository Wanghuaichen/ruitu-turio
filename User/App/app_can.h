/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_can.h
* @author       zhou
* @version      V1.0
* @date         2018/4/28
* @brief        can应用程序头文件
**************************************************************************************************
*/
#ifndef _APP_CAN_H_
#define _APP_CAN_H_
#include "include.h"
/*--------------- 宏定义 --------------*/

/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/
void task_can_rx_init(void);
void task_can_rx(void);
void can_rx_data_processing(uint8_t comType, CanRxMsg *rxMsg);
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





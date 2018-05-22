/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.h
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        基于w5500的tcp应用程序头文件
**************************************************************************************************
*/
#ifndef _APP_TCP_H_
#define _APP_TCP_H_
#include "include.h"
/*--------------- 宏定义 --------------*/

/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/
void Command_tcp_client(void);
void Status_tcp_client(void);
void task_tcp_init(void);
void task_tcp(void);

#endif


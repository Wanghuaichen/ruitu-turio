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
void do_tcp_server(void);
void do_tcp_client(void);
void ethernet_printf(char *buf, uint16_t len);
void ethernet_rx_data_processing(char *buf,uint16_t len);
#endif


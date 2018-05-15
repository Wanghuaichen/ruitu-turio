/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : include.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : 所有头文件包含，以及一些基础的宏定义
*******************************************************************************/


#ifndef     _INCLUDE_H_
#define     _INCLUDE_H_

/*****************宏定义************************/
#define      TRUE     1
#define      FALSE    0

#define      ON       1
#define      OFF      0




/**************** 头文件 **********************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

/******************数据格式定义***********************/
//----数据结构分解16位---
typedef union
{
   uint16_t  word;
   uint8_t   byte[2];
   struct {
       uint8_t    L;
       uint8_t    H;
   }HL;
}uUINT16;

//----数据结构分解32位--
typedef union
{
   uint32_t  longType;
   uint8_t   byte[4];
   struct {
       uint8_t    L;
       uint8_t    M;
       uint8_t    H;
       uint8_t    S;
   }SHML;
}uUINT32;


// 芯片头文件
#include "stm32f10x_conf.h"
#include "interfaces_bottom.h"
// 应用头文件
#include "main.h"

#include "ocp_uart.h"
#include "ocp_gpio.h"
#include "ocp_can.h"
#include "ocp_spi.h"
#include "ocp_adc.h"
#include "ocp_timer.h"

#include "bfm_w5500.h"

#include "app_config.h"
#include "app_uart.h"
#include "app_can.h"
#include "app_tcp.h"
#include "app_gpio.h"
#include "app_pt100.h"

#include "api_dataPro.h"
#include "api_motor.h"

#include "w5500_config.h"
#include "socket.h"

// 系统头文件
#include "Param.h"
#include "private.h"
#include "task.h"
//#include "log.h"
#include "parameter.h"



#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





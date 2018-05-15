/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : include.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : ����ͷ�ļ��������Լ�һЩ�����ĺ궨��
*******************************************************************************/


#ifndef     _INCLUDE_H_
#define     _INCLUDE_H_

/*****************�궨��************************/
#define      TRUE     1
#define      FALSE    0

#define      ON       1
#define      OFF      0




/**************** ͷ�ļ� **********************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

/******************���ݸ�ʽ����***********************/
//----���ݽṹ�ֽ�16λ---
typedef union
{
   uint16_t  word;
   uint8_t   byte[2];
   struct {
       uint8_t    L;
       uint8_t    H;
   }HL;
}uUINT16;

//----���ݽṹ�ֽ�32λ--
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


// оƬͷ�ļ�
#include "stm32f10x_conf.h"
#include "interfaces_bottom.h"
// Ӧ��ͷ�ļ�
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

// ϵͳͷ�ļ�
#include "Param.h"
#include "private.h"
#include "task.h"
//#include "log.h"
#include "parameter.h"



#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





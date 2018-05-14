/******************** (C) COPYRIGHT PEOPLE ******************************
* File Name          : log.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.12.2
* Description        : 日志文件头文件
*******************************************************************************/
#ifndef  _LOG_H_
#define  _LOG_H_

#include "include.h"
/*******************宏定义*************************/
#define PRINTF_LENGTH              TX_BUF_SIZE  // 长度不超过tx发送长度

#define PRINTF_CHANNEL_DISABLE     1
#define PRINTF_CHANNEL_ENABLE      3

#define PRINTF_MESSAGE_DISABLE     1
#define PRINTF_MESSAGE_ENABLE      5
//*************任务相关定义***********************/

/**************函数相关定义**********************/
void PrintfInit(void);
void LogPrintf(const char *format, ...);
void TestPrintf(const char *format, ...);
void PrintfChannel(uint8_t length);
#endif


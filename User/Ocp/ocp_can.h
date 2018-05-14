/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         can.h
* @author       zhou
* @version      V1.0
* @date         2017-08-11
* @brief        can口通信头文件
**************************************************************************************************
*/
#ifndef  _CAN_H_
#define  _CAN_H_

#include "include.h"

/********* 宏定义 *************/

/********* 变量定义 *************/
#define CAN_BUF_LENGTH    150
typedef struct
{
  volatile uint8_t top;
  uint8_t          tail;
  uint8_t          length;
  CanRxMsg         rxMsg[CAN_BUF_LENGTH];
}sCAN_BUF;
typedef struct
{
  uint8_t canCmd;  // 将所有Can通信数据集中到一个任务处理
  uint8_t canType; // 获得数据的来源can1或者can2
  uint8_t cmd;     // 数据指令
  uint8_t dir;     // 数据发送方向，固定为接收
  uint8_t addr;    // 发送数据的源地址
  uint8_t data[8]; // 数据内容
}sCAN_PROTOCOL;

/********* 函数定义 *************/

void can1_init(void);
uint8_t can_tx_data_package(CAN_TypeDef *hcan, uint8_t *buf, uint8_t len, uint32_t identifier,uint8_t frameMode);
#endif




/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





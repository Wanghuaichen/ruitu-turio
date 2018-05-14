/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_can.c
* @author       zhou
* @version      V1.0
* @date         2018/4/28
* @brief        can 应用程序
**************************************************************************************************
*/
#include "include.h"

void task_can_rx_init(void)
{
  _TaskCanRx.fun = task_can_rx;
  _TaskCanRx.command = CMD_TASK_CAN_RX;
}

void task_can_rx(void)
{
  // can1接收数据处理
  if (sCan1Buf_.tail != sCan1Buf_.top)
  {
    can_rx_data_processing(COM_TYPE_CAN, &sCan1Buf_.rxMsg[sCan1Buf_.tail++]);
    if (sCan1Buf_.tail >= CAN_BUF_LENGTH)
    {
      sCan1Buf_.tail = 0;
    }
  }
}

void can_rx_data_processing(uint8_t comType, CanRxMsg *rxMsg)
{

}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





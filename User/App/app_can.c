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
/**
*@function void task_can_rx_init(void)
*@brief    can接收任务初始化
*@param    void：空
*@return   无
*@date     2018/5/14
*/
void task_can_rx_init(void)
{
  _TaskCanRx.fun = task_can_rx;
  _TaskCanRx.command = CMD_TASK_CAN_RX;
}
/**
*@function void task_can_rx(void)
*@brief    can接收任务函数
*@param    void：无
*@return   无
*@date     2018/5/14
*/
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
/**
*@function void can_rx_data_processing(uint8_t comType, CanRxMsg *rxMsg)
*@brief    can接收数据处理
*@param    comType：接收类型，can1和can2
*@param    rxMsg：接收的数据
*@return   无
*@date     2018/5/14
*/
void can_rx_data_processing(uint8_t comType, CanRxMsg *rxMsg)
{
  if (rxMsg->ExtId  == (NMT_NODE_GUARDING_ID|DEVICE_ID))
  {
    memcpy(canRxData_,rxMsg->Data,8 );
  }
}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





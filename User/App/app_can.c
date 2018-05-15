/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_can.c
* @author       zhou
* @version      V1.0
* @date         2018/4/28
* @brief        can Ӧ�ó���
**************************************************************************************************
*/
#include "include.h"
/**
*@function void task_can_rx_init(void)
*@brief    can���������ʼ��
*@param    void����
*@return   ��
*@date     2018/5/14
*/
void task_can_rx_init(void)
{
  _TaskCanRx.fun = task_can_rx;
  _TaskCanRx.command = CMD_TASK_CAN_RX;
}
/**
*@function void task_can_rx(void)
*@brief    can����������
*@param    void����
*@return   ��
*@date     2018/5/14
*/
void task_can_rx(void)
{
  // can1�������ݴ���
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
*@brief    can�������ݴ���
*@param    comType���������ͣ�can1��can2
*@param    rxMsg�����յ�����
*@return   ��
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





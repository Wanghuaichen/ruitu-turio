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
  _TaskCanRx.state = TASK_STATE_RUN;
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
#ifdef COM_LOOP_BACK_ENABLE
    can_tx_data_package(CAN1,sCan1Buf_.rxMsg[sCan1Buf_.tail].Data,8,sCan1Buf_.rxMsg[sCan1Buf_.tail].StdId,CAN_RTR_DATA);
#endif
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
void task_motor_can_init(void)
{
  _TaskMotorCan.fun = task_motor_can;

}
void task_motor_can(void)
{
  uint8_t bar = TASK_BAR_CMD;
  if (_TaskMotorCan.progressBar == bar++)
  {
    motor_start_node();
    _TaskMotorCan.progressBar++;
    _TaskMotorCan.interval = 10;
    _TaskMotorCan.state = TASK_STATE_DELAY;
  }
 else if (_TaskMotorCan.progressBar == bar++)
  {
    motor_set_syn_cycle();
    _TaskMotorCan.progressBar++;
    _TaskMotorCan.interval = 10;
    _TaskMotorCan.state = TASK_STATE_DELAY;
  }
  else if (_TaskMotorCan.progressBar == bar++)
  {
    motor_start_syn();
    _TaskMotorCan.progressBar++;
    _TaskMotorCan.interval = 10;
    _TaskMotorCan.state = TASK_STATE_DELAY;
      _TaskMotorControl.state = TASK_STATE_RUN;
  }
  else if (_TaskMotorCan.progressBar == bar++)
  {
   // motor_get_state();
    _TaskMotorCan.interval = 1000;
    _TaskMotorCan.state = TASK_STATE_DELAY;
  }

}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





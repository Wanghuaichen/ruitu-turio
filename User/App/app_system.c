/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_system.c
* @author       zhou
* @version      V1.0
* @date         2018/5/26
* @brief        系统函数，主要用于整个系统的工作安排
*               -- 上电初始化事件
*               ---- 判断电机是否进入工作状态
*               ---- 电机进入工作状态，开启开同步
*               ---- 同步完成后进入回零模式
*               ---- 回零完成后进入停止模式等待上位机指令
**************************************************************************************************
*/
#include "include.h"
void task_system_init(void)
{
  _TaskSystem.fun = task_system;
  _TaskSystem.state = TASK_STATE_RUN;
}
void task_system(void)
{
  uint8_t bar = TASK_BAR_CMD;
  _TaskSystem.interval = 60;
  _TaskSystem.state = TASK_STATE_DELAY;
  if (_TaskSystem.progressBar == bar++)
  {
    motor_tx_data_processing( 'g', MOTOR_REG_GET_MONITORING_STATUS,0,0);
    _TaskSystem.progressBar++;
  }
  else if (_TaskSystem.progressBar == bar++)
  {
    if ( rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
      _TaskSystem.progressBar++;
    else
      _TaskSystem.progressBar--;
  }
  else if (_TaskSystem.progressBar == bar++)
  {
    _TaskSystem.state = TASK_STATE_SLEEP;
    _TaskMotorCan.state = TASK_STATE_RUN;
  }


}
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





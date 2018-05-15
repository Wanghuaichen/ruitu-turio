/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_motor.c
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        电机接口函数文件
**************************************************************************************************
*/
#include "include.h"
 uint8_t motorDataSetSyn[8]   = {0x23,0x06,0x10,0x00,0xA0,0x0F,0x00,0x00}; // 同步周期设置数据
 uint8_t motorDataStartSyn[8] = {0x23,0x05,0x10,0x00,0x80,0x00,0x00,0x40}; // 开启同步数据
 uint8_t motorDataNull[8]      = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // 开启同步数据

const char modeZero[] = "i r0 0x8000\n";  // 开启原点回零模式所发字符串
const char modePosition[] = "i r0 0x8001";  // 开启位置模式所发字符串
const char modeSuspend[] = "t 0";  // 开启位置模式所发字符串
const char setPosition[] = "i r3 " ; // 设置位置值-在r3后面拼接位置值的字符串
const char setVelocity[] = "i r4 " ; // 设置速度值-在r3后面拼接速度值的字符串
/**
*@function void motor_start_node(void)
*@brief    开启远程节点程序
*@return   无
*@date     2018/5/14
*/
void motor_start_node(void)
{
  uint32_t id;
  id = NMT_BROADCAST_ID;
  motorDataNull[0] = NMT_START_REMOTE_NODE;
  can_tx_data_package(CAN1, motorDataNull, 8, id, CAN_RTR_DATA);
}
/**
*@function void motor_stop_node(void)
*@brief    关闭远程节点
*@return   无
*@date     2018/5/14
*/
void motor_stop_node(void)
{
  uint32_t id;
  id = NMT_BROADCAST_ID;
  motorDataNull[0] = NMT_STOP_REMOTE_NODE;
  can_tx_data_package(CAN1, motorDataNull, 8, id, CAN_RTR_DATA);
}
/**
*@function void motor_set_syn_cycle(void)
*@brief    电机设置同步周期
*@return   无
*@date     2018/5/14
*/
void motor_set_syn_cycle(void)
{
  uint32_t id;
  id = SYNCHRONIZATION_CYCLE_ID | DEVICE_ID;
  can_tx_data_package(CAN1, motorDataSetSyn, 8, id, CAN_RTR_DATA);
}
/**
*@function void motor_start_syn(void)
*@brief    开启同步
*@return   无
*@date     2018/5/14
*/
void motor_start_syn(void)
{
  uint32_t id;
  id = SYNCHRONIZATION_START_ID | DEVICE_ID;
  can_tx_data_package(CAN1, motorDataStartSyn, 8, id, CAN_RTR_DATA);
}
/**
*@function uint8_t motor_get_state(uint8_t *buf, uint8_t len)
*@brief    获取电机状态，
*@param    buf：返回状态数据
*@param    len：返回数据的长度
*@return   1 ：获取状态成功 0：获取状态失败
*@date     2018/5/14
*/
uint8_t motor_get_state(uint8_t *buf,uint8_t len)
{
  uint32_t i = 0,id;
  id = NMT_NODE_GUARDING_ID | DEVICE_ID;
  canRxFlag_ &= ~CANOPNE_GET_NODE_STATE;
  can_tx_data_package(CAN1, motorDataNull, 8, id, CAN_RTR_REMOTE);
  while (++i < 0xffffff)
  {
    if (canRxFlag_ & CANOPNE_GET_NODE_STATE == CANOPNE_GET_NODE_STATE)
    {
      memcpy( buf,canRxData_,len);
      return 1;
    }
  }
  return 0;
}

uint8_t motor_set_position(uint32_t position)
{
  uint32_t i;
  uint8_t len;
  char trans[10],sendAsc[20] = "\0";
  // 设置位置
  rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
  i32toa(position, trans,&len);
  strcat(sendAsc, setPosition);
  strcat(sendAsc, trans);
  printf(sendAsc);
  while (++i < 0x9FFFFFF)
  {
    if ((rs232RxFlag_ & RS232_SET_MOTOR_PARAM) == RS232_SET_MOTOR_PARAM)
      break;
  }
  if (i >= 0x9FFF)
    return 0;
  return 1;
}

uint8_t motor_set_velocity(uint32_t velocity)
{
  uint16_t i;
  uint8_t len;
  char trans[10],sendAsc[20] = "\0";
  // 设置位置
  rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
  i32toa(velocity,trans,&len);
  strcat(sendAsc, setVelocity);
  strcat(sendAsc, trans);
  printf(sendAsc);
  while (++i < 0x9FFF)
  {
    if ((rs232RxFlag_ & RS232_SET_MOTOR_PARAM) == RS232_SET_MOTOR_PARAM)
      break;
  }
  if (i >= 0x9FFF)
    return 0;
  return 1;
}


void motor_start_position_mode(void)
{
  printf(modeZero);
}


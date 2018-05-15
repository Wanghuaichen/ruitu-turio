/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_motor.c
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        ����ӿں����ļ�
**************************************************************************************************
*/
#include "include.h"
 uint8_t motorDataSetSyn[8]   = {0x23,0x06,0x10,0x00,0xA0,0x0F,0x00,0x00}; // ͬ��������������
 uint8_t motorDataStartSyn[8] = {0x23,0x05,0x10,0x00,0x80,0x00,0x00,0x40}; // ����ͬ������
 uint8_t motorDataNull[8]      = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // ����ͬ������

const char modeZero[] = "i r0 0x8000\n";  // ����ԭ�����ģʽ�����ַ���
const char modePosition[] = "i r0 0x8001";  // ����λ��ģʽ�����ַ���
const char modeSuspend[] = "t 0";  // ����λ��ģʽ�����ַ���
const char setPosition[] = "i r3 " ; // ����λ��ֵ-��r3����ƴ��λ��ֵ���ַ���
const char setVelocity[] = "i r4 " ; // �����ٶ�ֵ-��r3����ƴ���ٶ�ֵ���ַ���
/**
*@function void motor_start_node(void)
*@brief    ����Զ�̽ڵ����
*@return   ��
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
*@brief    �ر�Զ�̽ڵ�
*@return   ��
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
*@brief    �������ͬ������
*@return   ��
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
*@brief    ����ͬ��
*@return   ��
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
*@brief    ��ȡ���״̬��
*@param    buf������״̬����
*@param    len���������ݵĳ���
*@return   1 ����ȡ״̬�ɹ� 0����ȡ״̬ʧ��
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
  // ����λ��
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
  // ����λ��
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


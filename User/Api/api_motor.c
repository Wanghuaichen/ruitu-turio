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

const char sendReturn[] = "\n";
const char modeZero[] = "i r0 0x8000\n";  // ����ԭ�����ģʽ�����ַ���
const char modePosition[] = "i r0 0x8001\n";  // ����λ��ģʽ�����ַ���
const char modeSuspend[] = "t 0";  // ����λ��ģʽ�����ַ���
const char setPosition[] = "i r3 " ; // ����λ��ֵ-��r3����ƴ��λ��ֵ���ַ���
const char setVelocity[] = "i r4 " ; // �����ٶ�ֵ-��r3����ƴ���ٶ�ֵ���ַ���
const char readReg[] = "g r0xa0\n "; //
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
/**
*@function uint8_t motor_set_position(uint32_t position)
*@brief    ���õ��λ��
*@param    position :�����λ��
*@return   1:�ɹ� 0:ʧ��
*/
uint8_t motor_set_position(uint32_t position)
{
  uint8_t len;
  char trans[10],sendAsc[20] = "\0";
  // ����λ��
  rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
  i32toa(position, trans,&len);
  strcat(sendAsc, setPosition);
  strcat(sendAsc, trans);
  strcat(sendAsc, sendReturn);
  len += sizeof(setPosition) + sizeof(sendReturn);
  Circle_Write_Data(&sUart3TxCircleBuf_,(uint8_t*)sendAsc,len -1);
  return 1;
}
/**
*@function uint8_t motor_set_velocity(uint32_t velocity)
*@brief    ���õ���������ٶ�
*@param    velocity :���õ��ٶ�
*@return   1:�ɹ� 0:ʧ��
*/
uint8_t motor_set_velocity(uint32_t velocity)
{
  uint8_t len;
  char trans[10],sendAsc[20] = "\0";
  // ����λ��
  rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
  i32toa(velocity,trans,&len);
  strcat(sendAsc, setVelocity);
  strcat(sendAsc, trans);
  strcat(sendAsc, sendReturn);
  len += sizeof(setPosition) + sizeof(sendReturn);
  Circle_Write_Data(&sUart3TxCircleBuf_,(uint8_t*)sendAsc,len -1);
  return 1;
}

/**
*@function void motor_start_position_mode(void)
*@brief    ���õ������λ��ģʽ
*@param    void :��
*@return   ��
*/
void motor_start_position_mode(void)
{
  Circle_Write_Data(&sUart3TxCircleBuf_,(uint8_t*)readReg,sizeof(readReg));
}
/**
*@function void task_motor_control_init(void)
*@brief    ������������ʼ������
*@param    void :��
*@return   ��
*/
void task_motor_control_init(void)
{
  _TaskMotorControl.fun = task_motor_control;
  rs232RxFlag_ |= RS232_SET_MOTOR_PARAM;
}
/**
*@function void task_motor_control(void)
*@brief    ��������������
*@return   ��
*/
void task_motor_control(void)
{
  uint8_t bar = TASK_BAR_CMD;
  _TaskMotorControl.interval = 100;
  _TaskMotorControl.state = TASK_STATE_DELAY;
  if (_TaskMotorControl.progressBar == bar++)
  {
    if (motor_mode_home_control() == 1)
   // if (motor_mode_position_control() == 1)
      _TaskMotorControl.progressBar++;
  }
  else if (_TaskMotorControl.progressBar == bar++)
  {
    motor_tx_data_processing( 'g', MOTOR_REG_GET_ACTUAL_POSITION,0,0);
   // if (motorMonitoringStatus_ & MOTOR_REG_STATUS_ENABLE_NOT_ACTIVE)
    //  _TaskMotorControl.progressBar++;
    //_TaskMotorControl.state = TASK_STATE_SLEEP;
  }
  else if (_TaskMotorControl.progressBar == bar++)
  {
    motor_tx_data_processing( 'g', MOTOR_REG_GET_MONITORING_STATUS,0,0);
    if ((motorMonitoringStatus_ & MOTOR_REG_STATUS_ENABLE_NOT_ACTIVE) != MOTOR_REG_STATUS_ENABLE_NOT_ACTIVE)
    {
      _TaskMotorControl.progressBar++;
        _TaskMotorControl.interval = 3000;
    }
    //_TaskMotorControl.state = TASK_STATE_SLEEP;
  }
  else if (_TaskMotorControl.progressBar == bar++)
  {
      _TaskMotorControl.progressBar -= 2;
      printf( "%s %d\n","t",1);

   }
//   if (_TaskMotorControl.progressBar == bar++)
//   {
//     _TaskMotorControl.info = 0;
//     motor_set_position( 8000);
//     _TaskMotorControl.progressBar++;
//   }
//  else if (_TaskMotorControl.progressBar == bar++)
//   {
//     _TaskMotorControl.info++;
//     if (_TaskMotorControl.info > 2000)
//       _TaskMotorControl.progressBar--;
//     if (rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
//     {
//       _TaskMotorControl.progressBar++;
//     }
//   }
//  else if (_TaskMotorControl.progressBar == bar++)
//   {
//     motor_set_velocity( 300);
//     _TaskMotorControl.progressBar++;
//   }
//  else if (_TaskMotorControl.progressBar == bar++)
//   {
//     if (rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
//     {
//       _TaskMotorControl.progressBar++;
//     }
//   }
//   else if (_TaskMotorControl.progressBar == bar++)
//   {
//     Circle_Write_Data(&sUart3TxCircleBuf_,(uint8_t*)modePosition,sizeof(modePosition));
//     _TaskMotorControl.state = TASK_STATE_SLEEP;
//   }

}
/**
*@function uint8_t motor_tx_data_processing(char ins, char *reg, uintbuf, uint16_t len)
*@brief    �Ե���������ݴ���
*@param    ins :s:���� g:��ȡ
*@param    reg :�Ĵ�����ַ
*@param    buf :����
*@param    len :���ݳ���
*@return   1:�ɹ� 0:ʧ��
*/
uint8_t motor_tx_data_processing(char ins,char *reg,uint32_t sendData,uint16_t len)
{
  uint8_t length = 0;

  char trans[10] = "\0",sendAsc[20] = "\0";
  rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
  sendAsc[0] = ins;
  sendAsc[1] = ' ';
  strcat(sendAsc, reg);
  if (len > 0)
  {
    i32toa(sendData,trans,&length);
    strcat(sendAsc, trans);
//    length += sizeof(sendData);
  }

  strcat(sendAsc, sendReturn);
  length += sizeof(reg) + sizeof(sendReturn) + 2;
  Circle_Write_Data(&sUart3TxCircleBuf_,(uint8_t*)sendAsc,length + 2);
  return 1;
}
uint8_t motor_rx_data_processing(char *buf,uint16_t len)
{
//  char recData[10] = "\0";
  if ((buf[0] == 'o')&& (buf[1] == 'k'))
  {
    if ( (rs232RxFlag_ & RS232_SET_MOTOR_PARAM) != RS232_SET_MOTOR_PARAM)
      rs232RxFlag_ |= RS232_SET_MOTOR_PARAM;
  }
  else if ((buf[0] == 'v') && (buf[1] == ' '))
  {
    motorMonitoringStatus_ = atoin32(& buf[2], len - 3);
  }
  return 1;
}
uint8_t motor_mode_home_control(void)
{
  static uint8_t step = 0;
  if (rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
  {
    switch (step++)
    {
        case 0: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_HOMING_METHOD,513,1);break;
        case 1: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_SLOW_VELOCITY,40000,2);break;
        case 2: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_OFFSET,0,1);break;
        case 3: motor_tx_data_processing( 's', MOTOR_REG_SET_DESIRED_STATE,21,1);break;
        case 4:
        {
          rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
          printf( "%s %d\n","t",2);
          break;
        }
        case 5:
        {
          step = 0;
          return  1;
        }
        default:break;
    }
  }
  return 0;
}
uint8_t motor_mode_position_control(void)
{
  static uint8_t step = 0;
  if (rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
  {
    switch (step++)
    {
//        case 0: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_PROFILE_TYPE,"0",1);break;
//        case 1: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_POSITION,"100000",1);break;
//        case 2: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_VELOCITY,"100000",1);break;
//        case 3: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_ACCELERATION,"30000",1);break;
//        case 4: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_DECELERATION,"30000",1);break;
//        case 5: motor_tx_data_processing( 's', MOTOR_REG_SET_DESIRED_STATE,"21",1);break;
        case 6:
        {
          rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
          printf( "%s %d\n","t",1);
          break;
        }
        case 7:
        {
          step = 0;
          return  1;
        }
        default:break;
    }
  }
  return 0;
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





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
char rs232RxData[11];
char startP[] = "0";
char endP[] = "-300000";
char *runP;
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
  motorPauseFlag_ = MOTOR_PAUSE_PUT_RIGHT;
  eMotorControlMode_ = Robot_CMD_Homing;
  runP = endP;
}
/**
*@function void task_motor_control(void)
*@brief    ��������������
*@return   ��
*/
void task_motor_control(void)
{
  E_MOTOR_STATE sTempMotor;
  uint8_t recFalg;
  uint8_t bar = TASK_BAR_CMD;
  _TaskMotorControl.interval = 100;
  _TaskMotorControl.state = TASK_STATE_DELAY;
  if (_TaskMotorControl.progressBar == bar++)
  {
       _TaskMotorState.state = TASK_STATE_SLEEP;
       recFalg = motor_mode_control(&sRobotStatus_.runStatus);
      if (recFalg == 1) // �������
      {
        motorFlag_ &= ~MOTOR_STATE_COMMUNICATION_ERROR;
        _TaskMotorControl.progressBar++;
        _TaskMotorState.state = TASK_STATE_RUN;
      }
      else if (recFalg == 2) // ����ʧ��
      {
        motorFlag_ |= MOTOR_STATE_COMMUNICATION_ERROR;
        _TaskMotorControl.state = TASK_STATE_SLEEP; // ֹͣ����
      }
      else
        ;

  }
  else if (_TaskMotorControl.progressBar == bar++)
  {
    if ((motorPauseFlag_ & 0x7F) != 0)
    {
      sTempMotor = Robot_CMD_Stop;
      _TaskMotorState.state = TASK_STATE_SLEEP;
      recFalg = motor_mode_control(&sTempMotor);
     if (recFalg == 1) // �������
      {
        _TaskMotorControl.progressBar++;
        _TaskMotorState.state = TASK_STATE_RUN;
      }
    }
//  if ((eMotorControlMode_ == Robot_CMD_Homing)
//      && (motorFlag_ & MOTOR_STATE_HOMING_STATE)
//      && (motorFlag_ & MOTOR_STATE_MOVE_COMPLETE)) // ������ɣ�����λ��״̬
//  {
//    eMotorControlMode_ = Robot_CMD_Auto;
//    _TaskMotorControl.progressBar = 0;
//  }
    if (motorFlag_ & MOTOR_STATE_MOVE_COMPLETE) // �������
    {
      _TaskMotorControl.state = TASK_STATE_SLEEP;
      if ((sRobotStatus_.runStatus == Robot_CMD_Backward) || (sRobotStatus_.runStatus == Robot_CMD_Forward))
        sRobotStatus_.runStatus = Robot_CMD_Jog;  //�ص��ֶ�ģʽ
      else if ((strcmp(runP,recMotorStatus_[0]) == 0)
                && (sRobotStatus_.runStatus == Robot_CMD_Auto))
      {
        if (++sRobotStatus_.RunningCount < (sMotorParam_.runCount * 2))
        {
          if (runP == sMotorParam_.startPosition)
            runP = sMotorParam_.endPosition;
          else
            runP = sMotorParam_.startPosition;
          _TaskMotorControl.progressBar = 0;
          _TaskMotorControl.state = TASK_STATE_RUN;
        }
      }
      else
        ;
    }

  }
  else if (_TaskMotorControl.progressBar == bar++)
  {
    if (motorPauseFlag_ == MOTOR_PAUSE_PUT_RIGHT)
    {
      _TaskMotorState.state = TASK_STATE_SLEEP;
      if (sRobotStatus_.runStatus == Robot_CMD_Auto)
        sTempMotor = Robot_CMD_Start;
      else if (sRobotStatus_.runStatus == Robot_CMD_Homing)
        sTempMotor = Robot_CMD_HomingStart;
      recFalg = motor_mode_control(&sTempMotor);
      if (recFalg == 1) // �������
      {
        _TaskMotorControl.progressBar--;
        _TaskMotorState.state = TASK_STATE_RUN;
      }
    }
  }
}
/**
*@function void task_motor_state_init(void)
*@brief    �������״̬��ѯ����
*@param    void ����
*@return   ��
*/
void task_motor_state_init(void)
{
  _TaskMotorState.fun = task_motor_state;

}
/**
*@function void task_motor_state(void)
*@brief    ���״̬�������
*@return   ��
*/
void task_motor_state(void)
{
  static uint8_t state = 0;
  char *gerReg;
  uint8_t bar = TASK_BAR_CMD;
  switch (state) // ѡ����Ҫ��ȡ��״̬
  {
      case 0: gerReg = MOTOR_REG_GET_ACTUAL_POSITION;break;
      case 1: gerReg = MOTOR_REG_GET_MONITORING_STATUS;break;
      case 2: gerReg = MOTOR_REG_GET_TRAJECTORY_STATUS;break;
      case 3: gerReg = MOTOR_REG_GET_ACTUAL_VELOCITY;break;
      default:break;
  }
  _TaskMotorState.interval = 100;
  _TaskMotorState.state = TASK_STATE_DELAY;

  if (_TaskMotorState.progressBar == bar++)
  {
    motor_tx_data_processing( 'g', gerReg,0,0);
    _TaskMotorState.progressBar++;
  }
  else if (_TaskMotorState.progressBar == bar++)
  {
    if ( rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
    {
      memcpy(recMotorStatus_[state],rs232RxData,sizeof(rs232RxData));
      memset(rs232RxData,0,sizeof(rs232RxData));
      if (++state >= 4)
        state = 0;
      _TaskMotorState.progressBar--;
    }
  }
  motor_state_Processing();
}
/**
*@function void motor_state_Processing(void)
*@brief    ���״̬������
*@param    void ����
*@return   ��
*/
void motor_state_Processing(void)
{
  motorStatus_[1] = atoin32(recMotorStatus_[1],0);
  motorStatus_[2] = atoin32(recMotorStatus_[2],0);
  motorStatus_[0] = atoin32(recMotorStatus_[0],0);
  motorStatus_[3] = atoin32(recMotorStatus_[0],0);
  // �жϵ��enable��״̬
  if (motorStatus_ [1] & MOTOR_REG_STATUS_ENABLE_NOT_ACTIVE)
    motorPauseFlag_ |= MOTOR_PAUSE_ENABLE_NOT_ACTIVE;
  else
    motorPauseFlag_ &= ~MOTOR_PAUSE_ENABLE_NOT_ACTIVE;
  // �жϵ���˶����״̬
  if (motorStatus_ [1] & MOTOR_REG_STATUS_MOVE_COMPLETE)
    motorFlag_ &= ~MOTOR_STATE_MOVE_COMPLETE;
  else
    motorFlag_ |= MOTOR_STATE_MOVE_COMPLETE;
  // �жϵ������״̬
  if (motorStatus_[2] & MOTOR_REG_STATUS_HOMING_RUNING) // ������
    motorFlag_ &= ~MOTOR_STATE_HOMING_STATE;
  if (motorStatus_[2] & MOTOR_REG_STATUS_HOMING_SUCCESSFULLY) // �ɹ�
    motorFlag_ |= MOTOR_STATE_HOMING_STATE;

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
uint8_t motor_tx_data_processing(char ins,char *reg,char* sendData,uint16_t len)
{
  uint8_t length = 0;

  char sendAsc[20] = "\0";
  rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
  sendAsc[0] = ins;
  sendAsc[1] = ' ';
  strcat(sendAsc, reg);
  if (len > 0)
  {
    strcat(sendAsc, sendData);
    length += strlen(sendData);
  }

  strcat(sendAsc, sendReturn);
  length += strlen(reg) + strlen(sendReturn) + 2;
  Circle_Write_Data(&sUart3TxCircleBuf_,(uint8_t*)sendAsc,length + 1);
  return 1;
}
/**
*@function uint8_t motor_rx_data_processing(char *buf, uint16_t len)
*@brief    ����������ݴ������
*@param    buf �����յ�����
*@param    len ���������ݵĳ���
*@return   1������ɹ� 0������ʧ��
*/
uint8_t motor_rx_data_processing(char *buf,uint16_t len)
{
  if ((buf[0] == 'o')&& (buf[1] == 'k'))
  {
    if ( (rs232RxFlag_ & RS232_SET_MOTOR_PARAM) != RS232_SET_MOTOR_PARAM)
      rs232RxFlag_ |= RS232_SET_MOTOR_PARAM;
  }
  else if ((buf[0] == 'v') && (buf[1] == ' '))
  {
    memcpy(rs232RxData,&buf[2], len - 3);
    rs232RxFlag_ |= RS232_SET_MOTOR_PARAM;
  }
  return 1;
}
/**
*@function uint8_t motor_mode_control(E_MOTOR_STATE *mode)
*@brief    ���ģ�����ָ��
*@param    mode ��ģʽ�μ�E_MOTOR_STATE
*@return   1 ���ɹ� 0�������� 2��ͨ�ų�ʱ
*/
uint8_t motor_mode_control(E_MOTOR_STATE* mode)
{
  uint8_t reFlag = 0;
  static uint8_t step = 0;
  static uint8_t sendTime = 0;
  if ((++sendTime % 5) == 0)  // �ط�����
  {
    rs232RxFlag_ |= RS232_SET_MOTOR_PARAM;
    step--;
  }
  if (sendTime > 15)
  {
    step = 0;
    sendTime = 0;
    return 2;   // �ط�ʧ��
  }
  if (rs232RxFlag_ & RS232_SET_MOTOR_PARAM)
  {
    switch (*mode)
    {
        case Robot_CMD_Homing: reFlag = motor_mode_control_homing( step++);break;
        case Robot_CMD_Auto: reFlag = motor_mode_control_position( step++,*mode);break;
        case Robot_CMD_Start: reFlag = motor_mode_control_start(step++); break;
        case Robot_CMD_HomingStart:reFlag = motor_mode_control_home_start(step++); break;
        case Robot_CMD_Stop: reFlag = motor_mode_control_stop(step++); break;
        case Robot_CMD_Backward: reFlag = motor_mode_control_position(step++,*mode); break;
        case Robot_CMD_Forward: reFlag = motor_mode_control_position(step++, *mode); break;
        case Robot_CMD_Dot: reFlag = motor_mode_control_position(step++, *mode); break;
       // case Robot_CMD_Jog: reFlag = motor_mode_control_stop(step++); break;
        default:break;
    }
    sendTime = 0;
  }
  if (reFlag == 1)
    step = 0;
  return reFlag;
}
/**
*@function uint8_t motor_mode_control_homing(uint8_t step)
*@brief    �������ģʽ-homing�����㣩
*@param    step �����㲽��
*@return   1���ɹ� 0��������
*/
uint8_t motor_mode_control_homing(uint8_t step)
{
  switch (step)
  {
      case 0: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_HOMING_METHOD,"513",1);break;
      case 1: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_SLOW_VELOCITY,"40000",2);break;
      case 2: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_FAST_VELOCITY,"40000",2);break;
      case 3: motor_tx_data_processing( 's', MOTOR_REG_SET_HOME_OFFSET,"-26000",1);break;
      case 4: motor_tx_data_processing( 's', MOTOR_REG_SET_DESIRED_STATE,"21",1);break;
      case 5:
      {
        rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
        printf( "%s %d\n","t",2);
        break;
      }
      case 6:
        return  1;
      default:break;
  }
  return 0;
}
/**
*@function uint8_t motor_mode_control_position(uint8_t step)
*@brief    ���ģʽ����-λ��ģʽ
*@param    step �����Ʋ���
*@return   1���ɹ� 0��������
*/
uint8_t motor_mode_control_position(uint8_t step, E_MOTOR_STATE mode)
{
  uint8_t len;
  char stepTarget[11];
  uint32_t position = 0;
  if (mode == Robot_CMD_Dot)
    runP = sMotorParam_.targetPosition;
  else if (mode == Robot_CMD_Forward)
  {
     position = (motorStatus_[0] + sMotorParam_.step);
    i32toa(position, stepTarget, &len);
    runP = stepTarget;
  }
  else if (mode == Robot_CMD_Backward)
  {
     position = (motorStatus_[0] - sMotorParam_.step);
    i32toa(position, stepTarget, &len);
    runP = stepTarget;
  }
  switch (step)
    {
      case 0: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_PROFILE_TYPE,"0",1);break;
      case 1: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_POSITION, runP, 1); break;
      case 2: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_VELOCITY, sMotorParam_.speed, 1); break;
      case 3: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_ACCELERATION,"6000",1);break;
      case 4: motor_tx_data_processing( 's', MOTOR_REG_SET_POS_DECELERATION,"6000",1);break;
      case 5: motor_tx_data_processing( 's', MOTOR_REG_SET_DESIRED_STATE,"21",1);break;
      case 6:
      {
        rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
        printf( "%s %d\n","t",1);
        break;
      }
      case 7:
        return  1;
      default:break;
    }
  return 0;
}
/**
*@function uint8_t motor_mode_control_start(uint8_t step)
*@brief    �������ģʽ-��ʼ
*@param    step �����Ʋ���
*@return   ��
*/
uint8_t motor_mode_control_start(uint8_t step)
{
    switch (step)
    {
      case 0:
      {
        rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
        printf( "%s %d\n","t",1);
        break;
      }
      case 1:
        return  1;
      default:break;
    }
  return 0;
}
/**
*@function uint8_t motor_mode_control_home_start(uint8_t step)
*@brief    ������ƻ���ģʽ��ʼ
*@param    step �����Ʋ���
*@return   1���ɹ� 0��������
*/
uint8_t motor_mode_control_home_start(uint8_t step)
{
    switch (step)
    {
      case 0:
      {
        rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
        printf( "%s %d\n","t",2);
        break;
      }
      case 1:
        return  1;
      default:break;
    }
  return 0;
}
/**
*@function uint8_t motor_mode_control_stop(uint8_t step)
*@brief    �������ģʽ-ֹͣ
*@param    step ����
*@return   1���ɹ� 0��������
*/
uint8_t motor_mode_control_stop(uint8_t step)
{
    switch (step)
    {
      case 0:
      {
        rs232RxFlag_ &= ~RS232_SET_MOTOR_PARAM;
        printf( "%s %d\n","t",0);
        break;
      }
      case 1:
        return  1;
      default:break;
    }
  return 0;
}
/**
*@function void SetCAN(uint8_t state)
*@brief    ͨ��canopen���õ��
*@param    state��ENABLE / DISABLE
*@return   ��
*@date     2018/5/14
*/
void SetCAN(uint8_t state)
{
  if (state == DISABLE) // �رսڵ�
  {
    motor_stop_node();
  }
  else
  {
    motor_set_syn_cycle(); // ����ͬ������
    motor_start_syn();     // ����ͬ��
    motor_start_node();    // �����ڵ�
  }
}
/**
*@function void SetMotor(uint8_t state)
*@brief    ���õ�ѹenable��״̬
*@param    state��ENABLE/DISABLE
*@return   ��
*@date     2018/5/14
*/
void SetMotor(uint8_t state)
{
  if (state == DISABLE)
    GPIO_ResetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
  else
    GPIO_SetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
}

/**
*@function uint8_t GetMotorState(uint8_t *buf, uint8_t len)
*@brief    ��ȡ���״̬,
*@param    buf:״̬����
*@param    len:״̬���ݳ���
*@return   1:�ɹ� 0:ʧ��
*@date     2018/5/14
*/
uint8_t GetMotorState(uint8_t *buf,uint8_t len)
{
  return motor_get_state(buf,len);
}
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_battery.c
* @author       zhou
* @version      V1.0
* @date         2018/5/17
* @brief        电池接口程序文件
**************************************************************************************************
*/
#include "include.h"


#define         CRC_16_POLYNOMIALS  0xa001
/* CRC 高位字节值表 */
uint8_t auchCRCH[] = {0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
   0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
   0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80,
  0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
  0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
        };
/* CRC低位字节值表*/
uint8_t auchCRCL[] = {
      0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07,
  0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE,
  0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19,
  0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C,
  0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13,
  0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2,
  0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD,
  0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8,
  0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F,
  0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6,
  0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61,
  0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64,
  0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B,
  0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A,
  0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75,
  0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70,
  0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57,
  0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E,
  0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49,
   0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C,
  0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43,
  0x83, 0x41, 0x81, 0x80, 0x40
        };

// X^16 +X^15 +X^2+1 ?à????
uint16_t Check_CRC16(uint8_t* pchMsg,uint8_t wDataLen)
{
    uint8_t i, chChar;
    uint16_t wCRC = 0xFFFF;
    while (wDataLen--)
    {
        chChar = *pchMsg++;
        wCRC ^= (uint16_t) chChar;
        for (i = 0; i < 8; i++)
        {
            if (wCRC & 0x0001)
                wCRC = (wCRC >> 1) ^ CRC_16_POLYNOMIALS;
            else
                wCRC >>= 1;
       }
   }
   return wCRC;
}


//校验函数
uint16_t crc16(uint8_t* puchMsg, uint16_t usDataLen)
{
  uint16_t clc;
  uint16_t i = 0;
  uint8_t uchCRCHi = 0xFF; /* 高CRC字节初始化 */
  uint8_t uchCRCLo = 0xFF; /* 低CRC 字节初始化 */
  uint8_t uIndex; /* CRC循环中的索引 */
  while (usDataLen-- > 0) /* 传输消息缓冲区 */
  {
      uIndex = (uint8_t)(uchCRCHi ^ puchMsg[i++]); /* 计算CRC */
      uchCRCHi = (uint8_t)(uchCRCLo ^ auchCRCH[uIndex]);
      uchCRCLo = auchCRCL[uIndex];
  }
  clc = (uint16_t)(uchCRCHi << 8 | uchCRCLo);
  return (clc);

}

void battery_tx_processing(uint8_t addr,uint8_t funCode, uint8_t regAddr)
{
  uint16_t crcData = 0;
  uint8_t sendData[9];
  sendData[0] = addr;
  sendData[1] = funCode;
  sendData[2] = 0x00;
  sendData[3] = regAddr;
  sendData[4] = 0x00;
  sendData[5] = 0x01;
  crcData = crc16(sendData,6);
  sendData[7] = (uint8_t)(crcData & 0xFF);
  sendData[6] = (uint8_t)((crcData >> 8) & 0xFF);
  Circle_Write_Data(&sUart1TxCircleBuf_,sendData,9);

}
void battery_rx_processing(uint8_t *buf, uint16_t len)
{
  if ((buf[0] == 0x01) && (buf[1] == 0x03))
  {
    if (queryRegAddr_ == BATTERY_REG_VOTAGE)
    {
      sBattery_.batteryVoltage = ((buf[3] << 8) & 0xFF00) + (buf[4] & 0xFF);
    }
    else if (queryRegAddr_ == BATTERY_REG_VOTAGE_PERCENT)
    {
      sBattery_.batteryPercent = ((buf[3] << 8) & 0xFF00) + (buf[4] & 0xFF);
    }
    else if (queryRegAddr_ == BATTERY_REG_CURRENT)
    {
      sBattery_.batteryCurrent = ((buf[3] << 8) & 0xFF00) + (buf[4] & 0xFF);
    }
    batteryStateFlag_ |= BATTERY_FLAG_GET_PARAM;
  }
}
void battery_control(uint8_t regAddr)
{
  batteryStateFlag_ &= ~BATTERY_FLAG_GET_PARAM;
  battery_tx_processing(BATTERY_ADDR,BATTERY_FUN_CODE,regAddr);
}
void task_battery_init(void)
{
  _TaskBattery.fun = task_battery;
  batteryStateFlag_ |= BATTERY_FLAG_GET_PARAM;
  _TaskBattery.state    = TASK_STATE_RUN;
}
void task_battery(void)
{
  static uint8_t i = 0;
  _TaskBattery.interval = 1000;
  _TaskBattery.state    = TASK_STATE_DELAY;
  if (batteryStateFlag_ & BATTERY_FLAG_GET_PARAM)
  {
    switch (i++)
    {
        case 0:queryRegAddr_ = BATTERY_REG_VOTAGE;break;
        case 1:queryRegAddr_ = BATTERY_REG_VOTAGE_PERCENT;break;
        case 2:queryRegAddr_ = BATTERY_REG_CURRENT;break;
    }
    if (i >= 3)
      i = 0;
    battery_control(queryRegAddr_ );
  }
  sRobotStatus_.CurrentVoltage = sBattery_.batteryVoltage;
  sRobotStatus_.CurrentAmp = sBattery_.batteryCurrent;
  sRobotStatus_.ControlSystemEnergy = sBattery_.batteryPercent;
  sRobotStatus_.DynamicSystemEnergy = sBattery_.batteryPercent;
  robot_tx_data_conversion(&sRobotStatus_);
}


uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd)
{
  uint8_t len;
  // 读取参数
  sMotorParam_.eComand = get_robot_command(sRobotCmd->Command); // 获取命令
  if (sRobotStatus_.runStatus == sMotorParam_.eComand) // 相同命令返回
    return 1;
  else if (sMotorParam_.eComand == Robot_CMD_Stop) // 其它任何状态都可以切换到stop
    sRobotStatus_.runStatus = Robot_CMD_Stop;
  else if (sRobotStatus_.runStatus == Robot_CMD_Stop) // stop状态
  {
      if (sMotorParam_.eComand == Robot_CMD_Set) // stop状态可设置
      {
        i32toa(sRobotCmd->Speed * MOTOR_COUNTS_VELOCITY, sMotorParam_.speed, &len); // 速度
        i32toa(sRobotCmd->StartPosition * MOTOR_COUNTS_POSITION, sMotorParam_.startPosition, &len); // 开始位置
        i32toa(sRobotCmd->EndPosition * MOTOR_COUNTS_POSITION, sMotorParam_.endPosition, &len); // 结束位置
        i32toa(sRobotCmd->TargetPosition * MOTOR_COUNTS_POSITION, sMotorParam_.targetPosition, &len); // 目标位置
        sMotorParam_.step = sRobotCmd->Step ;                              // 步长
        sMotorParam_.eWorkMode = get_robot_run_mode(sRobotCmd->WorkMode);  // 工作模式
      }
      else if ((sMotorParam_.eComand == Robot_CMD_Auto)  //stop状态可切换状态
              ||(sMotorParam_.eComand == Robot_CMD_Jog)
              ||(sMotorParam_.eComand == Robot_CMD_Dot)
              ||(sMotorParam_.eComand == Robot_CMD_Homing)
              )
      {
        sRobotStatus_.runStatus = sMotorParam_.eComand;
      }

  }
  else if (((sMotorParam_.eComand == Robot_CMD_Forward)   // 手动模式处理
          || (sMotorParam_.eComand == Robot_CMD_Backward))
          && (sRobotStatus_.runStatus == Robot_CMD_Jog)
          )
  {
    sRobotStatus_.runStatus = sMotorParam_.eComand;
  }
  else
    return 1;

  // 停止操作
  _TaskMotorControl.progressBar = 0;
  _TaskMotorControl.state = TASK_STATE_RUN;
  return 1;
}
void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus)
{
  ROBOStatus_TypeDef recRobotStatus;
  set_robot_command(sStatus->runStatus,recRobotStatus.RunStatus);
  strcpy(recRobotStatus.CurrentTime, "2017-10-13 17:27:30\0");
  recRobotStatus.CurrentPositiont = motorStatus_[0];
  recRobotStatus.CurrentSpeed = atoin32(sStatus->CurrentSpeed,0);
  recRobotStatus.RunningCount = sStatus->RunningCount;
  recRobotStatus.CurrentTemp = sStatus->CurrentTemp;
  recRobotStatus.CurrentVoltage = (float)(sStatus->CurrentVoltage / 100);
  recRobotStatus.CurrentAmp = (float)(sStatus->CurrentAmp/100);
  recRobotStatus.CurrentDir = sStatus->CurrentDir;

  recRobotStatus.ControlSystemEnergy = (float)(sStatus->ControlSystemEnergy/100);
  recRobotStatus.DynamicSystemEnergy = recRobotStatus.ControlSystemEnergy;

}

E_MOTOR_STATE get_robot_command(char *buf)
{
  if (strcmp(buf, "Auto") == 0)
    return Robot_CMD_Auto;
  else if (strcmp(buf, "Set") == 0)
    return Robot_CMD_Set;
  else if (strcmp(buf, "Jog") == 0)
    return Robot_CMD_Jog;
  else if (strcmp(buf, "Stop") == 0)
    return Robot_CMD_Stop;
  else if (strcmp(buf, "Forward") == 0)
    return Robot_CMD_Forward;
  else if (strcmp(buf, "Backward") == 0)
    return Robot_CMD_Backward;
  else if (strcmp(buf, "Dot") == 0)
    return Robot_CMD_Dot;
  else if (strcmp(buf, "Homing") == 0)
    return Robot_CMD_Homing;
  else
    return Robot_CMD_Error;
}
E_WORK_MODE get_robot_run_mode(char *buf)
{
  if (strcmp(buf, "RealTime") == 0)
    return Robot_Work_RealTime;
  else if (strcmp(buf, "Regular") == 0)
    return Robot_Work_Regular;
  else if (strcmp(buf, "Daily") == 0)
    return Robot_Work_Daily;
  else
    return Robot_Work_Error;
}
void set_robot_command(E_MOTOR_STATE eRobotStatus ,char *buf)
{

  if (eRobotStatus ==  Robot_CMD_Auto)
    strcpy(buf,"Auto\0");
  else if (eRobotStatus ==  Robot_CMD_Set)
    strcpy(buf, "Set\0");
  else if (eRobotStatus ==  Robot_CMD_Jog)
    strcpy(buf, "Jog\0");
  else if (eRobotStatus ==  Robot_CMD_Stop)
    strcpy(buf, "Stop\0");
  else if (eRobotStatus ==  Robot_CMD_Forward)
    strcpy(buf, "Forward\0");
  else if (eRobotStatus ==  Robot_CMD_Backward)
    strcpy(buf, "Backward\0");
  else if (eRobotStatus ==  Robot_CMD_Dot)
    strcpy(buf, "Dot\0");
  else if (eRobotStatus ==  Robot_CMD_Homing)
    strcpy(buf, "Homing\0");
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_config.h
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        配置文件头文件
**************************************************************************************************
*/

#ifndef  _APP_CONFIG_H_
#define  _APP_CONFIG_H_
#include "include.h"
/********* 宏定义 *************/

/********* 变量定义 *************/
typedef struct
{
  uint8_t cmd;
  uint8_t configCMD;
  uint8_t param0;
  uint8_t param1;
  uint8_t param2;
  uint8_t param3;
  uint8_t param4;
  uint8_t param5;
  uint8_t param6;
  uint8_t param7;
  uint8_t param8;
  uint8_t param9;
}sCONFIG_INSTRUCT;
extern uint8_t version_[16];
/********* 函数定义 *************/
void task_config_init(void);
void task_config(void);
void ConfigSendPackage(uint8_t instruct,uint8_t *buf,uint8_t len,uint8_t sendType);

void GetRemote(void);

void SetIP(void); // 设置IP地址
void GetIP(void);

void SetGateWay(void);
void GetGateWay(void);

void SetPort(void);
void GetPort(void);

void SetMACAddress(void);
void GetMACAddress(void);

void GetVersion(void);
void GetSN(void);
void GetPlatform(void);

void ResetFactory(void);
void RestartBoard(void);
#endif



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/






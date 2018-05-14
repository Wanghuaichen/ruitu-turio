/**
*************************(C) COPYRIGHT 2017 ********************************************
* @file         app_config.c
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        配置文件
**************************************************************************************************
*/
#include "include.h"


void set_platform(void);
uint8_t version_[16] = {'R','I','O','-','V','1','0','0','-','1','8','0','1','1','0','0'};
/**
*@brief
*@param
*@return
*/
void task_config_init(void)
{
    _TaskConfig.fun     = task_config;
    _TaskConfig.rxBuf   = &sParamConfig_;
    _TaskConfig.command = CMD_TASK_CONFIG;
}

/**
*@brief
*@param
*@return
*/
void task_config(void)
{
    switch(sParamConfig_.configCMD)
    {

    }
    memset(&sParamConfig_,0,sizeof(sParamConfig_));
    _TaskConfig.state = TASK_STATE_SLEEP;
}
///*--------------------开启上传遥控编码----------------*/
///**
//*@brief     开启一次上传遥控编码，通过网口
//*@param     无
//*@return  无
//*/
//void GetRemote(void)
//{
//  remoteUpFlag_ = _TaskConfig.port;
//}
/*---------------------IP设置--------------------------*/
/**
*@brief   设置IP地址
*@param   无
*@return  无
*/
//void SetIP(void)
//{
//  Param_now.local_ip2[0] = sParamConfig_.param0; // 取下发的4位IP
//  Param_now.local_ip2[1] = sParamConfig_.param1;
//  Param_now.local_ip2[2] = sParamConfig_.param2;
//  Param_now.local_ip2[3] = sParamConfig_.param3;
//  Param_SAVE();   // 保存
//
//  GetIP();  // 上传设置完成的IP
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   获取IP并上传
*@param   无
*@return  无
*/
void GetIP(void)
{

}

///*------------------------网关设置-------------------------*/
///**
//*@brief     设置网关
//*@param     无
//*@return  无
//*/
//void SetGateWay(void)
//{
//  Param_now.gateway2[0] = sParamConfig_.param0; // 取下发的4位IP
//  Param_now.gateway2[1] = sParamConfig_.param1;
//  Param_now.gateway2[2] = sParamConfig_.param2;
//  Param_now.gateway2[3] = sParamConfig_.param3;
//  Param_SAVE();   // 保存
//
//  GetGateWay();   // 上传设置完成的IP
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   获取网关并上传
*@param   无
*@return  无
*/
void GetGateWay(void)
{

}
///*------------------端口设置---------------------------------*/
///**
//*@brief     设置端口
//*@param     无
//*@return  无
//*/
//void SetPort(void)
//{
//  Param_now.local_port = ((sParamConfig_.param1 << 8) | (sParamConfig_.param0));
//  Param_SAVE();   // 保存
//  GetPort();
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   获取端口并上传
*@param   无
*@return  无
*/
void GetPort(void)
{

}
///*------------------------MAC地址-------------------------------*/
///**
//*@brief     设置MAC地址
//*@param     无
//*@return  无
//*/
//void SetMACAddress(void)
//{
//  Param_now.mac2[0] = sParamConfig_.param0;
//  Param_now.mac2[1] = sParamConfig_.param1;
//  Param_now.mac2[2] = sParamConfig_.param2;
//  Param_now.mac2[3] = sParamConfig_.param3;
//  Param_now.mac2[4] = sParamConfig_.param4;
//  Param_now.mac2[5] = sParamConfig_.param5;
//
//  Param_SAVE();   // 保存
//
//  GetMACAddress();   // 上传设置完成的IP
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   获取MAC地址并上传
*@param   无
*@return  无
*/
void GetMACAddress(void)
{

}
/*---------------------获取站台编号---------------------*/
/**
*@brief   获取站台编号并上传：拨码开关值
*@param   无
*@return  无
*/
void GetPlatform(void)
{

}
void set_platform(void)
{

}

/*----------------------版本号----------------------------*/
/**
*@brief   获取版本号并上传,V为正式版，T为测试版，F为工厂测试版，B为分支版，单独功能测试而做
*@param   无
*@return  无
*/
void GetVersion(void)
{
   // tx_data_processing(version_,16,CMD_GET_VER,_TaskConfig.port);
}
/*----------------------SN码-------------------------------*/
/**
*@brief   获取SN号并上传
*@param   无
*@return  无
*/
void GetSN(void)
{
    uint8_t snData[12];
    snData[0]   = *(char*)(0x1FFFF7F3); // 获取SN码，存在ST自身的Flash中
    snData[1]   = *(char*)(0x1FFFF7F2);
    snData[2]   = *(char*)(0x1FFFF7F1);
    snData[3]   = *(char*)(0x1FFFF7F0);
    snData[4]   = *(char*)(0x1FFFF7EF);
    snData[5]   = *(char*)(0x1FFFF7EE);
    snData[6]   = *(char*)(0x1FFFF7ED);
    snData[7]   = *(char*)(0x1FFFF7EC);
    snData[8]   = *(char*)(0x1FFFF7EB);
    snData[9]   = *(char*)(0x1FFFF7EA);
    snData[10]  = *(char*)(0x1FFFF7E9);
    snData[11]  = *(char*)(0x1FFFF7E8);

  //  tx_data_processing(snData,12,CMD_GET_SN,_TaskConfig.port);
}
///*---------------出厂设置---------------------*/
///**
//*@brief     恢复出厂设置
//*@param     无
//*@return  无
//*/
//void ResetFactory(void)
//{
//  uint8_t empty[2];
//  Param_Init();
//  Param_READ();
//  ConfigSendPackage(CMD_FACTORY_SET,empty,0,_TaskConfig.port);
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}
/*----------------重启--------------------------*/
/**
*@brief   重启电路板，通过看门狗超时
*@param   无
*@return  无
*/
void RestartBoard(void)
{
    SystemReset();
}
/*------------------------发送打包函数-----------------------*/
/**
*@brief   统一发送打包函数
*@param   instruct:指令
*@return  无
*/
//void ConfigSendPackage(uint8_t instruct,uint8_t *buf,uint8_t len,uint8_t sendType)
//{
//  uUINT16 crc16;
//  uint8_t i;
//  uint8_t sendData[30];
//  sendData[0] = 0xFD;      // 包头
//  sendData[1] = 0xF7;
//  sendData[2] = cmdTick_++;   // 指令计数
//  sendData[3] = len + 7;          // 数据包长度
//  sendData[4] = instruct;     // 指令码
//  for (i = 0; i < len; i++)   // 数据
//  {
//      sendData[5 + i] = buf[i];
//  }
//  crc16.word = CRC16(sendData,len + 5);        // 校验
//  sendData[len + 5] = crc16.HL.H;
//  sendData[len + 6] = crc16.HL.L;
//  if (sendType == COM_TYPE_UART3)
//  {
//      SetTxDMA(&sUart3TxDMA_,sendData,len + 7);   // 存入发送缓存
//      _TaskUart3Tx.state   = TASK_STATE_RUN;      // 开启发送
//  }
//  if (sendType == COM_TYPE_UART2)
//  {
//      SetTxDMA(&sUart5TxDMA_,sendData,len + 7);   // 存入发送缓存
//      _TaskUart2Tx.state   = TASK_STATE_RUN;      // 开启发送
//  }
//  if (sendType == COM_TYPE_NET)
//  {
//      send(0,sendData,len + 7);
//  }
//}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





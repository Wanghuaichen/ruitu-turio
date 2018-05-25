/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         Param.c
* @author       zhou
* @version      V1.0
* @date         2017-06-16
* @brief        参数设置头文件
**************************************************************************************************
*/
#include "include.h"
/**
*@function void param_default_set(void)
*@brief    默认初始化参数设置
*@param    void ：空
*@return   无
*/
void param_default_set(void)
{
  // 本机IP设置
  sDefaultNetConfig_.localIP[0] = 192;
  sDefaultNetConfig_.localIP[1] = 168;
  sDefaultNetConfig_.localIP[2] = 1;
  sDefaultNetConfig_.localIP[3] = 19;
  // 本机网关设置
  sDefaultNetConfig_.gateWay[0] = 192;
  sDefaultNetConfig_.gateWay[1] = 168;
  sDefaultNetConfig_.gateWay[2] = 1;
  sDefaultNetConfig_.gateWay[3] = 1;
  // 本机mac设置
  sDefaultNetConfig_.macAddress[0] = 0x1A;
  sDefaultNetConfig_.macAddress[1] = 0x2A;
  sDefaultNetConfig_.macAddress[2] = 0x3A;
  sDefaultNetConfig_.macAddress[3] = 0x4A;
  sDefaultNetConfig_.macAddress[4] = 0x5A;
  sDefaultNetConfig_.macAddress[5] = 0x6A;
  // 本机子网掩码设置
  sDefaultNetConfig_.subnetMask[0] = 255;
  sDefaultNetConfig_.subnetMask[1] = 255;
  sDefaultNetConfig_.subnetMask[2] = 255;
  sDefaultNetConfig_.subnetMask[3] = 0;
  // 本机端口号设置
  sDefaultNetConfig_.localPort = 502;
  //传感器任务数据调协
  segmentNum_ = 0;      // 段数，未使用，表示robot所处轨道位置
  irLocationNum_ = 0;   // 经过轨道孔时，定位传感器记录的经过距离
  homingDistance_ = 28; // 回零点距离，孔距超过此值，即进行发送回零信号
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





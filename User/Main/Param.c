/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         Param.c
* @author       zhou
* @version      V1.0
* @date         2017-06-16
* @brief        ��������ͷ�ļ�
**************************************************************************************************
*/
#include "include.h"
/**
*@function void param_default_set(void)
*@brief    Ĭ�ϳ�ʼ����������
*@param    void ����
*@return   ��
*/
void param_default_set(void)
{
  // ����IP����
  sDefaultNetConfig_.localIP[0] = 192;
  sDefaultNetConfig_.localIP[1] = 168;
  sDefaultNetConfig_.localIP[2] = 1;
  sDefaultNetConfig_.localIP[3] = 19;
  // ������������
  sDefaultNetConfig_.gateWay[0] = 192;
  sDefaultNetConfig_.gateWay[1] = 168;
  sDefaultNetConfig_.gateWay[2] = 1;
  sDefaultNetConfig_.gateWay[3] = 1;
  // ����mac����
  sDefaultNetConfig_.macAddress[0] = 0x1A;
  sDefaultNetConfig_.macAddress[1] = 0x2A;
  sDefaultNetConfig_.macAddress[2] = 0x3A;
  sDefaultNetConfig_.macAddress[3] = 0x4A;
  sDefaultNetConfig_.macAddress[4] = 0x5A;
  sDefaultNetConfig_.macAddress[5] = 0x6A;
  // ����������������
  sDefaultNetConfig_.subnetMask[0] = 255;
  sDefaultNetConfig_.subnetMask[1] = 255;
  sDefaultNetConfig_.subnetMask[2] = 255;
  sDefaultNetConfig_.subnetMask[3] = 0;
  // �����˿ں�����
  sDefaultNetConfig_.localPort = 502;
  //�������������ݵ�Э
  segmentNum_ = 0;      // ������δʹ�ã���ʾrobot�������λ��
  irLocationNum_ = 0;   // ���������ʱ����λ��������¼�ľ�������
  homingDistance_ = 28; // �������룬�׾೬����ֵ�������з��ͻ����ź�
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





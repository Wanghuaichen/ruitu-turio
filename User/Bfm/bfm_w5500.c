/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_w5500.c
* @author       zhou
* @version      V1.0
* @date         2018/5/4
* @brief        w5500�����ļ�
**************************************************************************************************
*/
#include "include.h"
#include "w5500_config.h"

void w5500_config_ip(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setSIPR(configData->localIP);
  else
    getSIPR(configData->localIP);
}

void w5500_config_gateway(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setGAR(configData->gateWay);
  else
    getGAR(configData->gateWay);
}

void w5500_config_subnetMask(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setSUBR(configData->subnetMask);
  else
    getSUBR(configData->subnetMask);
}
void w5500_config_macAddress(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setSHAR(configData->macAddress);
  else
    getSHAR(configData->macAddress);
}

void w5500_start_up(void)
{
  W5500_RESET_HIGH;
}
void w5500_turn_off(void)
{
  W5500_RESET_LOW;
}
void w5500_restart(void)
{
  W5500_RESET_LOW;
  delay_us( 600);
  W5500_RESET_HIGH;
  delay_us( 16000);
}

///**
//*@brief   ����W5500��IP��ַ
//*@param   ��
//*@return  ��
//*/
//void set_w5500_ip(void)
//{
//  uint8_t local_ip[4],subnet[4],gateway[4];
//  if(SPIx==1)
//  {
//   /*���ƶ����������Ϣ�����ýṹ��*/
//    memcpy(ConfigMsg.mac, Param.mac1, 6);
//    memcpy(ConfigMsg.lip,Param_now.local_ip1,4);
//    memcpy(ConfigMsg.sub,Param_now.subnet1,4);
//    memcpy(ConfigMsg.gw,Param_now.gateway1,4);
//    memcpy(ConfigMsg.dns,Param_now.dns_server1,4);
//  }
//  if(SPIx==2)
//  {
//   /*���ƶ����������Ϣ�����ýṹ��*/
//    memcpy(ConfigMsg.mac, Param_now.mac2, 6);
//    memcpy(ConfigMsg.lip,Param_now.local_ip2,4);
//    memcpy(ConfigMsg.sub,Param_now.subnet2,4);
//    memcpy(ConfigMsg.gw,Param_now.gateway2,4);
//    memcpy(ConfigMsg.dns,Param_now.dns_server2,4);
//  }

//  /*����������Ϣ��������Ҫѡ��*/
//  ConfigMsg.sw_ver[0]=FW_VER_HIGH;
//  ConfigMsg.sw_ver[1]=FW_VER_LOW;

//  /*��IP������Ϣд��W5500��Ӧ�Ĵ���*/
//  setSUBR(ConfigMsg.sub);
//  setGAR(ConfigMsg.gw);
//  setSIPR(ConfigMsg.lip);
//  getSIPR (local_ip);
////    printf(" W5500 IP��ַ   : %d.%d.%d.%d\r\n", local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
//  getSUBR(subnet);
////  printf(" W5500 �������� : %d.%d.%d.%d\r\n", subnet[0],subnet[1],subnet[2],subnet[3]);
//  getGAR(gateway);
////  printf(" W5500 ����     : %d.%d.%d.%d\r\n", gateway[0],gateway[1],gateway[2],gateway[3]);
//}

/**
*@brief   ����W5500��MAC��ַ
*@param   ��
*@return  ��
*/
void set_w5500_mac(S_W5500_CONFIG *configData)
{

  setSHAR(configData->macAddress); /**/
}

/**
*@brief   д��һ��8λ���ݵ�W5500
*@param   addrbsb: д�����ݵĵ�ַ
*@param   data��д���8λ����
*@return  ��
*/
void w5500_write_byte( uint32_t addrbsb,  uint8_t data)
{
   uint8_t getByte = 0;
   W5500_CS_LOW;
   W5500_SEND_GET_BYTE( (addrbsb & 0x00FF0000)>>16,&getByte);
   W5500_SEND_GET_BYTE( (addrbsb & 0x0000FF00)>> 8,&getByte);
   W5500_SEND_GET_BYTE( (addrbsb & 0x000000F8) + 4,&getByte);
   W5500_SEND_GET_BYTE(data,&getByte);
   W5500_CS_HIGH;
}

/**
*@brief   ��W5500����һ��8λ����
*@param   addrbsb: д�����ݵĵ�ַ
*@param   data����д��ĵ�ַ����ȡ����8λ����
*@return  ��
*/
uint8_t w5500_read_byte(uint32_t addrbsb)
{
   uint8_t getByte = 0;
   W5500_CS_LOW;
   W5500_SEND_GET_BYTE( (addrbsb & 0x00FF0000)>>16,&getByte);
   W5500_SEND_GET_BYTE( (addrbsb & 0x0000FF00)>> 8,&getByte);
   W5500_SEND_GET_BYTE( (addrbsb & 0x000000F8),&getByte)    ;
   W5500_SEND_GET_BYTE(0x00,&getByte);
   W5500_CS_HIGH;
   return getByte;
}

/**
*@brief   ��W5500д��len�ֽ�����
*@param   addrbsb: д�����ݵĵ�ַ
*@param   buf��д���ַ���
*@param   len���ַ�������
*@return  len�������ַ�������
*/
uint16_t w5500_write_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len)
{
  uint8_t getByte = 0;
  uint16_t idx = 0;
  //if(len == 0) printf("Unexpected2 length 0\r\n");
  W5500_CS_LOW;
  W5500_SEND_GET_BYTE( (addrbsb & 0x00FF0000)>>16,&getByte);
  W5500_SEND_GET_BYTE( (addrbsb & 0x0000FF00)>> 8,&getByte);
  W5500_SEND_GET_BYTE( (addrbsb & 0x000000F8) + 4,&getByte);
  for(idx = 0; idx < len; idx++)
  {
   W5500_SEND_GET_BYTE(buf[idx],&getByte);
  }
  W5500_CS_HIGH;
  return len;
}

/**
*@brief   ��W5500����len�ֽ�����
*@param   addrbsb: ��ȡ���ݵĵ�ַ
*@param   buf����Ŷ�ȡ����
*@param   len���ַ�������
*@return  len�������ַ�������
*/
uint16_t w5500_read_buf(uint32_t addrbsb, uint8_t* buf,uint16_t len)
{
  uint8_t getByte = 0;
  uint16_t idx = 0;
  if(len == 0)
  {
   // printf("Unexpected2 length 0\r\n");
  }
  W5500_CS_LOW;
  W5500_SEND_GET_BYTE( (addrbsb & 0x00FF0000)>>16,&getByte);
  W5500_SEND_GET_BYTE( (addrbsb & 0x0000FF00)>> 8,&getByte);
  W5500_SEND_GET_BYTE( (addrbsb & 0x000000F8),&getByte);
  for(idx = 0; idx < len; idx++)
  {
    W5500_SEND_GET_BYTE(0x00,&buf[idx]);
  }
  W5500_CS_HIGH;
  return len;
}





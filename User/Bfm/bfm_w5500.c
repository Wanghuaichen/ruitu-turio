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
/**
*@function void w5500_config_ip(S_W5500_CONFIG *configData, uint8_t readOrWrite)
*@brief    ��ȡ������w5500IP
*@param    configData �����û��ȡֵ
*@param    readOrWrite ��W5500_WRITE_PARAMETER:���ò��� W5500_READ_PARAMETER����ȡ����
*@return   ��
*/
void w5500_config_ip(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setSIPR(configData->localIP);
  else
    getSIPR(configData->localIP);
}
/**
*@function void w5500_config_gateway(S_W5500_CONFIG *configData, uint8_t readOrWrite)
*@brief    ������д����
*@param    configData �����û��߶�ȡֵ
*@param    readOrWrite ��W5500_WRITE_PARAMETER���������ݡ�W5500_READ_PARAMETER����ȡ����
*@return   ��
*/
void w5500_config_gateway(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setGAR(configData->gateWay);
  else
    getGAR(configData->gateWay);
}
/**
*@function void w5500_config_subnetMask(S_W5500_CONFIG *configData, uint8_t readOrWrite)
*@brief    w5500������������
*@param    configData �����û��ȡֵ
*@param    readOrWrite ��W5500_WRITE_PARAMETER���������ݡ�W5500_READ_PARAMETER����ȡ����
*@return   ��
*/
void w5500_config_subnetMask(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setSUBR(configData->subnetMask);
  else
    getSUBR(configData->subnetMask);
}
/**
*@function void w5500_config_macAddress(S_W5500_CONFIG *configData, uint8_t readOrWrite)
*@brief    w5500���û��߶�ȡmac��ַ
*@param    configData �����û��ȡֵ
*@param    readOrWrite ��W5500_WRITE_PARAMETER���������ݡ�W5500_READ_PARAMETER����ȡ����
*@return   ��
*/
void w5500_config_macAddress(S_W5500_CONFIG *configData, uint8_t readOrWrite)
{
  if (readOrWrite == W5500_WRITE_PARAMETER)
    setSHAR(configData->macAddress);
  else
    getSHAR(configData->macAddress);
}
/**
*@function void w5500_start_up(void)
*@brief    ����w5500
*@param    void ����
*@return   ��
*/
void w5500_start_up(void)
{
  W5500_RESET_HIGH;
}
/**
*@function void w5500_turn_off(void)
*@brief    �ر�w5500
*@param    void ����
*@return   ��
*/
void w5500_turn_off(void)
{
  W5500_RESET_LOW;
}
/**
*@function void w5500_restart(void)
*@brief    w5500���� ����Ҫ��ʱʱ��������ɷ��ڿ�ʼ��
*@param    void ����
*@return   ��
*/
void w5500_restart(void)
{
  W5500_RESET_LOW;
  delay_us( 600);
  W5500_RESET_HIGH;
  delay_us( 16000);
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




/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/






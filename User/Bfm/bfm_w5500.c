/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_w5500.c
* @author       zhou
* @version      V1.0
* @date         2018/5/4
* @brief        w5500配置文件
**************************************************************************************************
*/
#include "include.h"
#include "w5500_config.h"
/**
*@function void w5500_config_ip(S_W5500_CONFIG *configData, uint8_t readOrWrite)
*@brief    读取或配置w5500IP
*@param    configData ：配置或读取值
*@param    readOrWrite ：W5500_WRITE_PARAMETER:配置参数 W5500_READ_PARAMETER：读取参数
*@return   无
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
*@brief    读或者写网关
*@param    configData ：配置或者读取值
*@param    readOrWrite ：W5500_WRITE_PARAMETER：配置数据。W5500_READ_PARAMETER：读取参数
*@return   无
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
*@brief    w5500配置子网掩码
*@param    configData ：配置或读取值
*@param    readOrWrite ：W5500_WRITE_PARAMETER：配置数据。W5500_READ_PARAMETER：读取参数
*@return   无
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
*@brief    w5500配置或者读取mac地址
*@param    configData ：配置或读取值
*@param    readOrWrite ：W5500_WRITE_PARAMETER：配置数据。W5500_READ_PARAMETER：读取参数
*@return   无
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
*@brief    启动w5500
*@param    void ：空
*@return   无
*/
void w5500_start_up(void)
{
  W5500_RESET_HIGH;
}
/**
*@function void w5500_turn_off(void)
*@brief    关闭w5500
*@param    void ：空
*@return   无
*/
void w5500_turn_off(void)
{
  W5500_RESET_LOW;
}
/**
*@function void w5500_restart(void)
*@brief    w5500重启 ，需要延时时间过长，可放在开始处
*@param    void ：无
*@return   无
*/
void w5500_restart(void)
{
  W5500_RESET_LOW;
  delay_us( 600);
  W5500_RESET_HIGH;
  delay_us( 16000);
}


/**
*@brief   写入一个8位数据到W5500
*@param   addrbsb: 写入数据的地址
*@param   data：写入的8位数据
*@return  无
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
*@brief   从W5500读出一个8位数据
*@param   addrbsb: 写入数据的地址
*@param   data：从写入的地址处读取到的8位数据
*@return  无
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
*@brief   向W5500写入len字节数据
*@param   addrbsb: 写入数据的地址
*@param   buf：写入字符串
*@param   len：字符串长度
*@return  len：返回字符串长度
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
*@brief   从W5500读出len字节数据
*@param   addrbsb: 读取数据的地址
*@param   buf：存放读取数据
*@param   len：字符串长度
*@return  len：返回字符串长度
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






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
uint16_t local_port=502;                                  /*定义本地端口*/

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
//*@brief   配置W5500的IP地址
//*@param   无
//*@return  无
//*/
//void set_w5500_ip(void)
//{
//  uint8_t local_ip[4],subnet[4],gateway[4];
//  if(SPIx==1)
//  {
//   /*复制定义的配置信息到配置结构体*/
//    memcpy(ConfigMsg.mac, Param.mac1, 6);
//    memcpy(ConfigMsg.lip,Param_now.local_ip1,4);
//    memcpy(ConfigMsg.sub,Param_now.subnet1,4);
//    memcpy(ConfigMsg.gw,Param_now.gateway1,4);
//    memcpy(ConfigMsg.dns,Param_now.dns_server1,4);
//  }
//  if(SPIx==2)
//  {
//   /*复制定义的配置信息到配置结构体*/
//    memcpy(ConfigMsg.mac, Param_now.mac2, 6);
//    memcpy(ConfigMsg.lip,Param_now.local_ip2,4);
//    memcpy(ConfigMsg.sub,Param_now.subnet2,4);
//    memcpy(ConfigMsg.gw,Param_now.gateway2,4);
//    memcpy(ConfigMsg.dns,Param_now.dns_server2,4);
//  }

//  /*以下配置信息，根据需要选用*/
//  ConfigMsg.sw_ver[0]=FW_VER_HIGH;
//  ConfigMsg.sw_ver[1]=FW_VER_LOW;

//  /*将IP配置信息写入W5500相应寄存器*/
//  setSUBR(ConfigMsg.sub);
//  setGAR(ConfigMsg.gw);
//  setSIPR(ConfigMsg.lip);
//  getSIPR (local_ip);
////    printf(" W5500 IP地址   : %d.%d.%d.%d\r\n", local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
//  getSUBR(subnet);
////  printf(" W5500 子网掩码 : %d.%d.%d.%d\r\n", subnet[0],subnet[1],subnet[2],subnet[3]);
//  getGAR(gateway);
////  printf(" W5500 网关     : %d.%d.%d.%d\r\n", gateway[0],gateway[1],gateway[2],gateway[3]);
//}

/**
*@brief   配置W5500的MAC地址
*@param   无
*@return  无
*/
void set_w5500_mac(S_W5500_CONFIG *configData)
{

  setSHAR(configData->macAddress); /**/
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





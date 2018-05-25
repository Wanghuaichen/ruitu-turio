/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_w5500.h
* @author       zhou
* @version      V1.0
* @date         2018/5/4
* @brief        w5500配置头文件
**************************************************************************************************
*/
#ifndef _BFM_W5500_H_
#define _BFM_W5500_H_
#include "include.h"

typedef  void (*pFunction)(void);


#define FW_VER_HIGH             1
#define FW_VER_LOW              0
#define ON                      1
#define OFF                     0
#define HIGH                    1
#define LOW                     0

#define MAX_BUF_SIZE            1460                       /*定义每个数据包的大小*/
#define KEEP_ALIVE_TIME         30  // 30sec
#define TX_RX_MAX_BUF_SIZE      2048
#define EEPROM_MSG_LEN          sizeof(EEPROM_MSG)

#define IP_FROM_DEFINE                    0                /*使用初始定义的IP信息*/
#define IP_FROM_DHCP                      1                /*使用DHCP获取IP信息*/
#define IP_FROM_EEPROM                    2                /*使用EEPROM定义的IP信息*/
extern uint8_t  ip_from;                                     /*选择IP信息配置源*/

#pragma pack(1)
/*此结构体定义了W5500可供配置的主要参数*/
typedef struct _CONFIG_MSG
{
  uint8_t macAddress[6];                                      //*MAC地址*/
  uint8_t localIP[4];                                         //*local IP本地IP地址*/
  uint8_t subnetMask[4];                                      //*子网掩码*/
  uint8_t gateWay[4];                                         //*网关*/
  uint8_t dns[4];                                             //*DNS服务器地址*/
  uint8_t remoteIP[4];                                        //*remote IP远程IP地址*/
  uint16_t localPort;                                         // 本地端口
  uint16_t remotePort;                                        // 远程端口
}S_W5500_CONFIG;
#pragma pack()

extern S_W5500_CONFIG   ConfigMsg;

/*MCU配置相关函数*/
void gpio_for_w5500_config(void);                           /*SPI接口reset 及中断引脚*/
void gpio_for_w5500_config1(void);

/*W5500SPI相关函数*/
void w5500_write_byte( uint32_t addrbsb,  uint8_t data);           /*写入一个8位数据到W5500*/
uint8_t w5500_read_byte(uint32_t addrbsb);                         /*从W5500读出一个8位数据*/
uint16_t w5500_write_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len); /*向W5500写入len字节数据*/
uint16_t w5500_read_buf(uint32_t addrbsb, uint8_t* buf,uint16_t len); /*从W5500读出len字节数据*/


/*--------------- 宏定义 --------------*/
#define W5500_WRITE_PARAMETER     1  // 写参数宏定义，其它值都认为是读
#define W5500_READ_PARAMETER      0  // 写参数宏定义，其它值都认为是读

// 管脚配置
#define W5500_CS_HIGH          GPIO_SetBits( W5500_NSS_GPIO_Port,W5500_NSS_Pin);
#define W5500_CS_LOW           GPIO_ResetBits( W5500_NSS_GPIO_Port,W5500_NSS_Pin);
#define W5500_RESET_HIGH       GPIO_SetBits( W5500_RSTN_GPIO_Port,W5500_RSTN_Pin);
#define W5500_RESET_LOW        GPIO_ResetBits( W5500_RSTN_GPIO_Port,W5500_RSTN_Pin);

// spi读写数据
#define W5500_SEND_GET_BYTE(sendByte,getByte) spi_send_get_data( sendByte, getByte);

/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/
void w5500_config_ip(S_W5500_CONFIG *configData, uint8_t readOrWrite);
void w5500_config_gateway(S_W5500_CONFIG *configData, uint8_t readOrWrite);
void w5500_config_subnetMask(S_W5500_CONFIG *configData, uint8_t readOrWrite);
void w5500_config_macAddress(S_W5500_CONFIG *configData, uint8_t readOrWrite);

void w5500_restart(void);
#endif


/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : private.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : 私用函数头文件
*******************************************************************************/
#ifndef  _PRIATE_H_
#define  _PRIATE_H_

#include "include.h"
/*****************宏定义********************/

// 以下是缓冲区状态定义
#define BUF_STATE_FORE       1     // 头在尾前方
#define BUF_STATE_BACK       0     // 头在尾后方

// 以下是缓冲区标志定义
#define BUF_FLAG_EMPTY       0     // 缓冲区无数据
#define BUF_FLAG_FULL        1     // 缓冲区有数据
#define BUF_FLAG_OVER        2     // 缓冲区溢出
                                   //

#define LOG_PRINT(x)  {printf(x);}
/*****************数据定义******************/
// 缓冲数据结构体
typedef uint8_t BUF_STATE;
typedef struct
{
    BUF_STATE head;
    BUF_STATE tail;
    BUF_STATE state;
    BUF_STATE flag;
    BUF_STATE length;
    BUF_STATE *buf;
}sBUFFER;

/*-----------------新定义缓冲区结构---------------------------*/
#define CIRCLE_IS_EMPTY    0   // 环形缓冲区是空的
#define CIRCLE_IS_FILL     1   // 环形缓冲区是有数据的
#define CIRCLE_IS_FULL     2   // 环形缓冲区是满的

#define OVER_IS_COVERS         // 定义此项，缓冲溢出选择覆盖，否则丢去溢出数据
typedef struct
{
  uint8_t           flag;   // 标志，指示缓冲区状态
  uint16_t          head;   // 缓冲区新数据指向
  uint16_t          tail;   // 缓冲区读出数据指向
  volatile int      unreadLen; // 未读数据长度
  int               length;    // 缓冲区长度
  uint8_t           *buf;      // 缓冲区数据缓存首地址
}sCIRCLE_BUF;

//-------发送DMA数据结构-----------------------//
#define TX_BUF_NUM              10
#define TX_BUF_SIZE             500
typedef struct
{
    volatile uint8_t flag;
    volatile uint8_t top;
    volatile uint8_t tail;
    uint16_t len[TX_BUF_NUM];
    uint8_t buf[TX_BUF_NUM][TX_BUF_SIZE];
}sTXDMA;
#define TX_DMA_BUF_FULL       1
#define TX_DMA_BUF_EMPTY      0
/*****************函数定义******************/
// 创建环形缓冲1
BUF_STATE CreatBuf(sBUFFER* sbuffer,BUF_STATE *buf,uint8_t length);
BUF_STATE SetByte(sBUFFER* sbuf,uint8_t recData);
uint8_t GetByte(sBUFFER* sbuf, uint8_t *recData);

// 创建环形缓冲2
uint8_t Circle_Creat_Buffer(sCIRCLE_BUF *sBuf,uint8_t *buf,uint16_t len);
uint8_t Circle_Write_Byte(sCIRCLE_BUF *sBuf,uint8_t wrData);
uint8_t Circle_Write_Data(sCIRCLE_BUF *sBuf,uint8_t *wrData,int len);
uint8_t Circle_Read_Byte(sCIRCLE_BUF *sBuf,uint8_t *rdData);
uint8_t Circle_Read_Data(sCIRCLE_BUF *sBuf,uint8_t *rdData,uint16_t *len);
//其它
uint8_t CheckSum(uint8_t *buf,uint8_t length);
void Exchange_H_L(uint16_t *buf,uint16_t length);
uint16_t get_average_value_uint16(uint16_t *buf, uint16_t length);
uint8_t get_average_value_uint8(uint8_t *buf, uint16_t length);



uint16_t CRC16(uint8_t* puchMsg, uint16_t usDataLen);
__asm void SystemReset(void);
void delay_us(u32 usTime);


void i32toa(uint32_t n,char *str, uint8_t* len);
uint32_t atoin32(char* str,uint8_t len);
uint8_t ctod(char c );
#endif




/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





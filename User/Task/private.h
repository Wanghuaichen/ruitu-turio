/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : private.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : ˽�ú���ͷ�ļ�
*******************************************************************************/
#ifndef  _PRIATE_H_
#define  _PRIATE_H_

#include "include.h"
/*****************�궨��********************/

// �����ǻ�����״̬����
#define BUF_STATE_FORE       1     // ͷ��βǰ��
#define BUF_STATE_BACK       0     // ͷ��β��

// �����ǻ�������־����
#define BUF_FLAG_EMPTY       0     // ������������
#define BUF_FLAG_FULL        1     // ������������
#define BUF_FLAG_OVER        2     // ���������
                                   //

#define LOG_PRINT(x)  {printf(x);}
/*****************���ݶ���******************/
// �������ݽṹ��
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

/*-----------------�¶��建�����ṹ---------------------------*/
#define CIRCLE_IS_EMPTY    0   // ���λ������ǿյ�
#define CIRCLE_IS_FILL     1   // ���λ������������ݵ�
#define CIRCLE_IS_FULL     2   // ���λ�����������

#define OVER_IS_COVERS         // �������������ѡ�񸲸ǣ�����ȥ�������
typedef struct
{
  uint8_t           flag;   // ��־��ָʾ������״̬
  uint16_t          head;   // ������������ָ��
  uint16_t          tail;   // ��������������ָ��
  volatile int      unreadLen; // δ�����ݳ���
  int               length;    // ����������
  uint8_t           *buf;      // ���������ݻ����׵�ַ
}sCIRCLE_BUF;

//-------����DMA���ݽṹ-----------------------//
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
/*****************��������******************/
// �������λ���1
BUF_STATE CreatBuf(sBUFFER* sbuffer,BUF_STATE *buf,uint8_t length);
BUF_STATE SetByte(sBUFFER* sbuf,uint8_t recData);
uint8_t GetByte(sBUFFER* sbuf, uint8_t *recData);

// �������λ���2
uint8_t Circle_Creat_Buffer(sCIRCLE_BUF *sBuf,uint8_t *buf,uint16_t len);
uint8_t Circle_Write_Byte(sCIRCLE_BUF *sBuf,uint8_t wrData);
uint8_t Circle_Write_Data(sCIRCLE_BUF *sBuf,uint8_t *wrData,int len);
uint8_t Circle_Read_Byte(sCIRCLE_BUF *sBuf,uint8_t *rdData);
uint8_t Circle_Read_Data(sCIRCLE_BUF *sBuf,uint8_t *rdData,uint16_t *len);
//����
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





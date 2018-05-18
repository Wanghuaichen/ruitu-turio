/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : private.c
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : ˽�ú���
*******************************************************************************/
#include "include.h"

/*
 * �����Լ��Ļ�������ѭ������
 */
BUF_STATE CreatBuf(sBUFFER *sbuffer, BUF_STATE *buf, uint8_t length)
{

    sbuffer->length = length;          // ���û���������
    sbuffer->head  = 0;                // ����ͷ��ָ�򻺳�λ��
    sbuffer->tail  = 0;                // ����β��ָ�򻺳�λ��
    sbuffer->state = BUF_STATE_FORE;   // ����״̬Ϊͷ����ǰ�����λ�����β����ǰ�����
    sbuffer->flag  = BUF_FLAG_EMPTY;   // ���û�����Ϊ��
    sbuffer->buf = buf;                // ���������������
    return sbuffer->flag;              // ���ػ����־
}
/*
 * д����������һ���ֽ�����д������
 */
BUF_STATE SetByte(sBUFFER *sbuf, uint8_t recData)
{
    if (sbuf->flag == BUF_FLAG_OVER)   // ���������
    {
#ifdef PRINTF_LOG //------��ӡlog------
        printf("�����������");
#endif
        return sbuf->flag;
    }
    sbuf->buf[sbuf->head] = recData;     // ������д�뻺��
    (((sbuf->head + 1) >= sbuf->length) ? (sbuf->head = 0),sbuf->state--:sbuf->head++); // �жϻ����ͷ������λ��
    if ((sbuf->head == sbuf->tail) && (sbuf->state == BUF_STATE_BACK))    // ��ͷ���ں���ͷ�Ѿ�׷��β��˵���������
    {
        sbuf->flag = BUF_FLAG_OVER;   // ��λ��־
    }
    else
        sbuf->flag = BUF_FLAG_FULL; // ���������ݱ�־
    return sbuf->flag;               // ���ػ��嵱ǰ��־
}

/*
 * �ӻ������л�ȡһ���ֽ�
 */
uint8_t GetByte(sBUFFER *sbuf, uint8_t *recData)
{
    if ((sbuf->tail == sbuf->head) && (sbuf->state == BUF_STATE_FORE))  // ��ͷ����ǰ��β��׷��ͷ����˵��������ȡ��
    {
        sbuf->flag  = BUF_FLAG_EMPTY;

#ifdef PRINTF_LOG //------��ӡlog------
        printf("�����������ѿգ�");
#endif
        return sbuf->flag;
    }

    *recData = sbuf->buf[sbuf->tail]; // ȡ������
                                      //������״̬�ж�
    (((sbuf->tail + 1) >= sbuf->length) ? (sbuf->tail = 0),sbuf->state++:sbuf->tail++); // �ж�β��λ��
    return sbuf->flag;     // ���ػ����־
}

/*------------------�½����λ���������------------------------------------------*/
/**
*@brief   �������λ�����
*@param     sBuf�������Ļ������� len������������ buf�������������ַ
*@return
*/
uint8_t Circle_Creat_Buffer(sCIRCLE_BUF *sBuf, uint8_t *buf, uint16_t len)
{
    sBuf->buf       = buf;
    sBuf->length    = len;
    sBuf->tail      = 0;
    sBuf->head      = 0;
    sBuf->unreadLen = 0;
    sBuf->flag      = CIRCLE_IS_EMPTY;
    return 1;
}
/**
*@brief   �Ի�����дһ������
*@param     sbuf��д���ݵĻ����� wrData��д�������
*@return    ��������־
*/
uint8_t Circle_Write_Byte(sCIRCLE_BUF *sBuf, uint8_t wrData)
{
    if (sBuf->unreadLen >= sBuf->length)
    {
#ifdef OVER_IS_COVERS // ���ѡ�񸲸Ƿ�ʽ
        sBuf->buf[sBuf->head++] = wrData; // д������
        if (sBuf->head >= sBuf->length)    // �жϻ��νڵ�
            sBuf->head = 0;                 // �������¿�ʼд��
        sBuf->unreadLen = sBuf->length;   // ����δ��ȡ���ݳ���
#else                 // ������
        printf("���λ���������");
#endif
        return sBuf->flag = CIRCLE_IS_FULL; //���ػ�������
    }
    // �����ݴ��뻺����
    sBuf->buf[sBuf->head++] = wrData;  // д������
    if (sBuf->head >= sBuf->length)     // �жϻ��νڵ㣬�Ƿ��Ѿ�д��һȦ
        sBuf->head = 0;
    sBuf->unreadLen++;                 // δ��ȡ���ݳ���+1
    return sBuf->flag = CIRCLE_IS_FILL; //���ػ������������
}
/**
*@brief   �Ի�����дָ����������
*@param     sbuf��д���ݵĻ����� wrData��д������� ,len:д�����ݳ���
*@return    ��������־
*/
uint8_t Circle_Write_Data(sCIRCLE_BUF *sBuf, uint8_t *wrData, int len)
{
    int i;
    if (len > (sBuf->length - sBuf->unreadLen)) // �������洢�ռ䲻��
    {
        printf("д�����ݹ�����");
        return sBuf->flag = CIRCLE_IS_FULL; //���ػ�������
    }
    for (i = 0; i < len; i++)
    {
        // �����ݴ��뻺����
        sBuf->buf[sBuf->head++] = wrData[i];  // д������
        if (sBuf->head >= sBuf->length)     // �жϻ��νڵ㣬�Ƿ��Ѿ�д��һȦ
            sBuf->head = 0;
        sBuf->unreadLen++;                 // δ��ȡ���ݳ���+1
    }
    return sBuf->flag = CIRCLE_IS_FILL; //���ػ������������
}
/**
*@brief   �ӻ���������һ���ֽ�
*@param     sBuf���������ݵĻ����� rdData������������
*@return    ��������־
*/
uint8_t Circle_Read_Byte(sCIRCLE_BUF *sBuf, uint8_t *rdData)
{
    if (sBuf->unreadLen > 0)  // �ж���δ��ȡ����
    {
        *rdData = sBuf->buf[sBuf->tail++]; // ��ȡ����
        if (sBuf->tail >= sBuf->length)     // �ж϶�ȡ�����Ƿ���һȦ
            sBuf->tail = 0;
        sBuf->unreadLen--;                 // δ��ȡ����-1
    }
    else
        return sBuf->flag = CIRCLE_IS_EMPTY; // ����ȡ�˱�־�ÿ�
    return sBuf->flag;
}
/**
*@brief   �ӻ�����������������
*@param     sBuf���������ݵĻ����� rdData������������ len:���ض�����������
*@return    ��������־
*/
uint8_t Circle_Read_Data(sCIRCLE_BUF *sBuf, uint8_t *rdData, uint16_t *len)
{
    *len = 0;
    while (sBuf->unreadLen > 0)  // �ж���δ��ȡ����
    {
        rdData[(*len)++] = sBuf->buf[sBuf->tail++]; // ��ȡ����
        if (sBuf->tail >= sBuf->length)     // �ж϶�ȡ�����Ƿ���һȦ
            sBuf->tail = 0;
        sBuf->unreadLen--;                 // δ��ȡ����-1
    }
    return sBuf->flag = CIRCLE_IS_EMPTY; // ����ȡ�˱�־�ÿ�
}
//*************************************************************************
// ����˽�к���
//**************************************************************************
/*
 * ��У�麯����ȡ����֮�ͣ����ƽ�λ
 */
uint8_t CheckSum(uint8_t *buf, uint8_t length)
{
    uint8_t i, checkSum = 0;
    for (i = 0; i < length; i++)
    {
        checkSum += buf[i];
    }
    return checkSum;
}

/*
 * �ߵ��ֽڽ���λ��:��һ��16�������ݸߵ�λ����
 */
void Exchange_H_L(uint16_t *buf, uint16_t length)
{
    uint16_t i;
    uint16_t middle;
    for (i = 0; i < length; i++)
    {
        middle = buf[i] >> 8;
        buf[i] = buf[i] << 8;
        buf[i] |= middle;
    }
}



//------------------------------------------------------------------------------------------------------------------------------------------
//CRC16У���ӳ���
//------------------------------------------------------------------------------------------------------------------------------------------
/*16λCRCУ���*/
const uint8_t auchCRCHi[] = {
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,

    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40
};
const uint8_t auchCRCLo[] = {
    0x00, 0xc0, 0xc1, 0x01, 0xc3, 0x03, 0x02, 0xc2, 0xc6, 0x06, 0x07, 0xc7, 0x05, 0xc5, 0xc4, 0x04,
    0xcc, 0x0c, 0x0d, 0xcd, 0x0f, 0xcf, 0xce, 0x0e, 0x0a, 0xca, 0xcb, 0x0b, 0xc9, 0x09, 0x08, 0xc8,
    0xd8, 0x18, 0x19, 0xd9, 0x1b, 0xdb, 0xda, 0x1a, 0x1e, 0xde, 0xdf, 0x1f, 0xdd, 0x1d, 0x1c, 0xdc,
    0x14, 0xd4, 0xd5, 0x15, 0xd7, 0x17, 0x16, 0xd6, 0xd2, 0x12, 0x13, 0xd3, 0x11, 0xd1, 0xd0, 0x10,
    0xf0, 0x30, 0x31, 0xf1, 0x33, 0xf3, 0xf2, 0x32, 0x36, 0xf6, 0xf7, 0x37, 0xf5, 0x35, 0x34, 0xf4,
    0x3c, 0xfc, 0xfd, 0x3d, 0xff, 0x3f, 0x3e, 0xfe, 0xfa, 0x3a, 0x3b, 0xfb, 0x39, 0xf9, 0xf8, 0x38,
    0x28, 0xe8, 0xe9, 0x29, 0xeb, 0x2b, 0x2a, 0xea, 0xee, 0x2e, 0x2f, 0xef, 0x2d, 0xed, 0xec, 0x2c,
    0xe4, 0x24, 0x25, 0xe5, 0x27, 0xe7, 0xe6, 0x26, 0x22, 0xe2, 0xe3, 0x23, 0xe1, 0x21, 0x20, 0xe0,

    0xa0, 0x60, 0x61, 0xa1, 0x63, 0xa3, 0xa2, 0x62, 0x66, 0xa6, 0xa7, 0x67, 0xa5, 0x65, 0x64, 0xa4,
    0x6c, 0xac, 0xad, 0x6d, 0xaf, 0x6f, 0x6e, 0xae, 0xaa, 0x6a, 0x6b, 0xab, 0x69, 0xa9, 0xa8, 0x68,
    0x78, 0xb8, 0xb9, 0x79, 0xbb, 0x7b, 0x7a, 0xba, 0xbe, 0x7e, 0x7f, 0xbf, 0x7d, 0xbd, 0xbc, 0x7c,
    0xb4, 0x74, 0x75, 0xb5, 0x77, 0xb7, 0xb6, 0x76, 0x72, 0xb2, 0xb3, 0x73, 0xb1, 0x71, 0x70, 0xb0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
    0x9c, 0x5c, 0x5d, 0x9d, 0x5f, 0x9f, 0x9e, 0x5e, 0x5a, 0x9a, 0x9b, 0x5b, 0x99, 0x59, 0x58, 0x98,
    0x88, 0x48, 0x49, 0x89, 0x4b, 0x8b, 0x8a, 0x4a, 0x4e, 0x8e, 0x8f, 0x4f, 0x8d, 0x4d, 0x4c, 0x8c,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};
//------------------------------------------------------------------------------------------------------------------------------------------
//16λCRCУ���ӳ���
uint16_t CRC16(uint8_t *puchMsg, uint16_t usDataLen)
{
    uint8_t uchCRCHi = 0xff;
    uint8_t uchCRCLo = 0xff;
    uint16_t uIndex, crcEnd;
    while (usDataLen--)
    {
        uIndex = uchCRCHi ^ *(puchMsg++);
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex];
    }
    //Debug_Printf("crc = %d",(uint16_t)((uchCRCHi<<8)|uchCRCLo));
    crcEnd = (uint16_t)((uchCRCHi << 8) | uchCRCLo);
    return crcEnd; //(uint16_t)((uchCRCHi<<8)|uchCRCLo);
}

/*
 * ��ʱ����
 */
void delay_ms(__IO uint32_t Delay)
{
    delayTick_ = 0;
    while (delayTick_ < Delay)
    {
    }
}
/**
*@function uint8_t get_average_value_uint8(uint8_t *buf, uint16_t length)
*@brief    ��һ��uint8��������ȥ�����ֵ����Сֵ����ƽ��ֵ
*@param    buf:��Ҫ��ƽ��ֵ������
*@param    length:��Ҫ��ƽ��ֵ�����ݵĳ���
*@return   ��������ƽ��ֵ���
*@date     2018/5/11
*/
uint8_t get_average_value_uint8(uint8_t *buf, uint16_t length)
{
  uint16_t sumValue = 0;;
  uint16_t i;
  uint8_t maxValue,minValue,averageValue;
  maxValue = minValue = buf[0];  // �ȸ�ֵ��������Сֵ
  sumValue += buf[0];            // �ۼ���ֵ
  for (i = 1; i < length; i++)
  {
    if (buf[i] > maxValue)  // ȡ���ֵ
      maxValue = buf[i];
    if (buf[i] < minValue)  // ȡ��Сֵ
      minValue = buf[i];
    sumValue += buf[i];     // ȡ�ۼ�ֵ
  }
  sumValue -= (maxValue + minValue);    // ȥ�����ֵ����Сֵ
  averageValue = sumValue / (length - 2); // ��ƽ��ֵ
  return averageValue;
}
/**
*@function uint16_t get_average_value_uint16(uint16_t *buf, uint16_t length)
*@brief    ��һ��16λ����,ȥ�����ֵ\��Сֵ,Ȼ����ƽ��ֵ
*@param    buf:��Ҫ��ֵ������
*@param    length:��Ҫ��ƽ��ֵ�����ݳ���
*@return   ��������ƽ��ֵ
*@date     2018/5/11
*/
uint16_t get_average_value_uint16(uint16_t *buf, uint16_t length)
{
  uint16_t sumValue = 0;;
  uint16_t i;
  uint16_t maxValue,minValue,averageValue;
  maxValue = minValue = buf[0];  // �ȸ�ֵ��������Сֵ
  sumValue += buf[0];            // �ۼ���ֵ
  for (i = 1; i < length; i++)
  {
    if (buf[i] > maxValue)  // ȡ���ֵ
      maxValue = buf[i];
    if (buf[i] < minValue)  // ȡ��Сֵ
      minValue = buf[i];
    sumValue += buf[i];     // ȡ�ۼ�ֵ
  }
  sumValue -= (maxValue + minValue);    // ȥ�����ֵ����Сֵ
  averageValue = sumValue / (length - 2); // ��ƽ��ֵ
  return averageValue;
}
// printf����
//#ifdef __GNUC__
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
////#endif
//PUTCHAR_PROTOTYPE
//{
////    HAL_UART_Transmit(&huart5 ,(uint8_t *)&ch, 1, 0xFFFF);
//    //HAL_UART_Transmit_IT(&huart1,(uint8_t *)&ch, 1); // �����޷��仯
//  USART_SendData(USART3, (uint16_t)ch);
//  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
//  {
//  } //�ȴ��ַ��������
//  return ch;
//}

__asm void SystemReset(void)
{
    MOV R0, #1           //;
    MSR FAULTMASK, R0    //; ���FAULTMASK ��ֹһ���жϲ���

    LDR R0, = 0xE000ED0C  //;

    LDR R1, = 0x05FA0004  //;
    STR R1, [R0]         //; ϵͳ�����λ
deadloop
    B deadloop        //; ��ѭ��ʹ�������в�������Ĵ���

}
#if (0)
void Delay_us(uint16_t time)
{
    uint16_t i = 0;
    while (time--)
    {
        i = 10; //�Լ�����
        while (i--);
    }
}
#endif
/**
*@function void delay_us(u32 usTime)
*@brief    ͨ����ȡsystick������ʱ
*@param    usTime����ʱ΢��ʱ��
*@return   ��
*@date     2018/5/7
*/
void delay_us(u32 usTime)
{
  #define SYSTICK_US_TICK   72
    u32 ticks;
    u32 tOld,tNow,tConuter = 0;
    u32 reload = SysTick->LOAD;        //LOAD��ֵ
    ticks = usTime * SYSTICK_US_TICK;           //��Ҫ�Ľ�����
    tOld = SysTick->VAL;             //�ս���ʱ�ļ�����ֵ
    while(1)
    {
        tNow = SysTick->VAL;
        if(tNow != tOld)
        {
            if(tNow<tOld)
              tConuter += tOld - tNow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
            else
              tConuter += reload - tNow + tOld;
            tOld = tNow;
            if(tConuter >= ticks)
              break;//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    }
}
/**
*@function void itoa(uint32_t n, uint8_t *str, uint8_t *len)
*@brief    ��10��������ת����ascii��
*@param    n������
*@param    str��ת���Ľ��
*@param    len:ת�������ݳ���
*@return   ��
*/
void i32toa(uint32_t n,char *str, uint8_t* len)
{
  uint8_t i = 0;
  char tempr[10];
  do
  {
    tempr[i++]=n%10+'0';
  }while((n/=10)>0);
  *len = i;
  for (i = 0; i < *len; i++)
  {
    str[i] = tempr[*len - 1 - i];
  }
}
/**
*@function uint32_t atoi32(char *str)
*@brief    ��ascii����ת����32λ��
*@param    str:��Ҫת����asc����
*@return   ת����ɵ�����
*/
uint32_t atoin32(char* str,uint8_t len)
{
  uint32_t num = 0;
  if (len == 0)
  {
    while (*str != 0)
    {
      num = num * 10 + ctod(*str++);
    }
  }
  else
  {
    while (len-- != 0)
    {
      num = num * 10 + ctod(*str++);
    }
  }
  return num;
}
/**
*@function uint8_t ctod(char c)
*@brief    ��һ�������ַ�(0-F)ת��������(0-15)
*@param    c:��Ҫת�����ַ�
*@return   ����ת���Ľ��
*/
uint8_t ctod(char c )
{
  if ((c >= '0') && (c <= '9'))
    return c - '0';
  if ((c >= 'a') && (c <= 'f'))
    return 10 + c -'a';
  if ((c >= 'A') && (c <= 'F'))
    return 10 + c -'A';

  return (uint8_t)c;
}

//  uint32_t atoi (char *str)
//  {
//    uint32_t i,n,sign;
//    for(i=0;isspace(s[i]);i++)//�����հ׷�;
//      sign=(s[i]=='-')?-1:1;
//    if(s[i]=='+'||s[i]==' -')//��������
//      i++;
//    for(n=0;isdigit(s[i]);i++)
//         n=10*n+(s[i]-'0');//�������ַ�ת������������
//    return sign *n;
//  }
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





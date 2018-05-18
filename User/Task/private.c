/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : private.c
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : 私用函数
*******************************************************************************/
#include "include.h"

/*
 * 创建自己的缓冲区：循环缓冲
 */
BUF_STATE CreatBuf(sBUFFER *sbuffer, BUF_STATE *buf, uint8_t length)
{

    sbuffer->length = length;          // 设置缓充区长度
    sbuffer->head  = 0;                // 设置头部指向缓冲位置
    sbuffer->tail  = 0;                // 设置尾部指向缓冲位置
    sbuffer->state = BUF_STATE_FORE;   // 设置状态为头部在前，因环形缓冲有尾部在前的情况
    sbuffer->flag  = BUF_FLAG_EMPTY;   // 设置缓冲区为空
    sbuffer->buf = buf;                // 缓冲区与数组关联
    return sbuffer->flag;              // 返回缓冲标志
}
/*
 * 写缓冲区：将一个字节数据写缓冲区
 */
BUF_STATE SetByte(sBUFFER *sbuf, uint8_t recData)
{
    if (sbuf->flag == BUF_FLAG_OVER)   // 若缓冲溢出
    {
#ifdef PRINTF_LOG //------打印log------
        printf("缓冲区溢出！");
#endif
        return sbuf->flag;
    }
    sbuf->buf[sbuf->head] = recData;     // 将数据写入缓冲
    (((sbuf->head + 1) >= sbuf->length) ? (sbuf->head = 0),sbuf->state--:sbuf->head++); // 判断缓冲的头部所在位置
    if ((sbuf->head == sbuf->tail) && (sbuf->state == BUF_STATE_BACK))    // 若头部在后且头已经追上尾，说明缓冲溢出
    {
        sbuf->flag = BUF_FLAG_OVER;   // 置位标志
    }
    else
        sbuf->flag = BUF_FLAG_FULL; // 缓冲有数据标志
    return sbuf->flag;               // 返回缓冲当前标志
}

/*
 * 从缓冲区中获取一个字节
 */
uint8_t GetByte(sBUFFER *sbuf, uint8_t *recData)
{
    if ((sbuf->tail == sbuf->head) && (sbuf->state == BUF_STATE_FORE))  // 若头部在前，尾部追上头部，说明缓冲区取完
    {
        sbuf->flag  = BUF_FLAG_EMPTY;

#ifdef PRINTF_LOG //------打印log------
        printf("缓冲区数据已空！");
#endif
        return sbuf->flag;
    }

    *recData = sbuf->buf[sbuf->tail]; // 取出数据
                                      //缓冲区状态判断
    (((sbuf->tail + 1) >= sbuf->length) ? (sbuf->tail = 0),sbuf->state++:sbuf->tail++); // 判断尾部位置
    return sbuf->flag;     // 返回缓冲标志
}

/*------------------新建环形缓冲区函数------------------------------------------*/
/**
*@brief   创建环形缓冲区
*@param     sBuf：创建的缓冲区名 len：缓冲区长度 buf：缓冲区缓存地址
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
*@brief   对缓冲区写一个数据
*@param     sbuf：写数据的缓冲区 wrData：写入的数据
*@return    缓冲区标志
*/
uint8_t Circle_Write_Byte(sCIRCLE_BUF *sBuf, uint8_t wrData)
{
    if (sBuf->unreadLen >= sBuf->length)
    {
#ifdef OVER_IS_COVERS // 如果选择覆盖方式
        sBuf->buf[sBuf->head++] = wrData; // 写入数据
        if (sBuf->head >= sBuf->length)    // 判断环形节点
            sBuf->head = 0;                 // 超出重新开始写入
        sBuf->unreadLen = sBuf->length;   // 设置未读取数据长度
#else                 // 不覆盖
        printf("环形缓冲已满！");
#endif
        return sBuf->flag = CIRCLE_IS_FULL; //返回缓冲已满
    }
    // 将数据存入缓冲区
    sBuf->buf[sBuf->head++] = wrData;  // 写入数据
    if (sBuf->head >= sBuf->length)     // 判断环形节点，是否已经写满一圈
        sBuf->head = 0;
    sBuf->unreadLen++;                 // 未读取数据长度+1
    return sBuf->flag = CIRCLE_IS_FILL; //返回缓冲填充了数据
}
/**
*@brief   对缓冲区写指定长度数据
*@param     sbuf：写数据的缓冲区 wrData：写入的数据 ,len:写入数据长度
*@return    缓冲区标志
*/
uint8_t Circle_Write_Data(sCIRCLE_BUF *sBuf, uint8_t *wrData, int len)
{
    int i;
    if (len > (sBuf->length - sBuf->unreadLen)) // 缓冲区存储空间不够
    {
        printf("写入数据过长！");
        return sBuf->flag = CIRCLE_IS_FULL; //返回缓冲已满
    }
    for (i = 0; i < len; i++)
    {
        // 将数据存入缓冲区
        sBuf->buf[sBuf->head++] = wrData[i];  // 写入数据
        if (sBuf->head >= sBuf->length)     // 判断环形节点，是否已经写满一圈
            sBuf->head = 0;
        sBuf->unreadLen++;                 // 未读取数据长度+1
    }
    return sBuf->flag = CIRCLE_IS_FILL; //返回缓冲填充了数据
}
/**
*@brief   从缓冲区读出一个字节
*@param     sBuf：读出数据的缓冲区 rdData：读出的数据
*@return    缓冲区标志
*/
uint8_t Circle_Read_Byte(sCIRCLE_BUF *sBuf, uint8_t *rdData)
{
    if (sBuf->unreadLen > 0)  // 判断有未读取数据
    {
        *rdData = sBuf->buf[sBuf->tail++]; // 读取数据
        if (sBuf->tail >= sBuf->length)     // 判断读取环形是否满一圈
            sBuf->tail = 0;
        sBuf->unreadLen--;                 // 未读取数据-1
    }
    else
        return sBuf->flag = CIRCLE_IS_EMPTY; // 都读取了标志置空
    return sBuf->flag;
}
/**
*@brief   从缓冲区读出所有数据
*@param     sBuf：读出数据的缓冲区 rdData：读出的数据 len:返回读出多少数据
*@return    缓冲区标志
*/
uint8_t Circle_Read_Data(sCIRCLE_BUF *sBuf, uint8_t *rdData, uint16_t *len)
{
    *len = 0;
    while (sBuf->unreadLen > 0)  // 判断有未读取数据
    {
        rdData[(*len)++] = sBuf->buf[sBuf->tail++]; // 读取数据
        if (sBuf->tail >= sBuf->length)     // 判断读取环形是否满一圈
            sBuf->tail = 0;
        sBuf->unreadLen--;                 // 未读取数据-1
    }
    return sBuf->flag = CIRCLE_IS_EMPTY; // 都读取了标志置空
}
//*************************************************************************
// 其它私有函数
//**************************************************************************
/*
 * 和校验函数：取数据之和，不计进位
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
 * 高低字节交换位置:将一个16进制数据高低位互换
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
//CRC16校验子程序
//------------------------------------------------------------------------------------------------------------------------------------------
/*16位CRC校验表*/
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
//16位CRC校验子程序
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
 * 延时函数
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
*@brief    对一组uint8长度数据去除最大值和最小值后求平均值
*@param    buf:需要求平均值的数据
*@param    length:需要求平均值的数据的长度
*@return   返回所求平均值结果
*@date     2018/5/11
*/
uint8_t get_average_value_uint8(uint8_t *buf, uint16_t length)
{
  uint16_t sumValue = 0;;
  uint16_t i;
  uint8_t maxValue,minValue,averageValue;
  maxValue = minValue = buf[0];  // 先赋值给最大和最小值
  sumValue += buf[0];            // 累加总值
  for (i = 1; i < length; i++)
  {
    if (buf[i] > maxValue)  // 取最大值
      maxValue = buf[i];
    if (buf[i] < minValue)  // 取最小值
      minValue = buf[i];
    sumValue += buf[i];     // 取累加值
  }
  sumValue -= (maxValue + minValue);    // 去除最大值和最小值
  averageValue = sumValue / (length - 2); // 求平均值
  return averageValue;
}
/**
*@function uint16_t get_average_value_uint16(uint16_t *buf, uint16_t length)
*@brief    对一组16位数据,去掉最大值\最小值,然后求平均值
*@param    buf:需要求值的数组
*@param    length:需要求平均值的数据长度
*@return   返回所求平均值
*@date     2018/5/11
*/
uint16_t get_average_value_uint16(uint16_t *buf, uint16_t length)
{
  uint16_t sumValue = 0;;
  uint16_t i;
  uint16_t maxValue,minValue,averageValue;
  maxValue = minValue = buf[0];  // 先赋值给最大和最小值
  sumValue += buf[0];            // 累加总值
  for (i = 1; i < length; i++)
  {
    if (buf[i] > maxValue)  // 取最大值
      maxValue = buf[i];
    if (buf[i] < minValue)  // 取最小值
      minValue = buf[i];
    sumValue += buf[i];     // 取累加值
  }
  sumValue -= (maxValue + minValue);    // 去除最大值和最小值
  averageValue = sumValue / (length - 2); // 求平均值
  return averageValue;
}
// printf定义
//#ifdef __GNUC__
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
////#endif
//PUTCHAR_PROTOTYPE
//{
////    HAL_UART_Transmit(&huart5 ,(uint8_t *)&ch, 1, 0xFFFF);
//    //HAL_UART_Transmit_IT(&huart1,(uint8_t *)&ch, 1); // 长度无法变化
//  USART_SendData(USART3, (uint16_t)ch);
//  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
//  {
//  } //等待字符发送完毕
//  return ch;
//}

__asm void SystemReset(void)
{
    MOV R0, #1           //;
    MSR FAULTMASK, R0    //; 清除FAULTMASK 禁止一切中断产生

    LDR R0, = 0xE000ED0C  //;

    LDR R1, = 0x05FA0004  //;
    STR R1, [R0]         //; 系统软件复位
deadloop
    B deadloop        //; 死循环使程序运行不到下面的代码

}
#if (0)
void Delay_us(uint16_t time)
{
    uint16_t i = 0;
    while (time--)
    {
        i = 10; //自己定义
        while (i--);
    }
}
#endif
/**
*@function void delay_us(u32 usTime)
*@brief    通过读取systick进行延时
*@param    usTime：延时微秒时间
*@return   无
*@date     2018/5/7
*/
void delay_us(u32 usTime)
{
  #define SYSTICK_US_TICK   72
    u32 ticks;
    u32 tOld,tNow,tConuter = 0;
    u32 reload = SysTick->LOAD;        //LOAD的值
    ticks = usTime * SYSTICK_US_TICK;           //需要的节拍数
    tOld = SysTick->VAL;             //刚进入时的计数器值
    while(1)
    {
        tNow = SysTick->VAL;
        if(tNow != tOld)
        {
            if(tNow<tOld)
              tConuter += tOld - tNow;//这里注意一下SYSTICK是一个递减的计数器就可以了.
            else
              tConuter += reload - tNow + tOld;
            tOld = tNow;
            if(tConuter >= ticks)
              break;//时间超过/等于要延迟的时间,则退出.
        }
    }
}
/**
*@function void itoa(uint32_t n, uint8_t *str, uint8_t *len)
*@brief    将10进制数据转换成ascii码
*@param    n：数据
*@param    str：转换的结果
*@param    len:转换的数据长度
*@return   无
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
*@brief    将ascii数据转换成32位数
*@param    str:需要转换的asc数据
*@return   转换完成的数据
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
*@brief    将一个数字字符(0-F)转换成数字(0-15)
*@param    c:需要转换的字符
*@return   返回转换的结果
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
//    for(i=0;isspace(s[i]);i++)//跳过空白符;
//      sign=(s[i]=='-')?-1:1;
//    if(s[i]=='+'||s[i]==' -')//跳过符号
//      i++;
//    for(n=0;isdigit(s[i]);i++)
//         n=10*n+(s[i]-'0');//将数字字符转换成整形数字
//    return sign *n;
//  }
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





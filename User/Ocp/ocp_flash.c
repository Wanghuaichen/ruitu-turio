/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_flash.c
* @author       zhou
* @version      V1.0
* @date         2018/5/24
* @brief        ����flash���Ƴ����ļ�
**************************************************************************************************
*/
#include "include.h"
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
/**
*@function uint8_t Flash_Read(unsigned char *addr, uint16_t len)
*@brief    ��flash����
*@param    addr ����ȡ���ݵĵ�ַ
*@param    len ����ȡ���ݵĳ���
*@return   1���ɹ�
*/
uint8_t Flash_Read(unsigned char *addr, uint16_t len) //addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
{
  uint16_t i;
  for(i=0; i<len; i=i+2)
  {
    u16 temp;
    if(i+1 <= len-1)
    {
      temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));
      addr[i] = BYTE0(temp);
      addr[i+1] = BYTE1(temp);
    }
    else
    {
      temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));
      addr[i] = BYTE0(temp);
    }

  }
  return 1;
}
/**
*@function uint8_t Flash_Write(unsigned char *addr, uint16_t len)
*@brief    flashд����
*@param    addr ��д���ַ
*@param    len ��д�����ݳ���
*@return   ��
*/
uint8_t Flash_Write(unsigned char *addr, uint16_t len)
{
  uint16_t  FlashStatus;
  uint16_t i;
  //����flash
  FLASH_Unlock();

  FlashStatus = FLASH_ErasePage(PARAMFLASH_BASE_ADDRESS);//������ҳ
  if(FlashStatus != FLASH_COMPLETE)
    return 0;

  for(i=0; i<len; i=i+2)
  {
    u16 temp;
    if(i+1 <= len-1)
      temp = (u16)(addr[i+1]<<8) + addr[i];
    else
      temp = 0xff00 + addr[i];

    FlashStatus = FLASH_ProgramHalfWord(PARAMFLASH_BASE_ADDRESS+i, temp);
        if (FlashStatus != FLASH_COMPLETE)
      return 0;
  }
  return 1;
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





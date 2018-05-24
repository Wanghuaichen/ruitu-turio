/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_flash.h
* @author       zhou
* @version      V1.0
* @date         2018/5/24
* @brief        板上flash控制程序头文件
**************************************************************************************************
*/
#ifndef _OCP_FALSH_H_
#define _OCP_FALSH_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
/* Exported constants --------------------------------------------------------*/
/* Define the STM32F10Xxx Flash page size depending on the used STM32 device */
#if defined (STM32F10X_LD) || defined (STM32F10X_MD)
  #define PAGE_SIZE  (uint16_t)0x400  /* Page size = 1KByte */
#elif defined (STM32F10X_HD) || defined (STM32F10X_CL)
  #define PAGE_SIZE  (uint16_t)0x800  /* Page size = 2KByte */
#endif
/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS    ((uint32_t)0x08010000) /* EEPROM emulation start address: after 64KByte of used Flash memory */
#define PARAMFLASH_BASE_ADDRESS      ((uint32_t)(EEPROM_START_ADDRESS + 0x000))
#define PARAMFLASH_END_ADDRESS       ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/

uint8_t Flash_Read(unsigned char *addr, uint16_t len);
uint8_t Flash_Write(unsigned char *addr, uint16_t len);
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





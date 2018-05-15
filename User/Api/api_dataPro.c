/*
*************************(C) COPYRIGHT 2017 ********************************************
* @file         api_dataPro.c
* @author       zhou
* @version      V1.0
* @date         2018/1/11
* @brief        cte���ݴ�����
**************************************************************************************************
*/
#include "include.h"

void rx_data_processing(uint8_t *buf,uint16_t len,uint8_t mode)
{
  if ((buf[0] == 'o')&& (buf[1] == 'k'))
  {
    if ((mode == COM_TYPE_RS232)
        && ((rs232RxFlag_ & RS232_SET_MOTOR_PARAM) != RS232_SET_MOTOR_PARAM))
      rs232RxFlag_ |= RS232_SET_MOTOR_PARAM;
  }

}

/**
*@brief    �������ݴ������
*@param     buf����Ҫ��������� len����Ҫ��������ݳ��� instr:ָ�� mode��ģʽ
*@return 0:ʧ�� 1���ɹ�
*/
uint8_t tx_data_processing(uint8_t *buf, uint16_t len, uint8_t instr, uint8_t mode)
{
   uint8_t cteTxData_[100];
   // 8�ֽڣ���ͷ2bytes+����2bytes+ID 1byte+ָ��1byte+��ʷ���1byte+��β1byte
   cteTxData_[0] = 0xFD;
   cteTxData_[1] = 0xF7;
   cteTxData_[2] = (uint8_t)(((len + 8) & 0xFF00) >> 8); // ȡ���ݳ��ȸ��ֽ�
   cteTxData_[3] = (uint8_t)((len + 8) & 0x00FF);        // ȡ���ݳ��ȵ��ֽ�
//   cteTxData_[4] = GetID();                              // ��ȡID
   cteTxData_[5] = instr;                                // ָ��
   memcpy(&cteTxData_[6], buf, len);
   cteTxData_[len + 6] = cmdTick_++;
   cteTxData_[len + 7] = 0x16;
   if (mode == COM_TYPE_ETHERNET)                       // ͨ������ͨ��
   {

   }
   else if (mode == COM_TYPE_RS485)                  // ͨ��������PC���ʹ�ӡ����
   {
      Circle_Write_Data(&sUart1TxCircleBuf_, cteTxData_, len + 8);       // ��ӡ����д�뻺��
   }

   return 1;
}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





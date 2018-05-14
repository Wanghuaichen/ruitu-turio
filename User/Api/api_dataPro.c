/*
*************************(C) COPYRIGHT 2017 ********************************************
* @file         api_dataPro.c
* @author       zhou
* @version      V1.0
* @date         2018/1/11
* @brief        cte数据处理函数
**************************************************************************************************
*/
#include "include.h"

void rx_data_processing(uint8_t *buf,uint16_t len,uint8_t mode)
{
    //TcpWriteData(buf,len);
    uint8_t recData[30];
    uint16_t i = 0;
    uint16_t recLen = 0;
    // 判断所有字节
    while (i < len)
    {
      // 如果包头及ID是自己的进行数据处理
      if ((buf[i] == 0xFD) && (buf[i + 1] == 0xF7))// && ((buf[i + 4] == GetID()) ||(buf[i + 4] == 0xF7) ))
      {
        recLen = ((buf[i + 2] << 8) + buf[i + 3]); // 只计算数据域的长度
        if ((recLen < 9) || (recLen > 1032))
        {
//            printf("err cmd = %d",recData[0]);
//            printf("err len = %d",recLen);
            break;
        }
        else
            recLen -= 8;
        task_cmd(&buf[i + 5], recLen + 2, mode);                   // 执行任务处理
        i += (recLen + 7);
      }
      i++;
    }
}

/**
*@brief    发送数据打包程序
*@param     buf：需要打包的数据 len：需要打包的数据长度 instr:指令 mode：模式
*@return 0:失败 1：成功
*/
uint8_t tx_data_processing(uint8_t *buf, uint16_t len, uint8_t instr, uint8_t mode)
{
   uint8_t cteTxData_[100];
   // 8字节：包头2bytes+长度2bytes+ID 1byte+指令1byte+历史编号1byte+结尾1byte
   cteTxData_[0] = 0xFD;
   cteTxData_[1] = 0xF7;
   cteTxData_[2] = (uint8_t)(((len + 8) & 0xFF00) >> 8); // 取数据长度高字节
   cteTxData_[3] = (uint8_t)((len + 8) & 0x00FF);        // 取数据长度低字节
//   cteTxData_[4] = GetID();                              // 获取ID
   cteTxData_[5] = instr;                                // 指令
   memcpy(&cteTxData_[6], buf, len);
   cteTxData_[len + 6] = cmdTick_++;
   cteTxData_[len + 7] = 0x16;
   if (mode == COM_TYPE_ETHERNET)                       // 通过网口通信
   {

   }
   else if (mode == COM_TYPE_RS485)                  // 通过串口向PC发送打印数据
   {
      Circle_Write_Data(&sUart1TxCircleBuf_, cteTxData_, len + 8);       // 打印内容写入缓存
   }

   return 1;
}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





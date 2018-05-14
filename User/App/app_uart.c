/**
*************************(C) COPYRIGHT 2017 ********************************************
* @file         app_uart.c
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        串口应用文件
**************************************************************************************************
*/
#include "include.h"
void task_uart_rx(void);
void task_uart_tx(void);

void task_uart_rx_init(void)
{
  _TaskUartRx.fun = task_uart_rx;
  _TaskUartRx.command = CMD_TASK_UART_RX;
  memset(&uart1RxBuf_, 0, sizeof(uart1RxBuf_));
  Circle_Creat_Buffer(&sUart1RxCircleBuf_, uart1RxBuf_, UART1_BUF_LEN); // 创建缓冲区格式
  memset(&uart3RxBuf_, 0, sizeof(uart3RxBuf_));
  Circle_Creat_Buffer(&sUart3RxCircleBuf_, uart3RxBuf_, UART3_BUF_LEN); // 创建缓冲区格式
  _TaskUartRx.state = TASK_STATE_RUN;
}
void task_uart_rx(void)
{
  if (_TaskUartRx.info & UART3_RX_DATA)
  {
    _TaskUartRx.info &= ~(UART3_RX_DATA);
   // rx_data_processing(cteRxData_, cteRxLen, COM_TYPE_RS485);
  }
  if (_TaskUartRx.info & UART1_RX_DATA)
  {
    _TaskUartRx.info &= ~(UART1_RX_DATA);
//    Circle_Read_Data(&sUart1RxCircleBuf_, cteRxData_, &cteRxLen);
//    CTE_RX_Data_Pro(cteRxData_, cteRxLen, COM_TYPE_AORB);
  }
}
void task_uart_tx_init(void)
{
  _TaskUartTx.fun = task_uart_tx;
  _TaskUartTx.command = CMD_TASK_UART_TX;
  memset(&uart3TxBuf_, 0, sizeof(uart3TxBuf_));
  Circle_Creat_Buffer(&sUart3TxCircleBuf_, uart3TxBuf_, UART3_BUF_LEN); // 创建缓冲区格式
  _TaskUartTx.state = TASK_STATE_RUN;
}
void task_uart_tx(void)
{
  uint8_t sendData = 0;
  if (sUart3TxCircleBuf_.unreadLen > 0)
  {
    if (USART_GetFlagStatus(USART3,USART_FLAG_TC) != RESET)
    {
      Circle_Read_Byte(&sUart3TxCircleBuf_, &sendData);
      USART3->DR = (uint16_t)sendData;
    }
  }
}


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





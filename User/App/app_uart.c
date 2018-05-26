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
/**
*@function void task_uart_rx_init(void)
*@brief    接收任务初始化函数
*@param    void:参数无
*@return   无
*@date     2018/5/14
*/
void task_uart_rx_init(void)
{
  _TaskUartRx.fun = task_uart_rx;
  _TaskUartRx.command = CMD_TASK_UART_RX;
  memset(&uart1RxBuf_, 0, sizeof(uart1RxBuf_));
  Circle_Creat_Buffer(&sUart1RxCircleBuf_, uart1RxBuf_, UART1_BUF_LEN); // 创建缓冲区格式
  memset(&uart3RxBuf_, 0, sizeof(uart3RxBuf_));
  Circle_Creat_Buffer(&sUart3RxCircleBuf_, uart3RxBuf_, UART3_BUF_LEN); // 创建缓冲区格式
  _TaskUartRx.state = TASK_STATE_RUN;
  rs485_select_tx_rx(RS485_RX);
}
/**
*@function void task_uart_rx(void)
*@brief    接收任务函数
*@param    void
*@return   无
*@date     2018/5/14
*/
void task_uart_rx(void)
{
  uint8_t rxData[100];
  uint16_t len;
  _TaskUartRx.state = TASK_STATE_SLEEP; // 只执行一次
  // 串口1是否接收到数据
  if (_TaskUartRx.info & UART3_RX_DATA)
  {
    _TaskUartRx.info &= ~(UART3_RX_DATA);
    Circle_Read_Data(&sUart3RxCircleBuf_, rxData, &len);
    motor_rx_data_processing((char*)rxData, len);
#ifdef COM_LOOP_BACK_ENABLE
    Circle_Write_Data(&sUart3TxCircleBuf_,rxData,len+1); //回环测试
#endif
  }
  // 串口3是否接收到数据
  if (_TaskUartRx.info & UART1_RX_DATA)
  {
    _TaskUartRx.info &= ~(UART1_RX_DATA);
    Circle_Read_Data(&sUart1RxCircleBuf_, rxData, &len);
    battery_rx_processing(rxData, len);
#ifdef COM_LOOP_BACK_ENABLE
    Circle_Write_Data(&sUart1TxCircleBuf_,rxData,len+1);
#endif
//    Circle_Read_Data(&sUart1RxCircleBuf_, cteRxData_, &cteRxLen);
//    CTE_RX_Data_Pro(cteRxData_, cteRxLen, COM_TYPE_AORB);
  }

}
/**
*@function void task_uart_tx_init(void)
*@brief    发送任务处理初始化函数
*@param    void
*@return   无
*@date     2018/5/14
*/
void task_uart_tx_init(void)
{
  _TaskUartTx.fun = task_uart_tx;
  _TaskUartTx.command = CMD_TASK_UART_TX;
  memset(&uart3TxBuf_, 0, sizeof(uart3TxBuf_));
  Circle_Creat_Buffer(&sUart3TxCircleBuf_, uart3TxBuf_, UART3_BUF_LEN); // 创建缓冲区格式
    memset(&uart1TxBuf_, 0, sizeof(uart1TxBuf_));
  Circle_Creat_Buffer(&sUart1TxCircleBuf_, uart1TxBuf_, UART1_BUF_LEN); // 创建缓冲区格式
  _TaskUartTx.state = TASK_STATE_RUN;
}
/**
*@function void task_uart_tx(void)
*@brief    发送任务初始化函数
*@return   无
*@date     2018/5/14
*/
void task_uart_tx(void)
{
  uint8_t sendData = 0;
  if (sUart3TxCircleBuf_.unreadLen > 0)
  {
    if (USART_GetFlagStatus(USART3,USART_FLAG_TC) != RESET)
    {
      Circle_Read_Byte(&sUart3TxCircleBuf_, &sendData);
      while (sUart3TxCircleBuf_.unreadLen > 0)
      {
        USART3->DR = (uint16_t)sendData;
        Circle_Read_Byte(&sUart3TxCircleBuf_, &sendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        } //等待字符发送完毕
      }
    }
  }
  if (sUart1TxCircleBuf_.unreadLen > 0)
  {
    if (USART_GetFlagStatus(USART1,USART_FLAG_TC) != RESET)
    {
      rs485_select_tx_rx(RS485_TX);
      Circle_Read_Byte(&sUart1TxCircleBuf_, &sendData);
      while (sUart1TxCircleBuf_.unreadLen > 0)
      {
        USART1->DR = (uint16_t)sendData;
        Circle_Read_Byte(&sUart1TxCircleBuf_, &sendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        {
        } //等待字符发送完毕
      }
      rs485_select_tx_rx(RS485_RX);
    }
  }
}


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





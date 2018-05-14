/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.c
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        基于w5500的tcp应用程
**************************************************************************************************
*/
#include "include.h"
uint8_t buff[1000];
/**
*@brief   TCP Server回环演示函数。
*@param   无
*@return  无
*/
void do_tcp_server(void)
{
  uint16_t len=0;
  switch(getSn_SR(SOCK_TCPS))                                   /*获取socket的状态*/
  {
    case SOCK_CLOSED:                                           /*socket处于关闭状态*/
      socket(SOCK_TCPS, Sn_MR_TCP, sDefaultNetConfig_.localPort, Sn_MR_ND);         /*打开socket*/
      break;

    case SOCK_INIT:                                             /*socket已初始化状态*/
      listen(SOCK_TCPS);                                        /*socket建立监听*/
      break;

    case SOCK_ESTABLISHED:                                      /*socket处于连接建立状态*/
      if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPS, Sn_IR_CON);                         /*清除接收中断标志位*/
      }
      len=getSn_RX_RSR(SOCK_TCPS);                              /*定义len为已接收数据的长度*/
      if(len>0)
      {
        recv(SOCK_TCPS,buff,len);                               /*接收来自Client的数据*/
        send(SOCK_TCPS,buff,len);
      }
      break;
    case SOCK_CLOSE_WAIT:                                       /*socket处于等待关闭状态*/

      close(SOCK_TCPS);
      break;
  }
}

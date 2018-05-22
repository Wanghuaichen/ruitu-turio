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
uint8_t buff[500];
char erhBuff[500];
uint16_t remote_port =  502;
uint8_t remote_ip[4] = {192,168,1,103};
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
      if(len>20)
      {
        recv(SOCK_TCPS,buff,len);                               /*接收来自Client的数据*/
        //send(SOCK_TCPS,buff,len -2);
        ethernet_rx_data_processing( (char*)buff,len );
      }
      break;
    case SOCK_CLOSE_WAIT:                                       /*socket处于等待关闭状态*/

      close(SOCK_TCPS);
      break;
  }
}
/**
*@brief   TCP Client回环演示函数。
*@param   无
*@return  无
*/
void do_tcp_client(void)
{
   uint16_t len=0;

  switch(getSn_SR(SOCK_TCPC))                                  /*获取socket的状态*/
  {
    case SOCK_CLOSED:                                          /*socket处于关闭状态*/
      socket(SOCK_TCPC,Sn_MR_TCP,sDefaultNetConfig_.localPort++,Sn_MR_ND);
      break;

    case SOCK_INIT:                                            /*socket处于初始化状态*/
      connect(SOCK_TCPC,remote_ip,remote_port);                /*socket连接服务器*/
      break;

    case SOCK_ESTABLISHED:                                     /*socket处于连接建立状态*/
      if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPC, Sn_IR_CON);                        /*清除接收中断标志位*/
      }

      len=getSn_RX_RSR(SOCK_TCPC);                             /*定义len为已接收数据的长度*/
      if(len>2)
      {
        recv(SOCK_TCPC,buff,len);                              /*接收来自Server的数据*/
        buff[len]=0x00;                                        /*添加字符串结束符*/
        //printf("%s\r\n",buff);
        send(SOCK_TCPC,buff,len -2);                               /*向Server发送数据*/
        rx_data_processing(buff,len,COM_TYPE_ETHERNET);
      }
      break;

    case SOCK_CLOSE_WAIT:                                      /*socket处于等待关闭状态*/
      close(SOCK_TCPC);
      break;

  }
}

void ethernet_printf(char *buf, uint16_t len)
{
  if (len > 0)
    send(SOCK_TCPS,(uint8_t*)buf, len);
  else
    send(SOCK_TCPS,(uint8_t*)buf, strlen(buf));
}

void ethernet_rx_data_processing(char *buf,uint16_t len)
{
  cJSON *name,*psw,*num;
  static uint8_t flag = 0,recoder = 0;
  static uint16_t dnum = 0;
  uint16_t i = 0;
  for (i = 0; i < len; i++)
  {
    if ( (buf[i] != ' ') && (buf[i] != '\r') && (buf[i] != '\n'))
      erhBuff[dnum++] = buf[i];
    if (flag == 0)
    {
      if (buf[i] == '{')
      {
        flag = 1;
        recoder++;
      }
    }
    else if (flag == 1)
    {
      if (buf[i] == '{')
        recoder++;
      else if (buf[i] == '}')
        recoder--;
      if (recoder == 0)
      {
        cJSON *root = cJSON_Parse(erhBuff);
        char *out = cJSON_Print(root);   //将json形式打印成正常字符串形式
        ethernet_printf(out,0);
        name = cJSON_GetObjectItem(root, "name");
        ethernet_printf(name->valuestring, 0);
        psw = cJSON_GetObjectItem(root, "passwd");
        ethernet_printf(psw->valuestring, 0);
        num = cJSON_GetObjectItem(root, "num");
        ethernet_printf((char*)num->type, 0);
        ethernet_printf((char*)num->valueint, 0);
        // 释放内存
        cJSON_Delete(root);
        free(out);
        flag = 0;
        dnum = 0;
      }
    }
  }

}

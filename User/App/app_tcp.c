/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.c
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        ����w5500��tcpӦ�ó�
**************************************************************************************************
*/
#include "include.h"
uint8_t buff[500];
char erhBuff[500];
uint16_t remote_port =  502;
uint8_t remote_ip[4] = {192,168,1,103};
/**
*@brief   TCP Server�ػ���ʾ������
*@param   ��
*@return  ��
*/
void do_tcp_server(void)
{
  uint16_t len=0;
  switch(getSn_SR(SOCK_TCPS))                                   /*��ȡsocket��״̬*/
  {
    case SOCK_CLOSED:                                           /*socket���ڹر�״̬*/
      socket(SOCK_TCPS, Sn_MR_TCP, sDefaultNetConfig_.localPort, Sn_MR_ND);         /*��socket*/
      break;

    case SOCK_INIT:                                             /*socket�ѳ�ʼ��״̬*/
      listen(SOCK_TCPS);                                        /*socket��������*/
      break;

    case SOCK_ESTABLISHED:                                      /*socket�������ӽ���״̬*/
      if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPS, Sn_IR_CON);                         /*��������жϱ�־λ*/
      }
      len=getSn_RX_RSR(SOCK_TCPS);                              /*����lenΪ�ѽ������ݵĳ���*/
      if(len>20)
      {
        recv(SOCK_TCPS,buff,len);                               /*��������Client������*/
        //send(SOCK_TCPS,buff,len -2);
        ethernet_rx_data_processing( (char*)buff,len );
      }
      break;
    case SOCK_CLOSE_WAIT:                                       /*socket���ڵȴ��ر�״̬*/

      close(SOCK_TCPS);
      break;
  }
}
/**
*@brief   TCP Client�ػ���ʾ������
*@param   ��
*@return  ��
*/
void do_tcp_client(void)
{
   uint16_t len=0;

  switch(getSn_SR(SOCK_TCPC))                                  /*��ȡsocket��״̬*/
  {
    case SOCK_CLOSED:                                          /*socket���ڹر�״̬*/
      socket(SOCK_TCPC,Sn_MR_TCP,sDefaultNetConfig_.localPort++,Sn_MR_ND);
      break;

    case SOCK_INIT:                                            /*socket���ڳ�ʼ��״̬*/
      connect(SOCK_TCPC,remote_ip,remote_port);                /*socket���ӷ�����*/
      break;

    case SOCK_ESTABLISHED:                                     /*socket�������ӽ���״̬*/
      if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPC, Sn_IR_CON);                        /*��������жϱ�־λ*/
      }

      len=getSn_RX_RSR(SOCK_TCPC);                             /*����lenΪ�ѽ������ݵĳ���*/
      if(len>2)
      {
        recv(SOCK_TCPC,buff,len);                              /*��������Server������*/
        buff[len]=0x00;                                        /*����ַ���������*/
        //printf("%s\r\n",buff);
        send(SOCK_TCPC,buff,len -2);                               /*��Server��������*/
        rx_data_processing(buff,len,COM_TYPE_ETHERNET);
      }
      break;

    case SOCK_CLOSE_WAIT:                                      /*socket���ڵȴ��ر�״̬*/
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
        char *out = cJSON_Print(root);   //��json��ʽ��ӡ�������ַ�����ʽ
        ethernet_printf(out,0);
        name = cJSON_GetObjectItem(root, "name");
        ethernet_printf(name->valuestring, 0);
        psw = cJSON_GetObjectItem(root, "passwd");
        ethernet_printf(psw->valuestring, 0);
        num = cJSON_GetObjectItem(root, "num");
        ethernet_printf((char*)num->type, 0);
        ethernet_printf((char*)num->valueint, 0);
        // �ͷ��ڴ�
        cJSON_Delete(root);
        free(out);
        flag = 0;
        dnum = 0;
      }
    }
  }

}

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
uint16_t local_port = 502;
uint8_t buff[500];
char erhBuff[500];
uint16_t remote_port =  502;
uint8_t remote_ip[4] = {192,168,1,103};
/**************************************************************************
�������ܣ�����SOCKET����λ�������ĳ���
��ڲ�����
����  ֵ��
ע�⣺
**************************************************************************/
void Command_tcp_client(void)
{
    char *sendchar = NULL;
    char *recchar = NULL;
    uint8_t ComdType=0;
    uint16_t len=0;
    uint16_t count=0;
  switch(getSn_SR(SOCK_TCPC))                                  /*��ȡsocket��״̬*/
  {
    case SOCK_CLOSED:                                          /*socket���ڹر�״̬*/
      socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
      break;

    case SOCK_INIT:                                            /*socket���ڳ�ʼ��״̬*/
      connect(SOCK_TCPC,remote_ip,remote_port);                /*socket���ӷ�����*/
      break;

    case SOCK_ESTABLISHED:                                     /*socket�������ӽ���״̬*/
        count++;
      if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPC, Sn_IR_CON);                        /*��������жϱ�־λ*/
      }
      if(count==1)//�����ϵ�һ�η����������͸���λ��
        //send(SOCK_TCPC,buff,strlen(buff));                     //��Server��������ShakeHandInit_TypeDef ���ͣ�IDΪ���٣�TypeΪRobotCommand
      {
//        sendchar = Trans_to_ServerFormat(sendchar,HelloStatusCommand_to_cJSON( &Command_Hello_TypeStructure));
        TCP_Send(sendchar);
      }



      if(count>65534)//��ֹ�������
        count=2;
      //send(SOCK_TCPC,buff,strlen(buff));                     /*��Server����״̬���ݣ�����*/

      len=getSn_RX_RSR(SOCK_TCPC);                             /*����lenΪ�ѽ������ݵĳ���*/
      if(len>0)//���յ�����
      {
        recv(SOCK_TCPC,buff,len);                              //*��������Server������,�����ݴ浽һ��������

        buff[len]=0x00;                                        /*����ַ���������*/
        //�����ݽ��н���������Ϊ������ȥ��֡ͷ֡β��Ȼ���JSON���н�������ʱ��Ϊ���������һ���Ƿ���������Ӧ�ģ�һ���Ƿ�������ģ�
        recchar=Parse_from_ServerFormat((char*)buff);
        ComdType=GetCommandFromServer(recchar);
        if(ComdType==NOCOMMAND)
            break;
        if(ComdType==COMMAND)
        {
        //���յ����µ�����


        }
        if(ComdType==HELLO_ACK)
        {

        //���յ���ID��ʱ���������


        }

        printf("%s\r\n",buff);

        send(SOCK_TCPC,buff,sizeof(buff));                               /*��Server��������*/
      }
        //send(SOCK_TCPC,(const)root,sizeof(root));
      break;

    case SOCK_CLOSE_WAIT:                                      /*socket���ڵȴ��ر�״̬*/
      close(SOCK_TCPC);
      break;


  }
}

/**************************************************************************
�������ܣ�״̬SOCKET����λ�������ĳ���
��ڲ�����
����  ֵ��
ע�⣺
**************************************************************************/

void Status_tcp_client(void)
{
   uint16_t len=0;
   uint16_t count=0;

  switch(getSn_SR(SOCK_TCPC2))                                   /*��ȡsocket��״̬*/
  {
    case SOCK_CLOSED:                                          /*socket���ڹر�״̬*/
      socket(SOCK_TCPC2,Sn_MR_TCP,local_port++,Sn_MR_ND);
      count=0;
      break;

    case SOCK_INIT:                                            /*socket���ڳ�ʼ��״̬*/
      connect(SOCK_TCPC2,remote_ip,remote_port);                /*socket���ӷ�����*/
      count=0;
      break;

    case SOCK_ESTABLISHED:                                     /*socket�������ӽ���״̬*/
      count++;
      if(getSn_IR(SOCK_TCPC2) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPC2, Sn_IR_CON);                       /*��������жϱ�־λ*/
       }
      if(count==1)//�����ϵ�һ�η����������͸���λ��
        //send(SOCK_TCPC2,buff2,strlen(buff2));                    //��Server��������ShakeHandInit_TypeDef ���ͣ�IDΪ���٣�TypeΪRobotStatus
      if(count>65534)//��ֹ�������
        count=2;
      //send(SOCK_TCPC2,buff2,strlen(buff2));                    /*��Server����״̬���ݣ�����*/

      break;

    case SOCK_CLOSE_WAIT:                                      /*socket���ڵȴ��ر�״̬*/
      close(SOCK_TCPC2);
      break;


  }
}
void task_tcp_init(void)
{
  _TaskTcp.fun = task_tcp;
  _TaskTcp.state = TASK_STATE_RUN;
}
void task_tcp(void)
{
  uint8_t bar = TASK_BAR_CMD;
  if (_TaskTcp.progressBar == bar++)
  {
    Command_tcp_client();
    _TaskTcp.progressBar++;
  }
  else if (_TaskTcp.progressBar == bar++)
  {
    Status_tcp_client();
    _TaskTcp.progressBar--;
  }
}

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
uint16_t local_port = 502;
uint8_t buff[500];
char erhBuff[500];
uint16_t remote_port =  502;
uint8_t remote_ip[4] = {192,168,1,103};
/**************************************************************************
函数功能：命令SOCKET与上位机交互的程序
入口参数：
返回  值：
注意：
**************************************************************************/
void Command_tcp_client(void)
{
    char *sendchar = NULL;
    char *recchar = NULL;
    uint8_t ComdType=0;
    uint16_t len=0;
    uint16_t count=0;
  switch(getSn_SR(SOCK_TCPC))                                  /*获取socket的状态*/
  {
    case SOCK_CLOSED:                                          /*socket处于关闭状态*/
      socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
      break;

    case SOCK_INIT:                                            /*socket处于初始化状态*/
      connect(SOCK_TCPC,remote_ip,remote_port);                /*socket连接服务器*/
      break;

    case SOCK_ESTABLISHED:                                     /*socket处于连接建立状态*/
        count++;
      if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPC, Sn_IR_CON);                        /*清除接收中断标志位*/
      }
      if(count==1)//连接上第一次发送连接类型给上位机
        //send(SOCK_TCPC,buff,strlen(buff));                     //向Server发送数据ShakeHandInit_TypeDef 类型，ID为多少，Type为RobotCommand
      {
//        sendchar = Trans_to_ServerFormat(sendchar,HelloStatusCommand_to_cJSON( &Command_Hello_TypeStructure));
        TCP_Send(sendchar);
      }



      if(count>65534)//防止次数溢出
        count=2;
      //send(SOCK_TCPC,buff,strlen(buff));                     /*向Server发送状态数据，数据*/

      len=getSn_RX_RSR(SOCK_TCPC);                             /*定义len为已接收数据的长度*/
      if(len>0)//接收到数据
      {
        recv(SOCK_TCPC,buff,len);                              //*接收来自Server的数据,把数据存到一个缓存内

        buff[len]=0x00;                                        /*添加字符串结束符*/
        //对数据进行解析，过程为：首先去掉帧头帧尾，然后对JSON进行解析，此时分为两种情况，一种是返回握手响应的，一种是返回命令的，
        recchar=Parse_from_ServerFormat((char*)buff);
        ComdType=GetCommandFromServer(recchar);
        if(ComdType==NOCOMMAND)
            break;
        if(ComdType==COMMAND)
        {
        //接收到了新的命令


        }
        if(ComdType==HELLO_ACK)
        {

        //接收到了ID及时间参数反馈


        }

        printf("%s\r\n",buff);

        send(SOCK_TCPC,buff,sizeof(buff));                               /*向Server发送数据*/
      }
        //send(SOCK_TCPC,(const)root,sizeof(root));
      break;

    case SOCK_CLOSE_WAIT:                                      /*socket处于等待关闭状态*/
      close(SOCK_TCPC);
      break;


  }
}

/**************************************************************************
函数功能：状态SOCKET与上位机交互的程序
入口参数：
返回  值：
注意：
**************************************************************************/

void Status_tcp_client(void)
{
   uint16_t len=0;
   uint16_t count=0;

  switch(getSn_SR(SOCK_TCPC2))                                   /*获取socket的状态*/
  {
    case SOCK_CLOSED:                                          /*socket处于关闭状态*/
      socket(SOCK_TCPC2,Sn_MR_TCP,local_port++,Sn_MR_ND);
      count=0;
      break;

    case SOCK_INIT:                                            /*socket处于初始化状态*/
      connect(SOCK_TCPC2,remote_ip,remote_port);                /*socket连接服务器*/
      count=0;
      break;

    case SOCK_ESTABLISHED:                                     /*socket处于连接建立状态*/
      count++;
      if(getSn_IR(SOCK_TCPC2) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPC2, Sn_IR_CON);                       /*清除接收中断标志位*/
       }
      if(count==1)//连接上第一次发送连接类型给上位机
        //send(SOCK_TCPC2,buff2,strlen(buff2));                    //向Server发送数据ShakeHandInit_TypeDef 类型，ID为多少，Type为RobotStatus
      if(count>65534)//防止次数溢出
        count=2;
      //send(SOCK_TCPC2,buff2,strlen(buff2));                    /*向Server发送状态数据，数据*/

      break;

    case SOCK_CLOSE_WAIT:                                      /*socket处于等待关闭状态*/
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

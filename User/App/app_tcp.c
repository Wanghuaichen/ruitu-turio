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

//  uint8_t buff[500];
//  char erhBuff[500];
//  char testcmd[] = "Auto";
//  char testtime[] = "2017-10-13 17:27:30";
//uint16_t remote_port =  502;
//uint8_t remote_ip[4] = {192,168,1,103};
///**************************************************************************
//函数功能：命令SOCKET与上位机交互的程序
//入口参数：
//返回  值：
//注意：
//**************************************************************************/
//void Command_tcp_client(void)
//{
//    char *sendchar = NULL;
//    char *recchar = NULL;
//    uint8_t ComdType=0;
//    uint16_t len=0;
//    uint16_t count=0;
//  switch(getSn_SR(SOCK_TCPC))                                  /*获取socket的状态*/
//  {
//    case SOCK_CLOSED:                                          /*socket处于关闭状态*/
//      socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
//      break;

//    case SOCK_INIT:                                            /*socket处于初始化状态*/
//      connect(SOCK_TCPC,remote_ip,remote_port);                /*socket连接服务器*/
//      break;

//    case SOCK_ESTABLISHED:                                     /*socket处于连接建立状态*/
//        count++;
//      if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
//      {
//        setSn_IR(SOCK_TCPC, Sn_IR_CON);                        /*清除接收中断标志位*/
//      }
//      if(count==1)//连接上第一次发送连接类型给上位机
//        //send(SOCK_TCPC,buff,strlen(buff));                     //向Server发送数据ShakeHandInit_TypeDef 类型，ID为多少，Type为RobotCommand
//      {
////        sendchar = Trans_to_ServerFormat(sendchar,HelloStatusCommand_to_cJSON( &Command_Hello_TypeStructure));
//        TCP_Send(sendchar);
//      }



//      if(count>65534)//防止次数溢出
//        count=2;
//      //send(SOCK_TCPC,buff,strlen(buff));                     /*向Server发送状态数据，数据*/

//      len=getSn_RX_RSR(SOCK_TCPC);                             /*定义len为已接收数据的长度*/
//      if(len>0)//接收到数据
//      {
//        recv(SOCK_TCPC,buff,len);                              //*接收来自Server的数据,把数据存到一个缓存内

//        buff[len]=0x00;                                        /*添加字符串结束符*/
//        //对数据进行解析，过程为：首先去掉帧头帧尾，然后对JSON进行解析，此时分为两种情况，一种是返回握手响应的，一种是返回命令的，
//        recchar=Parse_from_ServerFormat((char*)buff);
//        ComdType=GetCommandFromServer(recchar);
//        if(ComdType==NOCOMMAND)
//            break;
//        if(ComdType==COMMAND)
//        {
//        //接收到了新的命令


//        }
//        if(ComdType==HELLO_ACK)
//        {

//        //接收到了ID及时间参数反馈


//        }

//        printf("%s\r\n",buff);

//        send(SOCK_TCPC,buff,sizeof(buff));                               /*向Server发送数据*/
//      }
//        //send(SOCK_TCPC,(const)root,sizeof(root));
//      break;

//    case SOCK_CLOSE_WAIT:                                      /*socket处于等待关闭状态*/
//      close(SOCK_TCPC);
//      break;


//  }
//}

///**************************************************************************
//函数功能：状态SOCKET与上位机交互的程序
//入口参数：
//返回  值：
//注意：
//**************************************************************************/

//void Status_tcp_client(void)
//{
//   uint16_t len=0;
//   uint16_t count=0;

//  switch(getSn_SR(SOCK_TCPC2))                                   /*获取socket的状态*/
//  {
//    case SOCK_CLOSED:                                          /*socket处于关闭状态*/
//      socket(SOCK_TCPC2,Sn_MR_TCP,local_port++,Sn_MR_ND);
//      count=0;
//      break;

//    case SOCK_INIT:                                            /*socket处于初始化状态*/
//      connect(SOCK_TCPC2,remote_ip,remote_port);                /*socket连接服务器*/
//      count=0;
//      break;

//    case SOCK_ESTABLISHED:                                     /*socket处于连接建立状态*/
//      count++;
//      if(getSn_IR(SOCK_TCPC2) & Sn_IR_CON)
//      {
//        setSn_IR(SOCK_TCPC2, Sn_IR_CON);                       /*清除接收中断标志位*/
//       }
//      if(count==1)//连接上第一次发送连接类型给上位机
//        //send(SOCK_TCPC2,buff2,strlen(buff2));                    //向Server发送数据ShakeHandInit_TypeDef 类型，ID为多少，Type为RobotStatus
//      if(count>65534)//防止次数溢出
//        count=2;
//      //send(SOCK_TCPC2,buff2,strlen(buff2));                    /*向Server发送状态数据，数据*/

//      break;

//    case SOCK_CLOSE_WAIT:                                      /*socket处于等待关闭状态*/
//      close(SOCK_TCPC2);
//      break;


//  }
//}
/**
*@function void task_tcp_init(void)
*@brief    tcp任务初始化函数
*@param    void ：空
*@return   无
*/
void task_tcp_init(void)
{
  _TaskTcp.fun = task_tcp;
  _TaskTcp.state = TASK_STATE_RUN;
  setRTR(50);
}
/**
*@function void task_tcp(void)
*@brief    tcp任务函数
*@return   无
*/
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
    Status_tcp_client2();
    _TaskTcp.progressBar--;
  }
}
/**
*@function uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd)
*@brief    机器人接收数据转换，将网上发出数据转换成指令执行
*@param    sRobotCmd ：上位机指令数据结构体
*@return   1：成功 0：失败
*/
uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd)
{
  uint8_t len;
  // 读取参数
  sMotorParam_.eComand = get_robot_command(sRobotCmd->Command); // 获取命令
  if (sRobotStatus_.runStatus == sMotorParam_.eComand) // 相同命令返回
    return 1;
  else if (sMotorParam_.eComand == Robot_CMD_Stop) // 其它任何状态都可以切换到stop
    sRobotStatus_.runStatus = Robot_CMD_Stop;
  else if (sRobotStatus_.runStatus == Robot_CMD_Stop) // stop状态
  {
      if (sMotorParam_.eComand == Robot_CMD_Set) // stop状态可设置
      {
        i32toa(sRobotCmd->Speed * MOTOR_COUNTS_VELOCITY, sMotorParam_.speed, &len); // 速度
        i32toa(sRobotCmd->StartPosition * MOTOR_COUNTS_POSITION, sMotorParam_.startPosition, &len); // 开始位置
        i32toa(sRobotCmd->EndPosition * MOTOR_COUNTS_POSITION, sMotorParam_.endPosition, &len); // 结束位置
        i32toa(sRobotCmd->TargetPosition * MOTOR_COUNTS_POSITION, sMotorParam_.targetPosition, &len); // 目标位置
        sMotorParam_.step = sRobotCmd->Step ;                              // 步长
        sMotorParam_.runCount = sRobotCmd->RunCount;
        sMotorParam_.eWorkMode = get_robot_run_mode(sRobotCmd->WorkMode);  // 工作模式
      }
      else if ((sMotorParam_.eComand == Robot_CMD_Auto)  //stop状态可切换状态
              ||(sMotorParam_.eComand == Robot_CMD_Jog)
              ||(sMotorParam_.eComand == Robot_CMD_Dot)
              ||(sMotorParam_.eComand == Robot_CMD_Homing)
              )
      {
        sRobotStatus_.runStatus = sMotorParam_.eComand;
      }

  }
  else if (((sMotorParam_.eComand == Robot_CMD_Forward)   // 手动模式处理
          || (sMotorParam_.eComand == Robot_CMD_Backward))
          && (sRobotStatus_.runStatus == Robot_CMD_Jog)
          )
  {
    sRobotStatus_.runStatus = sMotorParam_.eComand;
  }
  else
    return 1;

  // 停止操作
  _TaskMotorControl.progressBar = 0;
  _TaskMotorControl.state = TASK_STATE_RUN;
  return 1;
}
/**
*@function void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus)
*@brief    机器人发送数据处理
*@param    sStatus ：需要发送的数据
*@return   无
*/
void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus)
{
  ROBOStatus_TypeDef recRobotStatus;
  set_robot_command(sStatus->runStatus,recRobotStatus.RunStatus); // 上传状态
  strcpy( recRobotStatus.CurrentTime ,"2017-10-13 17:27:30\0");    // 上传时间
  recRobotStatus.CurrentPositiont = motorStatus_[0]/MOTOR_COUNTS_POSITION;    // 上传当前位置
  recRobotStatus.CurrentSpeed = motorStatus_[3] / MOTOR_COUNTS_VELOCITY; // 上传当前速度
  recRobotStatus.RunningCount = (sStatus->RunningCount/2);        // 上传巡检次数
  recRobotStatus.CurrentTemp = sStatus->CurrentTemp;              // 上传当前温度
  recRobotStatus.CurrentVoltage = ((float)(sStatus->CurrentVoltage) / 100); // 上传当前电池电压
  recRobotStatus.CurrentAmp = ((float)(sStatus->CurrentAmp)/100);           // 上传当前电池电流
  recRobotStatus.CurrentDir = sStatus->CurrentDir;                        // 上传当前运动向
  recRobotStatus.ControlSystemEnergy = (float)(sStatus->ControlSystemEnergy); // 上传当前电池电量
  recRobotStatus.DynamicSystemEnergy = recRobotStatus.ControlSystemEnergy;        // 上传当前电池电量
  send_robot_status_data(&recRobotStatus);
}
/**
*@function E_MOTOR_STATE get_robot_command(char *buf)
*@brief    获取指令状态，将字符串转为枚举
*@param    buf ：指令字符串
*@return   枚举结果
*/
E_MOTOR_STATE get_robot_command(char *buf)
{
  if (strcmp(buf, "Auto") == 0)
    return Robot_CMD_Auto;
  else if (strcmp(buf, "Set") == 0)
    return Robot_CMD_Set;
  else if (strcmp(buf, "Jog") == 0)
    return Robot_CMD_Jog;
  else if (strcmp(buf, "Stop") == 0)
    return Robot_CMD_Stop;
  else if (strcmp(buf, "Forward") == 0)
    return Robot_CMD_Forward;
  else if (strcmp(buf, "Backward") == 0)
    return Robot_CMD_Backward;
  else if (strcmp(buf, "Dot") == 0)
    return Robot_CMD_Dot;
  else if (strcmp(buf, "Homing") == 0)
    return Robot_CMD_Homing;
  else
    return Robot_CMD_Error;
}
/**
*@function E_WORK_MODE get_robot_run_mode(char *buf)
*@brief    运行模式字符串转枚举值
*@param    buf ：需要转换的字符串
*@return   枚举结果
*/
E_WORK_MODE get_robot_run_mode(char *buf)
{
  if (strcmp(buf, "RealTime") == 0)
    return Robot_Work_RealTime;
  else if (strcmp(buf, "Regular") == 0)
    return Robot_Work_Regular;
  else if (strcmp(buf, "Daily") == 0)
    return Robot_Work_Daily;
  else
    return Robot_Work_Error;
}
/**
*@function void set_robot_command(E_MOTOR_STATE eRobotStatus, char *buf)
*@brief    将指令从枚举类型转换成字符串
*@param    eRobotStatus ：枚举类型
*@param    buf ：字符串地址
*@return   无
*/
void set_robot_command(E_MOTOR_STATE eRobotStatus ,char *buf)
{

  if (eRobotStatus ==  Robot_CMD_Auto)
   strcpy( buf,"Auto");
  else if (eRobotStatus ==  Robot_CMD_Set)
    strcpy( buf,"Set");
  else if (eRobotStatus ==  Robot_CMD_Jog)
    strcpy( buf,"Jog");
  else if (eRobotStatus ==  Robot_CMD_Stop)
    strcpy( buf,"Stop");
  else if (eRobotStatus ==  Robot_CMD_Forward)
    strcpy( buf,"Forward");
  else if (eRobotStatus ==  Robot_CMD_Backward)
    strcpy( buf,"Backward");
  else if (eRobotStatus ==  Robot_CMD_Dot)
    strcpy( buf,"Dot");
  else if (eRobotStatus ==  Robot_CMD_Homing)
    strcpy( buf,"Homing");
}


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





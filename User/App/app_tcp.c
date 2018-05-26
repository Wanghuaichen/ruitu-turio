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

//  uint8_t buff[500];
//  char erhBuff[500];
//  char testcmd[] = "Auto";
//  char testtime[] = "2017-10-13 17:27:30";
//uint16_t remote_port =  502;
//uint8_t remote_ip[4] = {192,168,1,103};
///**************************************************************************
//�������ܣ�����SOCKET����λ�������ĳ���
//��ڲ�����
//����  ֵ��
//ע�⣺
//**************************************************************************/
//void Command_tcp_client(void)
//{
//    char *sendchar = NULL;
//    char *recchar = NULL;
//    uint8_t ComdType=0;
//    uint16_t len=0;
//    uint16_t count=0;
//  switch(getSn_SR(SOCK_TCPC))                                  /*��ȡsocket��״̬*/
//  {
//    case SOCK_CLOSED:                                          /*socket���ڹر�״̬*/
//      socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
//      break;

//    case SOCK_INIT:                                            /*socket���ڳ�ʼ��״̬*/
//      connect(SOCK_TCPC,remote_ip,remote_port);                /*socket���ӷ�����*/
//      break;

//    case SOCK_ESTABLISHED:                                     /*socket�������ӽ���״̬*/
//        count++;
//      if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
//      {
//        setSn_IR(SOCK_TCPC, Sn_IR_CON);                        /*��������жϱ�־λ*/
//      }
//      if(count==1)//�����ϵ�һ�η����������͸���λ��
//        //send(SOCK_TCPC,buff,strlen(buff));                     //��Server��������ShakeHandInit_TypeDef ���ͣ�IDΪ���٣�TypeΪRobotCommand
//      {
////        sendchar = Trans_to_ServerFormat(sendchar,HelloStatusCommand_to_cJSON( &Command_Hello_TypeStructure));
//        TCP_Send(sendchar);
//      }



//      if(count>65534)//��ֹ�������
//        count=2;
//      //send(SOCK_TCPC,buff,strlen(buff));                     /*��Server����״̬���ݣ�����*/

//      len=getSn_RX_RSR(SOCK_TCPC);                             /*����lenΪ�ѽ������ݵĳ���*/
//      if(len>0)//���յ�����
//      {
//        recv(SOCK_TCPC,buff,len);                              //*��������Server������,�����ݴ浽һ��������

//        buff[len]=0x00;                                        /*����ַ���������*/
//        //�����ݽ��н���������Ϊ������ȥ��֡ͷ֡β��Ȼ���JSON���н�������ʱ��Ϊ���������һ���Ƿ���������Ӧ�ģ�һ���Ƿ�������ģ�
//        recchar=Parse_from_ServerFormat((char*)buff);
//        ComdType=GetCommandFromServer(recchar);
//        if(ComdType==NOCOMMAND)
//            break;
//        if(ComdType==COMMAND)
//        {
//        //���յ����µ�����


//        }
//        if(ComdType==HELLO_ACK)
//        {

//        //���յ���ID��ʱ���������


//        }

//        printf("%s\r\n",buff);

//        send(SOCK_TCPC,buff,sizeof(buff));                               /*��Server��������*/
//      }
//        //send(SOCK_TCPC,(const)root,sizeof(root));
//      break;

//    case SOCK_CLOSE_WAIT:                                      /*socket���ڵȴ��ر�״̬*/
//      close(SOCK_TCPC);
//      break;


//  }
//}

///**************************************************************************
//�������ܣ�״̬SOCKET����λ�������ĳ���
//��ڲ�����
//����  ֵ��
//ע�⣺
//**************************************************************************/

//void Status_tcp_client(void)
//{
//   uint16_t len=0;
//   uint16_t count=0;

//  switch(getSn_SR(SOCK_TCPC2))                                   /*��ȡsocket��״̬*/
//  {
//    case SOCK_CLOSED:                                          /*socket���ڹر�״̬*/
//      socket(SOCK_TCPC2,Sn_MR_TCP,local_port++,Sn_MR_ND);
//      count=0;
//      break;

//    case SOCK_INIT:                                            /*socket���ڳ�ʼ��״̬*/
//      connect(SOCK_TCPC2,remote_ip,remote_port);                /*socket���ӷ�����*/
//      count=0;
//      break;

//    case SOCK_ESTABLISHED:                                     /*socket�������ӽ���״̬*/
//      count++;
//      if(getSn_IR(SOCK_TCPC2) & Sn_IR_CON)
//      {
//        setSn_IR(SOCK_TCPC2, Sn_IR_CON);                       /*��������жϱ�־λ*/
//       }
//      if(count==1)//�����ϵ�һ�η����������͸���λ��
//        //send(SOCK_TCPC2,buff2,strlen(buff2));                    //��Server��������ShakeHandInit_TypeDef ���ͣ�IDΪ���٣�TypeΪRobotStatus
//      if(count>65534)//��ֹ�������
//        count=2;
//      //send(SOCK_TCPC2,buff2,strlen(buff2));                    /*��Server����״̬���ݣ�����*/

//      break;

//    case SOCK_CLOSE_WAIT:                                      /*socket���ڵȴ��ر�״̬*/
//      close(SOCK_TCPC2);
//      break;


//  }
//}
/**
*@function void task_tcp_init(void)
*@brief    tcp�����ʼ������
*@param    void ����
*@return   ��
*/
void task_tcp_init(void)
{
  _TaskTcp.fun = task_tcp;
  _TaskTcp.state = TASK_STATE_RUN;
  setRTR(50);
}
/**
*@function void task_tcp(void)
*@brief    tcp������
*@return   ��
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
*@brief    �����˽�������ת���������Ϸ�������ת����ָ��ִ��
*@param    sRobotCmd ����λ��ָ�����ݽṹ��
*@return   1���ɹ� 0��ʧ��
*/
uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd)
{
  uint8_t len;
  // ��ȡ����
  sMotorParam_.eComand = get_robot_command(sRobotCmd->Command); // ��ȡ����
  if (sRobotStatus_.runStatus == sMotorParam_.eComand) // ��ͬ�����
    return 1;
  else if (sMotorParam_.eComand == Robot_CMD_Stop) // �����κ�״̬�������л���stop
    sRobotStatus_.runStatus = Robot_CMD_Stop;
  else if (sRobotStatus_.runStatus == Robot_CMD_Stop) // stop״̬
  {
      if (sMotorParam_.eComand == Robot_CMD_Set) // stop״̬������
      {
        i32toa(sRobotCmd->Speed * MOTOR_COUNTS_VELOCITY, sMotorParam_.speed, &len); // �ٶ�
        i32toa(sRobotCmd->StartPosition * MOTOR_COUNTS_POSITION, sMotorParam_.startPosition, &len); // ��ʼλ��
        i32toa(sRobotCmd->EndPosition * MOTOR_COUNTS_POSITION, sMotorParam_.endPosition, &len); // ����λ��
        i32toa(sRobotCmd->TargetPosition * MOTOR_COUNTS_POSITION, sMotorParam_.targetPosition, &len); // Ŀ��λ��
        sMotorParam_.step = sRobotCmd->Step ;                              // ����
        sMotorParam_.runCount = sRobotCmd->RunCount;
        sMotorParam_.eWorkMode = get_robot_run_mode(sRobotCmd->WorkMode);  // ����ģʽ
      }
      else if ((sMotorParam_.eComand == Robot_CMD_Auto)  //stop״̬���л�״̬
              ||(sMotorParam_.eComand == Robot_CMD_Jog)
              ||(sMotorParam_.eComand == Robot_CMD_Dot)
              ||(sMotorParam_.eComand == Robot_CMD_Homing)
              )
      {
        sRobotStatus_.runStatus = sMotorParam_.eComand;
      }

  }
  else if (((sMotorParam_.eComand == Robot_CMD_Forward)   // �ֶ�ģʽ����
          || (sMotorParam_.eComand == Robot_CMD_Backward))
          && (sRobotStatus_.runStatus == Robot_CMD_Jog)
          )
  {
    sRobotStatus_.runStatus = sMotorParam_.eComand;
  }
  else
    return 1;

  // ֹͣ����
  _TaskMotorControl.progressBar = 0;
  _TaskMotorControl.state = TASK_STATE_RUN;
  return 1;
}
/**
*@function void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus)
*@brief    �����˷������ݴ���
*@param    sStatus ����Ҫ���͵�����
*@return   ��
*/
void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus)
{
  ROBOStatus_TypeDef recRobotStatus;
  set_robot_command(sStatus->runStatus,recRobotStatus.RunStatus); // �ϴ�״̬
  strcpy( recRobotStatus.CurrentTime ,"2017-10-13 17:27:30\0");    // �ϴ�ʱ��
  recRobotStatus.CurrentPositiont = motorStatus_[0]/MOTOR_COUNTS_POSITION;    // �ϴ���ǰλ��
  recRobotStatus.CurrentSpeed = motorStatus_[3] / MOTOR_COUNTS_VELOCITY; // �ϴ���ǰ�ٶ�
  recRobotStatus.RunningCount = (sStatus->RunningCount/2);        // �ϴ�Ѳ�����
  recRobotStatus.CurrentTemp = sStatus->CurrentTemp;              // �ϴ���ǰ�¶�
  recRobotStatus.CurrentVoltage = ((float)(sStatus->CurrentVoltage) / 100); // �ϴ���ǰ��ص�ѹ
  recRobotStatus.CurrentAmp = ((float)(sStatus->CurrentAmp)/100);           // �ϴ���ǰ��ص���
  recRobotStatus.CurrentDir = sStatus->CurrentDir;                        // �ϴ���ǰ�˶���
  recRobotStatus.ControlSystemEnergy = (float)(sStatus->ControlSystemEnergy); // �ϴ���ǰ��ص���
  recRobotStatus.DynamicSystemEnergy = recRobotStatus.ControlSystemEnergy;        // �ϴ���ǰ��ص���
  send_robot_status_data(&recRobotStatus);
}
/**
*@function E_MOTOR_STATE get_robot_command(char *buf)
*@brief    ��ȡָ��״̬�����ַ���תΪö��
*@param    buf ��ָ���ַ���
*@return   ö�ٽ��
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
*@brief    ����ģʽ�ַ���תö��ֵ
*@param    buf ����Ҫת�����ַ���
*@return   ö�ٽ��
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
*@brief    ��ָ���ö������ת�����ַ���
*@param    eRobotStatus ��ö������
*@param    buf ���ַ�����ַ
*@return   ��
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





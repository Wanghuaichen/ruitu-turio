/**
************************************************************************************************
* @file   		tcp_demo.c
* @author  		WIZnet Software Team 
* @version 		V1.0
* @date    		2015-02-14
* @brief   		TCP ��ʾ����
* @attention  
************************************************************************************************
**/

#include "include.h"
// char *s = "{\"name\":\"xiao hong\",\"age\":10}"; 
uint16_t count=0;//����socket�������ô���
uint16_t count2=0;//״̬socket�������ô���
uint16_t count3=0;
uint16_t local_port = 502;
uint16_t remote_port =  8888;
uint8_t remote_ip[4] = {192,168,1,106};
 char  cJSON_FORMAT_Buf[350];//���ջ���ת����cJSON�ַ����Ľ�����������������,ʹ��static��ʾֻ���ڱ��ļ��ڲ�ʹ�ô˱�����
 char  Sever_FORMAT_Buf[350];//���ջ��ߴ����͵ķ�����ʶ����ַ�����ʽ�Ľ�����������������

 char  cmdcJSON_FORMAT_Buf[350];//���ջ���ת����cJSON�ַ����Ľ�����������������,ʹ��static��ʾֻ���ڱ��ļ��ڲ�ʹ�ô˱�����
 char  cmdSever_FORMAT_Buf[350];//���ջ��ߴ����͵ķ�����ʶ����ַ�����ʽ�Ľ�����������������



//---------------------ȫ�ֱ�������------------------------------------------------



ROBOStatus_TypeDef ROBOStatus_TypeDefStructure;//�ϴ�����λ����״̬�ṹ�壬ȫ�ֱ���
ROBOCmd_TypeDef Cmd_From_Server;//���յ�������
Hello_Ack_TypeDef Ack_From_Server;//������ack���Я��ID�����Լ�ʱ���ַ�
Command_Ack_TypeDef Command_Ack_TypeDefStructure;//response "Set OK"
Hello_TypeDef Status_Hello_TypeStructure={"Robot001","RobotStatus"};//״̬�ṹ�壬���ڳ�ʼ����ʱ���͸�������
Hello_TypeDef Command_Hello_TypeStructure={"Robot001","RobotCommand"};//






/**************************************************************************
�������ܣ�����SOCKET����λ�������ĳ���
��ڲ�����
����  ֵ��
ע�⣺
**************************************************************************/
void Command_tcp_client(void)
{	
	CommandType CmdType;
	uint16_t len=0;//���յ������ݳ���
	switch(getSn_SR(SOCK_TCPC))								  				         /*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:											        		         /*socket���ڹر�״̬*/
			socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
		  break;
		
		case SOCK_INIT:													        	         /*socket���ڳ�ʼ��״̬*/
			connect(SOCK_TCPC,remote_ip,remote_port);                /*socket���ӷ�����*/ 
			count=0;
		  break;
		case SOCK_ESTABLISHED: 												             /*socket�������ӽ���״̬*/
			if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC, Sn_IR_CON); 							         /*��������жϱ�־λ*/
			}
			if(count++==1)//�����ϵ�һ�η����������͸���λ��
			{	
			  Trans_to_ServerFormat(cmdSever_FORMAT_Buf,HelloStatusCommand_to_cJSON( cmdcJSON_FORMAT_Buf,Command_Hello_TypeStructure));
				send(SOCK_TCPC,(uint8_t *)cmdSever_FORMAT_Buf,strlen(cmdSever_FORMAT_Buf));//ע��˴���SOCK_TCPC			
			}
			if(count>65534)//��ֹ�������
				count=2;
		  //send(SOCK_TCPC,buff,strlen(buff));								     /*��Server����״̬���ݣ�����*/
			
			len=getSn_RX_RSR(SOCK_TCPC); 								  	         /*����lenΪ�ѽ������ݵĳ���*/
			if(len>10)//���յ�����
			{
        //mymemset(cmdSever_FORMAT_Buf,'\0',350);
        recv(SOCK_TCPC,(uint8_t*)cmdSever_FORMAT_Buf,len); 		//*��������Server������,�����ݴ浽һ��������
        cmdSever_FORMAT_Buf[len]=0x00;/*����ַ���������*/	
        Parse_from_ServerFormat(cmdcJSON_FORMAT_Buf, cmdSever_FORMAT_Buf);//ȥ��****��#####������
        len=0;											                 
				CmdType=GetCommandFromServer(cmdcJSON_FORMAT_Buf);								
			}	
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket���ڵȴ��ر�״̬*/
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

void Status_tcp_client2(void)
{	
//�ڶ���socket���ڷ���״̬��������
	switch(getSn_SR(SOCK_TCPC2))								  				         /*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:											        		         /*socket���ڹر�״̬*/
			socket(SOCK_TCPC2,Sn_MR_TCP,local_port++,Sn_MR_ND);
			count2=0;
		  break;
		
		case SOCK_INIT:													        	         /*socket���ڳ�ʼ��״̬*/
			connect(SOCK_TCPC2,remote_ip,remote_port);                /*socket���ӷ�����*/ 
			count2=0;
		  break;
		
		case SOCK_ESTABLISHED: 												             /*socket�������ӽ���״̬*/
			if(getSn_IR(SOCK_TCPC2) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC2, Sn_IR_CON); 							         /*��������жϱ�־λ*/
			 }
			if(count2++==1)//�����ϵ�һ�η���hello status ���������͸���λ��
			{
				Trans_to_ServerFormat(Sever_FORMAT_Buf,HelloStatusCommand_to_cJSON( cJSON_FORMAT_Buf,Status_Hello_TypeStructure));				
				send(SOCK_TCPC2,(uint8_t *)Sever_FORMAT_Buf,strlen(Sever_FORMAT_Buf));		
        _TaskBattery.interval = 1000;
        _TaskBattery.state    = TASK_STATE_DELAY;
				break;         
			}
      if (count2 > 3)
      count2 = 3;										     
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket���ڵȴ��ر�״̬*/
			close(SOCK_TCPC2);
		  break;

	}
}












/**************************************************************************
�������ܣ��ַ����ָ����ȥ��֡ͷ*****��ȥ��֡β#####
��ڲ�����room Ϊ���ת��������ַ�����cJSON�ַ�������data[]Ϊת����*****{---------}#####
����  ֵ��{--------}
ע�⣺��ʹ��ʱ��roomΪ��ǰԼ���õ�ȫ�ֱ��������ļ���ΪcJSON_FORMAT_Buf[]
**************************************************************************/
char * Parse_from_ServerFormat(char * room, char data[])//�ַ������ܺ���
{

//	char * result=(char *)mymalloc(sizeof(char)*350);//������ʹresult���Ұָ�룿
char *	result = strtok(data,"*");
	      result = strtok(result,"#");
	strcpy(room,result);
	//myfree(result);
	return room;
}


/**************************************************************************
�������ܣ���һ���ַ�����ͷ������5��*��β������5��#��һ��������string�⺯���ģ�һ�����Լ�д�ġ�
��ڲ������ַ���{--------}
����  ֵ�����ܺ���ַ�������ʽΪ*****{--------}#####
ע�⣺strcat��ʹ�ù����е��ڴ�������⣬roomΪһ������ַ����ĵ�ַ
strcat��ƴ�ӷ���
**************************************************************************/
	char * Trans_to_ServerFormat(char *room,char data[])
{

		char * result=(char *)mymalloc(sizeof(char)*350);
		mymemset(result,0,350);//���������仰��ÿ��ִ�������������������room�ĺ��������µ����ݣ������Խ��Խ����why?��ʼ����
		strcat(result,"*****");
		strcat(result,data);
		strcat(result,"#####");
		strcpy(room,result);
		myfree(result);
	 return room;
}

	char * Trans_to_ServerFormat2(char *room,char data[])
{
	
	//int len1,len2;
	 int i,j,k;
   char s1[512] = "*****" ;
   char s2[6] = "#####" ;
   for(i=0;s1[i];i++);
     // len1=i;
   for(j=0;data[j];j++)
			s1[i++]=data[j];
   for(k=0;s2[k];k++)
			s1[i++]=s2[k];
		strcpy(room, s1);

	
	return room;
}
	
/**************************************************************************
�������ܣ�JSON�ַ������ɣ�����״̬��ʽ��Hello_Ack_TypeDef�ṹ��ת����һ��JSON���ַ���
��ڲ�����Hello_Ack_TypeDef���͵�״̬�ṹ��
����  ֵ����Ӧ��JSON�ַ���
**************************************************************************/

char * CommandAck_to_cJSON( char * cJSONROOM, Command_Ack_TypeDef  Acknowledge)//��ڲ���Ϊ״̬�ṹ�壬����ֵΪһ��cJSON��ʽ���ַ���
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//����һ��������״̬��JSON����
	cJSON_AddItemToObject(root, "Response", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"Command",Acknowledge.Command);
	cJSON_AddStringToObject(subroot,"Result",Acknowledge.Result);	
	result=cJSON_PrintUnformatted(root);
	strcpy(cJSONROOM,result);
	cJSON_Delete(root);
	//cJSON_Delete(subroot);
	myfree(result);
	
	return cJSONROOM;

}
/**************************************************************************
�������ܣ�//���ֽṹ������JSON
��ڲ�����Hello_TypeDef���͵�״̬�ṹ��
����  ֵ����Ӧ��JSON�ַ���
**************************************************************************/
	
char * HelloStatusCommand_to_cJSON( char * cJSONROOM, Hello_TypeDef  StatusCmd)
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//����һ��������״̬��JSON����
	cJSON_AddItemToObject(root, "Hello", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"ID",StatusCmd.ID);
	cJSON_AddStringToObject(subroot,"Type",StatusCmd.Type);	
	result=cJSON_PrintUnformatted(root);
	strcpy(cJSONROOM,result);
	cJSON_Delete(root);
	cJSON_Delete(subroot);
	myfree(result);
	
	return cJSONROOM;

}		
	
	
/**************************************************************************
�������ܣ�״̬����JSON
��ڲ�����ROBOStatus_TypeDef���͵�״̬�ṹ��
����  ֵ����Ӧ��JSON�ַ���
//log;
20180523�����Է��ִ˺�������48��֮��ͱ����ˣ����ص��ַ��������룬��������Сʱ�������ڴ�û���ͷţ�cJSON_PrintUnformatted������ʹ����mymalloc����
**************************************************************************/
	
char * Status_to_cJSON( char * cJSONROOM,ROBOStatus_TypeDef status)//����һ��������ָ��
{
	 char *result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//����һ��������״̬��JSON����
	subroot=cJSON_CreateObject();
	
		
	cJSON_AddStringToObject(subroot,"RunStatus",status.RunStatus);
	cJSON_AddStringToObject(subroot,"CurrentTime",status.CurrentTime);	
	cJSON_AddNumberToObject(subroot,"CurrentPosition",status.CurrentPositiont);
	cJSON_AddNumberToObject(subroot,"CurrentSpeed",status.CurrentSpeed);
	cJSON_AddNumberToObject(subroot,"RunningCount",status.RunningCount);	
	cJSON_AddNumberToObject(subroot,"CurrentTemp",status.CurrentTemp);
	cJSON_AddNumberToObject(subroot,"CurrentVoltage",status.CurrentVoltage);	
	cJSON_AddNumberToObject(subroot,"CurrentAmp",status.CurrentAmp);
	cJSON_AddNumberToObject(subroot,"CurrentDir",status.CurrentDir);	
	cJSON_AddNumberToObject(subroot,"ControlSystemEnergy",status.ControlSystemEnergy);
	cJSON_AddNumberToObject(subroot,"DynamicSystemEnergy",status.DynamicSystemEnergy);
  cJSON_AddItemToObject(root, "RobotStatus", subroot);
	result=cJSON_PrintUnformatted(root);
	strcpy(cJSONROOM,result);
	cJSON_Delete(root);
	//cJSON_Delete(subroot);
	myfree(result);//����Ҫ�У�Ҫ��Ȼ�ڴ����ʧȥһ�οռ䣬���ϵͳ����
	
	return cJSONROOM;//��Ҫָ���ŷ���һ���ֲ������ĵ�ַ�����Ƿǳ�Σ�յģ���Ϊ����������Ϻ������ַָ������ݾ���ʧ�ˡ�

}	
/**************************************************************************
�������ܣ�ɾHelloJSON_Ack_TypeDefָ��
��ڲ�����HelloJSON_Ack_TypeDef��ʽ���ַ�����
����  ֵ��������ָ��Ľṹ��
ע    �⣺�ӷ�������socket�õ����ַ����Ǽ����˵��ַ�������Ҫ���Ƚ��ܺ���ܷ���˺���
**************************************************************************/
void Delete_HelloJSON_Ack_TypeDef(HelloJSON_Ack_TypeDef  *jsonStructure)
{
	cJSON_Delete(jsonStructure->ID);
	cJSON_Delete(jsonStructure->Time);
}




/**************************************************************************
�������ܣ�ɾ��RobotJSON_CMD_TypeDefָ��
��ڲ�����RobotJSON_CMD_TypeDef��ʽ���ַ�����
����  ֵ��������ָ��Ľṹ��
ע    �⣺�ӷ�������socket�õ����ַ����Ǽ����˵��ַ�������Ҫ���Ƚ��ܺ���ܷ���˺���
**************************************************************************/

void Delete_RobotJSON_CMD_TypeDef(RobotJSON_CMD_TypeDef  *jsonStructure)
{
cJSON_Delete(jsonStructure->Command);
	cJSON_Delete(jsonStructure->EndPosition);
	cJSON_Delete(jsonStructure->RunCount);
	cJSON_Delete(jsonStructure->Speed);
	cJSON_Delete(jsonStructure->StartPosition);
	cJSON_Delete(jsonStructure->Step);
	cJSON_Delete(jsonStructure->TargetPosition);
	cJSON_Delete(jsonStructure->WorkMode);
}
	
/**************************************************************************
�������ܣ�JSON�ַ������������������ʽ����������λ�����͵�����
��ڲ�����JSON��ʽ���ַ�����
����  ֵ��������ָ��Ľṹ��
ע    �⣺�ӷ�������socket�õ����ַ����Ǽ����˵��ַ�������Ҫ���Ƚ��ܺ���ܷ���˺���
**************************************************************************/
CommandType GetCommandFromServer(char * JsonDataFromSocket)
{
	
//  ROBOCmd_TypeDef cmd;//ʹ�õ�ʱ����ȫ���ṹ�����
	
//	Hello_Ack_TypeDef hello_ack;//ʹ�õ�ʱ����ȫ�ֽ�ͷ�����
	CommandType cmdtype;
  RobotJSON_CMD_TypeDef json_cmd;	
	HelloJSON_Ack_TypeDef json_ack;
	
  cJSON *root,*command_root;

  root = 	cJSON_Parse(JsonDataFromSocket); //ʵ����JSON���󣨾�̬����	
	if(!root) 
			{
				 //printf("get cJSON  faild !\n");
				cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
			 } 
			else
				{
				 command_root = cJSON_GetObjectItem(root, "RobotCommand"); //ȡRobotCommand��ֵ��
					if(!command_root) 
						{ 
								//printf("No RobotCommand !\n"); 
							
							    command_root = cJSON_GetObjectItem(root, "HelloACK"); //ȡhellACK��ֵ��
									if(!command_root)
									{
										 //�������ķ���ֵ���� �Ȳ���RobotCommandҲ����HelloACK������ͷ���0
										     cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
									}
									else{
												
									
											json_ack.ID = cJSON_GetObjectItem(command_root,"ID");
											if(!json_ack.ID)
												{
													cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
												}
											else
												{
														 strcpy(Ack_From_Server.ID,json_ack.ID->valuestring);
												}
											json_ack.Time = cJSON_GetObjectItem(command_root,"Time");
											if(!json_ack.Time)
												{
													cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
												}
											else
												{
														 strcpy(Ack_From_Server.Time,json_ack.Time->valuestring);					
												}

												cmdtype=HELLO_ACK;//���û�У���ֱ�ӷ���0
									}
						}
					else
						{
							
							//�˶�����
							  json_cmd.Command =cJSON_GetObjectItem(command_root,"Command");
							if(!json_cmd.Command) 
								{ 
									//printf("no Command!\n");
										//cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0	
								} 
							else
								{
												//printf("Command is %s\r\n", robocmd.Command->valuestring);
												  strcpy(Cmd_From_Server.Command,json_cmd.Command->valuestring);
                    if(strcmp(Cmd_From_Server.Command,"Auto")==0||strcmp(Cmd_From_Server.Command,"Set")==0||strcmp(Cmd_From_Server.Command,"Dot")==0)
                    {
                          strcpy(Command_Ack_TypeDefStructure.Command,json_cmd.Command->valuestring);
                          strcpy(Command_Ack_TypeDefStructure.Result,"OK");
                          Trans_to_ServerFormat(Sever_FORMAT_Buf,CommandAck_to_cJSON( cJSON_FORMAT_Buf,Command_Ack_TypeDefStructure));
                          send(SOCK_TCPC,(uint8_t *)Sever_FORMAT_Buf,strlen(Sever_FORMAT_Buf));//ע��˴���SOCK_TCPC			
                    }

								}
							//�ٶ�ָ��
							json_cmd.Speed=cJSON_GetObjectItem(command_root,"Speed");
							if(!json_cmd.Speed) 
								{ 
									//printf("no Speed!\n"); 	
//									cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
												//printf("Speed is %d\r\n", json_cmd.Speed->valueint);
												Cmd_From_Server.Speed=json_cmd.Speed->valueint;
								}
							
								//���д���
								json_cmd.RunCount = cJSON_GetObjectItem(command_root,"RunTime");
							if(!json_cmd.RunCount) 
								{ 
									//printf("no RunCount!\n"); 
//										cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
											//printf("RunCount is %d\r\n",json_cmd.RunCount->valueint);
											Cmd_From_Server.RunCount=json_cmd.RunCount->valueint;
								}
								//��ʼλ��
									json_cmd.StartPosition = cJSON_GetObjectItem(command_root,"StartPosition");
							if(!json_cmd.StartPosition) 
								{ 
									//printf("no StartPosition!\n"); 
//										cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
											//printf("StartPosition is %d\r\n",json_cmd.StartPosition->valueint);
											Cmd_From_Server.StartPosition=json_cmd.StartPosition->valueint;
								}
								//����λ��
											json_cmd.EndPosition = cJSON_GetObjectItem(command_root,"EndPosition");
							if(!json_cmd.EndPosition) 
								{ 
									//printf("no EndPosition!\n"); 
//										cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
											//printf("EndPosition is %d\r\n",json_cmd.EndPosition->valueint);
											Cmd_From_Server.EndPosition=json_cmd.EndPosition->valueint;
								}
								//Ŀ��λ��TargetPosition
														json_cmd.TargetPosition = cJSON_GetObjectItem(command_root,"TargetPosition");
							if(!json_cmd.TargetPosition) 
								{ 
									//printf("no TargetPosition!\n"); 
//										cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
											//printf("TargetPosition is %d\r\n",json_cmd.TargetPosition->valueint);
											Cmd_From_Server.TargetPosition=json_cmd.TargetPosition->valueint;
								}
							
								//*����ģʽWorkMode;
								 json_cmd.WorkMode= cJSON_GetObjectItem(command_root,"WorkMode");
								if(!json_cmd.WorkMode) 
								{ 
									//printf("no WorkMode!\n"); 
//										cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
											//printf("WorkMode is %s\r\n",json_cmd.WorkMode->valuestring);
											 strcpy(Cmd_From_Server.WorkMode,json_cmd.WorkMode->valuestring);
								}
								//step
									 json_cmd.Step= cJSON_GetObjectItem(command_root,"Step");
								if(!json_cmd.Step) 
								{ 
									//printf("no Step!\n"); 
//										cmdtype=NOCOMMAND;//���û�У���ֱ�ӷ���0
								} 
							else
								{
											//printf("Step is %d\r\n",json_cmd.Step->valueint);
											Cmd_From_Server.Step=json_cmd.Step->valueint;
								}
								
								
								cmdtype= COMMAND;
								robot_rx_date_coversion(& Cmd_From_Server);
						} 
			 }

cJSON_Delete(root);
//myfree(command_root);
//myfree(json_cmd.Command);
//myfree(json_cmd.Command);
//myfree(json_cmd.EndPosition);
//myfree(json_cmd.RunCount);
//myfree(json_cmd.Speed);
//myfree(json_cmd.StartPosition);
//myfree(json_cmd.Step);
//myfree(json_cmd.TargetPosition);
//myfree(json_cmd.WorkMode);		 
//myfree(json_ack.ID);
//myfree(json_ack.Time);		 

//cJSON_Delete(command_root);
//cJSON_Delete(json_cmd.Command);
//cJSON_Delete(json_cmd.Command);
//cJSON_Delete(json_cmd.EndPosition);
//cJSON_Delete(json_cmd.RunCount);
//cJSON_Delete(json_cmd.Speed);
//cJSON_Delete(json_cmd.StartPosition);
//cJSON_Delete(json_cmd.Step);
//cJSON_Delete(json_cmd.TargetPosition);
//cJSON_Delete(json_cmd.WorkMode);		 
//cJSON_Delete(json_ack.ID);
//cJSON_Delete(json_ack.Time);		 
			 			 
			 
			 
//Delete_HelloJSON_Ack_TypeDef(&json_ack);
//Delete_RobotJSON_CMD_TypeDef(&json_cmd);

return cmdtype;
}

uint8_t send_robot_status_data(ROBOStatus_TypeDef *sRobotStatus)
{
  uint16_t len = 0;
  mymemset(cJSON_FORMAT_Buf,'\0',350);
  mymemset(Sever_FORMAT_Buf,'\0',350);
  Trans_to_ServerFormat(Sever_FORMAT_Buf,Status_to_cJSON( cJSON_FORMAT_Buf,*sRobotStatus));//ROBOStatus_TypeDefStructure����֮��ͨ�������������
  len=strlen(Sever_FORMAT_Buf);
  if(len>10)
  {
    send(SOCK_TCPC2,(uint8_t *)Sever_FORMAT_Buf,len);		//ע��˴���SOCK_TCPC2
    return 1;
  }
  return 0;
}


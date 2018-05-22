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

ROBOCmd_TypeDef Command_From_Server;//��λ�����͵�����
Hello_Ack_TypeDef Ack_From_Server;//��λ�����͵�Ӧ��ṹ��


Hello_TypeDef Status_Hello_TypeStructure={"Robot001","RobotStatus"};
Hello_TypeDef Command_Hello_TypeStructure={"Robot001","RobotCommand"};


/**************************************************************************
�������ܣ��ַ����ָ����ȥ��֡ͷ*****��ȥ��֡β#####
��ڲ�����*****{---------}#####
����  ֵ��{--------}
ע�⣺
**************************************************************************/
char * Parse_from_ServerFormat(char * data)//�ַ������ܺ���
{
char delims[]="*";
char delims2[]="#";
char *result = NULL;
result = strtok(data,delims);
result = strtok(result,delims2);
return result;
}


/**************************************************************************
�������ܣ������ַ�����������
��ڲ������ַ���
����  ֵ����
ע�⣺
**************************************************************************/


void TCP_Send( char * buf)
{
	send(SOCK_TCPC,(uint8_t*)buf,strlen(buf));								     	         /*��Server��������*/
}


/**************************************************************************
�������ܣ���һ���ַ�����ͷ������5��*��β������5��#
��ڲ������ַ���{--------}
����  ֵ�����ܺ���ַ�������ʽΪ*****{--------}#####
ע�⣺strcat��ʹ�ù����е��ڴ�������⣬roomΪһ������ַ����ĵ�ַ
**************************************************************************/
	char * Trans_to_ServerFormat(char *room,char * data)
{
	
	  char *FormatData=NULL;
	  //room=NULL;
		FormatData=(char *)malloc(sizeof(char)*400);
	
		strcat(FormatData,"*****");
		strcat(FormatData,data);
		strcat(FormatData,"#####");
	  room=FormatData;
		myfree(FormatData);
	return room;
}
	
/**************************************************************************
�������ܣ�JSON�ַ������ɣ�����״̬��ʽ��Hello_Ack_TypeDef�ṹ��ת����һ��JSON���ַ���
��ڲ�����Hello_Ack_TypeDef���͵�״̬�ṹ��
����  ֵ����Ӧ��JSON�ַ���
**************************************************************************/

char * CommandAck_to_cJSON( Command_Ack_TypeDef * Acknowledge)//��ڲ���Ϊ״̬�ṹ�壬����ֵΪһ��cJSON��ʽ���ַ���
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//����һ��������״̬��JSON����
	cJSON_AddItemToObject(root, "Response", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"Command",Acknowledge->Command);
	cJSON_AddStringToObject(subroot,"Result",Acknowledge->Result);	
	result=cJSON_Print(root);	
	cJSON_Delete(root);
	myfree(subroot);
	
	return result;

}
/**************************************************************************
�������ܣ�//���ֽṹ������JSON
��ڲ�����Hello_TypeDef���͵�״̬�ṹ��
����  ֵ����Ӧ��JSON�ַ���
**************************************************************************/
	
char * HelloStatusCommand_to_cJSON( Hello_TypeDef * StatusCmd)
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//����һ��������״̬��JSON����
	cJSON_AddItemToObject(root, "Hello", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"ID",StatusCmd->ID);
	cJSON_AddStringToObject(subroot,"Type",StatusCmd->Type);	
	result=cJSON_Print(root);	
	cJSON_Delete(root);
	myfree(subroot);
	
	return result;

}		
	
	
/**************************************************************************
�������ܣ�״̬����JSON
��ڲ�����ROBOStatus_TypeDef���͵�״̬�ṹ��
����  ֵ����Ӧ��JSON�ַ���
**************************************************************************/
	
char * Status_to_cJSON( ROBOStatus_TypeDef *status)
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//����һ��������״̬��JSON����
	cJSON_AddItemToObject(root, "RobotStatus", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"RunStatus",status->RunStatus);
	cJSON_AddStringToObject(subroot,"CurrentTime",status->CurrentTime);	
	cJSON_AddNumberToObject(subroot,"CurrentPosition",status->CurrentPositiont);
	cJSON_AddNumberToObject(subroot,"CurrentSpeed",status->CurrentSpeed);
	cJSON_AddNumberToObject(subroot,"RunningCount",status->RunningCount);	
	cJSON_AddNumberToObject(subroot,"CurrentTemp",status->CurrentTemp);
	cJSON_AddNumberToObject(subroot,"CurrentVoltage",status->CurrentVoltage);	
	cJSON_AddNumberToObject(subroot,"CurrentAmp",status->CurrentAmp);
	cJSON_AddNumberToObject(subroot,"CurrentDir",status->CurrentDir);	
	cJSON_AddNumberToObject(subroot,"ControlSystemEnergy",status->ControlSystemEnergy);
	cJSON_AddNumberToObject(subroot,"DynamicSystemEnergy",status->DynamicSystemEnergy);

	result=cJSON_Print(root);	
	cJSON_Delete(root);
	myfree(subroot);
	
	return result;

}	
	
	
	
/**************************************************************************
�������ܣ�JSON�ַ������������������ʽ����������λ�����͵�����
��ڲ�����JSON��ʽ���ַ�����
����  ֵ��������ָ��Ľṹ��
ע    �⣺�ӷ�������socket�õ����ַ����Ǽ����˵��ַ�������Ҫ���Ƚ��ܺ���ܷ���˺���
**************************************************************************/
	CommandType GetCommandFromServer(char * DataFromSocket)
{
	
  ROBOCmd_TypeDef cmd;//ʹ�õ�ʱ����ȫ���ṹ�����
	CommandType cmdtype;
	Hello_Ack_TypeDef hello_ack;//ʹ�õ�ʱ����ȫ�ֽ�ͷ�����
	
  RobotJSON_CMD_TypeDef json_cmd;
	
	JSON_Hello_Ack_TypeDef json_ack;
	
  cJSON *root,*command_root;

  root = 	cJSON_Parse(DataFromSocket); //ʵ����JSON���󣨾�̬����	
 if(!root) 
			{
				 //printf("get cJSON  faild !\n");
				return NOCOMMAND;//���û�У���ֱ�ӷ���0
			 } 
			else
				{
				 command_root = cJSON_GetObjectItem(root, "RobotCommand"); //ȡRobotCommand��ֵ��
					if(!command_root) 
						{ 
								//printf("No RobotCommand !\n"); 
							
							    command_root = cJSON_GetObjectItem(root, "HelloACK"); //ȡhellACK��ֵ��
									if(!command_root)
										 //�������ķ���ֵ���� �Ȳ���RobotCommandҲ����HelloACK������ͷ���0
										      return NOCOMMAND;//���û�У���ֱ�ӷ���0
									
									else{
												
									
											json_ack.ID = cJSON_GetObjectItem(command_root,"ID");
											if(!json_ack.ID)
												{
											
												}
											else
												{
														hello_ack.ID=json_ack.ID->valuestring;
												}
											json_ack.Time = cJSON_GetObjectItem(command_root,"Time");
											if(!json_ack.Time)
												{
											
												}
											else
												{
														hello_ack.Time=json_ack.Time->valuestring;					
												}
												return HELLO_ACK;
												
									}
						}
					else
						{
							
							//�˶�����
							  json_cmd.Command =cJSON_GetObjectItem(command_root,"Command");
							if(!json_cmd.Command) 
								{ 
									//printf("no Command!\n"); 
								} 
							else
								{
												//printf("Command is %s\r\n", robocmd.Command->valuestring);
												cmd.Command=json_cmd.Command->valuestring;
								}
							//�ٶ�ָ��
							json_cmd.Speed=cJSON_GetObjectItem(command_root,"Speed");
							if(!json_cmd.Speed) 
								{ 
									//printf("no Speed!\n"); 
								} 
							else
								{
												//printf("Speed is %d\r\n", json_cmd.Speed->valueint);
												cmd.Speed=json_cmd.Speed->valueint;
								}
							
								//���д���
								json_cmd.RunCount = cJSON_GetObjectItem(command_root,"RunCount");
							if(!json_cmd.RunCount) 
								{ 
									//printf("no RunCount!\n"); 
								} 
							else
								{
											//printf("RunCount is %d\r\n",json_cmd.RunCount->valueint);
											cmd.RunCount=json_cmd.RunCount->valueint;
								}
								//��ʼλ��
									json_cmd.StartPosition = cJSON_GetObjectItem(command_root,"StartPosition");
							if(!json_cmd.StartPosition) 
								{ 
									//printf("no StartPosition!\n"); 
								} 
							else
								{
											//printf("StartPosition is %d\r\n",json_cmd.StartPosition->valueint);
											cmd.StartPosition=json_cmd.StartPosition->valueint;
								}
								//����λ��
											json_cmd.EndPosition = cJSON_GetObjectItem(command_root,"EndPosition");
							if(!json_cmd.EndPosition) 
								{ 
									//printf("no EndPosition!\n"); 
								} 
							else
								{
											//printf("EndPosition is %d\r\n",json_cmd.EndPosition->valueint);
											cmd.EndPosition=json_cmd.EndPosition->valueint;
								}
								//Ŀ��λ��TargetPosition
														json_cmd.TargetPosition = cJSON_GetObjectItem(command_root,"TargetPosition");
							if(!json_cmd.TargetPosition) 
								{ 
									//printf("no TargetPosition!\n"); 
								} 
							else
								{
											//printf("TargetPosition is %d\r\n",json_cmd.TargetPosition->valueint);
											cmd.TargetPosition=json_cmd.TargetPosition->valueint;
								}
							
								//*����ģʽWorkMode;
								 json_cmd.WorkMode= cJSON_GetObjectItem(command_root,"WorkMode");
								if(!json_cmd.WorkMode) 
								{ 
									//printf("no WorkMode!\n"); 
								} 
							else
								{
											//printf("WorkMode is %s\r\n",json_cmd.WorkMode->valuestring);
											cmd.WorkMode=json_cmd.WorkMode->valuestring;
								}
								//step
									 json_cmd.Step= cJSON_GetObjectItem(command_root,"Step");
								if(!json_cmd.Step) 
								{ 
									//printf("no Step!\n"); 
								} 
							else
								{
											//printf("Step is %d\r\n",json_cmd.Step->valueint);
											cmd.Step=json_cmd.Step->valueint;
								}
								return COMMAND;
								
						} 
			 }

return cmdtype;
       
}


/**
************************************************************************************************
* @file   		tcp_demo.c
* @author  		WIZnet Software Team 
* @version 		V1.0
* @date    		2015-02-14
* @brief   		TCP 演示函数
* @attention  
************************************************************************************************
**/

#include "include.h"
// char *s = "{\"name\":\"xiao hong\",\"age\":10}"; 

ROBOCmd_TypeDef Command_From_Server;//上位机发送的命令
Hello_Ack_TypeDef Ack_From_Server;//上位机发送的应答结构体


Hello_TypeDef Status_Hello_TypeStructure={"Robot001","RobotStatus"};
Hello_TypeDef Command_Hello_TypeStructure={"Robot001","RobotCommand"};


/**************************************************************************
函数功能：字符串分割函数，去掉帧头*****，去掉帧尾#####
入口参数：*****{---------}#####
返回  值：{--------}
注意：
**************************************************************************/
char * Parse_from_ServerFormat(char * data)//字符串解密函数
{
char delims[]="*";
char delims2[]="#";
char *result = NULL;
result = strtok(data,delims);
result = strtok(result,delims2);
return result;
}


/**************************************************************************
函数功能：发送字符串到服务器
入口参数：字符串
返回  值：无
注意：
**************************************************************************/


void TCP_Send( char * buf)
{
	send(SOCK_TCPC,(uint8_t*)buf,strlen(buf));								     	         /*向Server发送数据*/
}


/**************************************************************************
函数功能：加一个字符串的头部增加5个*，尾部增加5个#
入口参数：字符串{--------}
返回  值：加密后的字符串，形式为*****{--------}#####
注意：strcat的使用过程中的内存管理问题，room为一个存放字符串的地址
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
函数功能：JSON字符串生成，按照状态格式，Hello_Ack_TypeDef结构体转换成一个JSON的字符串
入口参数：Hello_Ack_TypeDef类型的状态结构体
返回  值：对应的JSON字符串
**************************************************************************/

char * CommandAck_to_cJSON( Command_Ack_TypeDef * Acknowledge)//入口参数为状态结构体，返回值为一个cJSON格式的字符串
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//创建一个机器人状态的JSON对象
	cJSON_AddItemToObject(root, "Response", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"Command",Acknowledge->Command);
	cJSON_AddStringToObject(subroot,"Result",Acknowledge->Result);	
	result=cJSON_Print(root);	
	cJSON_Delete(root);
	myfree(subroot);
	
	return result;

}
/**************************************************************************
函数功能：//握手结构体生成JSON
入口参数：Hello_TypeDef类型的状态结构体
返回  值：对应的JSON字符串
**************************************************************************/
	
char * HelloStatusCommand_to_cJSON( Hello_TypeDef * StatusCmd)
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//创建一个机器人状态的JSON对象
	cJSON_AddItemToObject(root, "Hello", subroot=cJSON_CreateObject());
		
	cJSON_AddStringToObject(subroot,"ID",StatusCmd->ID);
	cJSON_AddStringToObject(subroot,"Type",StatusCmd->Type);	
	result=cJSON_Print(root);	
	cJSON_Delete(root);
	myfree(subroot);
	
	return result;

}		
	
	
/**************************************************************************
函数功能：状态生成JSON
入口参数：ROBOStatus_TypeDef类型的状态结构体
返回  值：对应的JSON字符串
**************************************************************************/
	
char * Status_to_cJSON( ROBOStatus_TypeDef *status)
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//创建一个机器人状态的JSON对象
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
函数功能：JSON字符串解析，按照命令格式，解析出上位机发送的命令
入口参数：JSON格式的字符串，
返回  值：机器人指令的结构体
注    意：从服务器的socket得到的字符串是加密了的字符串，需要首先解密后才能放入此函数
**************************************************************************/
	CommandType GetCommandFromServer(char * DataFromSocket)
{
	
  ROBOCmd_TypeDef cmd;//使用的时候用全部结构体代替
	CommandType cmdtype;
	Hello_Ack_TypeDef hello_ack;//使用的时候用全局接头体代替
	
  RobotJSON_CMD_TypeDef json_cmd;
	
	JSON_Hello_Ack_TypeDef json_ack;
	
  cJSON *root,*command_root;

  root = 	cJSON_Parse(DataFromSocket); //实例化JSON对象（静态对象）	
 if(!root) 
			{
				 //printf("get cJSON  faild !\n");
				return NOCOMMAND;//如果没有，就直接返回0
			 } 
			else
				{
				 command_root = cJSON_GetObjectItem(root, "RobotCommand"); //取RobotCommand键值对
					if(!command_root) 
						{ 
								//printf("No RobotCommand !\n"); 
							
							    command_root = cJSON_GetObjectItem(root, "HelloACK"); //取hellACK键值对
									if(!command_root)
										 //将函数的返回值改下 既不是RobotCommand也不是HelloACK的情况就返回0
										      return NOCOMMAND;//如果没有，就直接返回0
									
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
							
							//运动命令
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
							//速度指令
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
							
								//运行次数
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
								//开始位置
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
								//结束位置
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
								//目标位置TargetPosition
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
							
								//*工作模式WorkMode;
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


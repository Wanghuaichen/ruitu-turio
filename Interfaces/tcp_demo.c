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
uint16_t count=0;//命令socket函数调用次数
uint16_t count2=0;//状态socket函数调用次数
uint16_t count3=0;
uint16_t local_port = 502;
uint16_t remote_port =  8888;
uint8_t remote_ip[4] = {192,168,1,106};
 char  cJSON_FORMAT_Buf[350];//接收或者转化的cJSON字符串的结果放在这个缓存里面,使用static表示只能在本文件内部使用此变量！
 char  Sever_FORMAT_Buf[350];//接收或者待发送的服务器识别的字符串格式的结果放在这个缓存里面

 char  cmdcJSON_FORMAT_Buf[350];//接收或者转化的cJSON字符串的结果放在这个缓存里面,使用static表示只能在本文件内部使用此变量！
 char  cmdSever_FORMAT_Buf[350];//接收或者待发送的服务器识别的字符串格式的结果放在这个缓存里面



//---------------------全局变量定义------------------------------------------------



ROBOStatus_TypeDef ROBOStatus_TypeDefStructure;//上传给上位机的状态结构体，全局变量
ROBOCmd_TypeDef Cmd_From_Server;//接收到的命令
Hello_Ack_TypeDef Ack_From_Server;//反馈的ack命令，携带ID号码以及时间字符
Command_Ack_TypeDef Command_Ack_TypeDefStructure;//response "Set OK"
Hello_TypeDef Status_Hello_TypeStructure={"Robot001","RobotStatus"};//状态结构体，用于初始化的时候发送给服务器
Hello_TypeDef Command_Hello_TypeStructure={"Robot001","RobotCommand"};//






/**************************************************************************
函数功能：命令SOCKET与上位机交互的程序
入口参数：
返回  值：
注意：
**************************************************************************/
void Command_tcp_client(void)
{	
	CommandType CmdType;
	uint16_t len=0;//接收到的数据长度
	switch(getSn_SR(SOCK_TCPC))								  				         /*获取socket的状态*/
	{
		case SOCK_CLOSED:											        		         /*socket处于关闭状态*/
			socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
		  break;
		
		case SOCK_INIT:													        	         /*socket处于初始化状态*/
			connect(SOCK_TCPC,remote_ip,remote_port);                /*socket连接服务器*/ 
			count=0;
		  break;
		case SOCK_ESTABLISHED: 												             /*socket处于连接建立状态*/
			if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC, Sn_IR_CON); 							         /*清除接收中断标志位*/
			}
			if(count++==1)//连接上第一次发送连接类型给上位机
			{	
			  Trans_to_ServerFormat(cmdSever_FORMAT_Buf,HelloStatusCommand_to_cJSON( cmdcJSON_FORMAT_Buf,Command_Hello_TypeStructure));
				send(SOCK_TCPC,(uint8_t *)cmdSever_FORMAT_Buf,strlen(cmdSever_FORMAT_Buf));//注意此处是SOCK_TCPC			
			}
			if(count>65534)//防止次数溢出
				count=2;
		  //send(SOCK_TCPC,buff,strlen(buff));								     /*向Server发送状态数据，数据*/
			
			len=getSn_RX_RSR(SOCK_TCPC); 								  	         /*定义len为已接收数据的长度*/
			if(len>10)//接收到数据
			{
        //mymemset(cmdSever_FORMAT_Buf,'\0',350);
        recv(SOCK_TCPC,(uint8_t*)cmdSever_FORMAT_Buf,len); 		//*接收来自Server的数据,把数据存到一个缓存内
        cmdSever_FORMAT_Buf[len]=0x00;/*添加字符串结束符*/	
        Parse_from_ServerFormat(cmdcJSON_FORMAT_Buf, cmdSever_FORMAT_Buf);//去掉****与#####的作用
        len=0;											                 
				CmdType=GetCommandFromServer(cmdcJSON_FORMAT_Buf);								
			}	
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket处于等待关闭状态*/
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

void Status_tcp_client2(void)
{	
//第二个socket用于发送状态给服务器
	switch(getSn_SR(SOCK_TCPC2))								  				         /*获取socket的状态*/
	{
		case SOCK_CLOSED:											        		         /*socket处于关闭状态*/
			socket(SOCK_TCPC2,Sn_MR_TCP,local_port++,Sn_MR_ND);
			count2=0;
		  break;
		
		case SOCK_INIT:													        	         /*socket处于初始化状态*/
			connect(SOCK_TCPC2,remote_ip,remote_port);                /*socket连接服务器*/ 
			count2=0;
		  break;
		
		case SOCK_ESTABLISHED: 												             /*socket处于连接建立状态*/
			if(getSn_IR(SOCK_TCPC2) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC2, Sn_IR_CON); 							         /*清除接收中断标志位*/
			 }
			if(count2++==1)//连接上第一次发送hello status 等连接类型给上位机
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
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket处于等待关闭状态*/
			close(SOCK_TCPC2);
		  break;

	}
}












/**************************************************************************
函数功能：字符串分割函数，去掉帧头*****，去掉帧尾#####
入口参数：room 为存放转换结果的字符串（cJSON字符串），data[]为转化的*****{---------}#####
返回  值：{--------}
注意：在使用时候，room为提前约定好的全局变量，本文件中为cJSON_FORMAT_Buf[]
**************************************************************************/
char * Parse_from_ServerFormat(char * room, char data[])//字符串解密函数
{

//	char * result=(char *)mymalloc(sizeof(char)*350);//这样会使result变成野指针？
char *	result = strtok(data,"*");
	      result = strtok(result,"#");
	strcpy(room,result);
	//myfree(result);
	return room;
}


/**************************************************************************
函数功能：加一个字符串的头部增加5个*，尾部增加5个#，一个是利用string库函数的，一个是自己写的。
入口参数：字符串{--------}
返回  值：加密后的字符串，形式为*****{--------}#####
注意：strcat的使用过程中的内存管理问题，room为一个存放字符串的地址
strcat的拼接方法
**************************************************************************/
	char * Trans_to_ServerFormat(char *room,char data[])
{

		char * result=(char *)mymalloc(sizeof(char)*350);
		mymemset(result,0,350);//如果不加这句话，每次执行这个函数，都会是在room的后面增加新的内容，结果是越来越长，why?初始化，
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
函数功能：JSON字符串生成，按照状态格式，Hello_Ack_TypeDef结构体转换成一个JSON的字符串
入口参数：Hello_Ack_TypeDef类型的状态结构体
返回  值：对应的JSON字符串
**************************************************************************/

char * CommandAck_to_cJSON( char * cJSONROOM, Command_Ack_TypeDef  Acknowledge)//入口参数为状态结构体，返回值为一个cJSON格式的字符串
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//创建一个机器人状态的JSON对象
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
函数功能：//握手结构体生成JSON
入口参数：Hello_TypeDef类型的状态结构体
返回  值：对应的JSON字符串
**************************************************************************/
	
char * HelloStatusCommand_to_cJSON( char * cJSONROOM, Hello_TypeDef  StatusCmd)
{
	char * result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//创建一个机器人状态的JSON对象
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
函数功能：状态生成JSON
入口参数：ROBOStatus_TypeDef类型的状态结构体
返回  值：对应的JSON字符串
//log;
20180523：调试发现此函数调用48次之后就崩溃了，返回的字符串是乱码，搞了两个小时发现是内存没有释放，cJSON_PrintUnformatted（）中使用了mymalloc函数
**************************************************************************/
	
char * Status_to_cJSON( char * cJSONROOM,ROBOStatus_TypeDef status)//传入一个变量的指针
{
	 char *result;
	cJSON *root,*subroot;
	root=cJSON_CreateObject();//创建一个机器人状态的JSON对象
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
	myfree(result);//必须要有，要不然内存里会失去一段空间，最后系统崩溃
	
	return cJSONROOM;//不要指望着返回一个局部变量的地址，这是非常危险的，因为函数调用完毕后这个地址指向的内容就消失了。

}	
/**************************************************************************
函数功能：删HelloJSON_Ack_TypeDef指针
入口参数：HelloJSON_Ack_TypeDef格式的字符串，
返回  值：机器人指令的结构体
注    意：从服务器的socket得到的字符串是加密了的字符串，需要首先解密后才能放入此函数
**************************************************************************/
void Delete_HelloJSON_Ack_TypeDef(HelloJSON_Ack_TypeDef  *jsonStructure)
{
	cJSON_Delete(jsonStructure->ID);
	cJSON_Delete(jsonStructure->Time);
}




/**************************************************************************
函数功能：删除RobotJSON_CMD_TypeDef指针
入口参数：RobotJSON_CMD_TypeDef格式的字符串，
返回  值：机器人指令的结构体
注    意：从服务器的socket得到的字符串是加密了的字符串，需要首先解密后才能放入此函数
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
函数功能：JSON字符串解析，按照命令格式，解析出上位机发送的命令
入口参数：JSON格式的字符串，
返回  值：机器人指令的结构体
注    意：从服务器的socket得到的字符串是加密了的字符串，需要首先解密后才能放入此函数
**************************************************************************/
CommandType GetCommandFromServer(char * JsonDataFromSocket)
{
	
//  ROBOCmd_TypeDef cmd;//使用的时候用全部结构体代替
	
//	Hello_Ack_TypeDef hello_ack;//使用的时候用全局接头体代替
	CommandType cmdtype;
  RobotJSON_CMD_TypeDef json_cmd;	
	HelloJSON_Ack_TypeDef json_ack;
	
  cJSON *root,*command_root;

  root = 	cJSON_Parse(JsonDataFromSocket); //实例化JSON对象（静态对象）	
	if(!root) 
			{
				 //printf("get cJSON  faild !\n");
				cmdtype=NOCOMMAND;//如果没有，就直接返回0
			 } 
			else
				{
				 command_root = cJSON_GetObjectItem(root, "RobotCommand"); //取RobotCommand键值对
					if(!command_root) 
						{ 
								//printf("No RobotCommand !\n"); 
							
							    command_root = cJSON_GetObjectItem(root, "HelloACK"); //取hellACK键值对
									if(!command_root)
									{
										 //将函数的返回值改下 既不是RobotCommand也不是HelloACK的情况就返回0
										     cmdtype=NOCOMMAND;//如果没有，就直接返回0
									}
									else{
												
									
											json_ack.ID = cJSON_GetObjectItem(command_root,"ID");
											if(!json_ack.ID)
												{
													cmdtype=NOCOMMAND;//如果没有，就直接返回0
												}
											else
												{
														 strcpy(Ack_From_Server.ID,json_ack.ID->valuestring);
												}
											json_ack.Time = cJSON_GetObjectItem(command_root,"Time");
											if(!json_ack.Time)
												{
													cmdtype=NOCOMMAND;//如果没有，就直接返回0
												}
											else
												{
														 strcpy(Ack_From_Server.Time,json_ack.Time->valuestring);					
												}

												cmdtype=HELLO_ACK;//如果没有，就直接返回0
									}
						}
					else
						{
							
							//运动命令
							  json_cmd.Command =cJSON_GetObjectItem(command_root,"Command");
							if(!json_cmd.Command) 
								{ 
									//printf("no Command!\n");
										//cmdtype=NOCOMMAND;//如果没有，就直接返回0	
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
                          send(SOCK_TCPC,(uint8_t *)Sever_FORMAT_Buf,strlen(Sever_FORMAT_Buf));//注意此处是SOCK_TCPC			
                    }

								}
							//速度指令
							json_cmd.Speed=cJSON_GetObjectItem(command_root,"Speed");
							if(!json_cmd.Speed) 
								{ 
									//printf("no Speed!\n"); 	
//									cmdtype=NOCOMMAND;//如果没有，就直接返回0
								} 
							else
								{
												//printf("Speed is %d\r\n", json_cmd.Speed->valueint);
												Cmd_From_Server.Speed=json_cmd.Speed->valueint;
								}
							
								//运行次数
								json_cmd.RunCount = cJSON_GetObjectItem(command_root,"RunTime");
							if(!json_cmd.RunCount) 
								{ 
									//printf("no RunCount!\n"); 
//										cmdtype=NOCOMMAND;//如果没有，就直接返回0
								} 
							else
								{
											//printf("RunCount is %d\r\n",json_cmd.RunCount->valueint);
											Cmd_From_Server.RunCount=json_cmd.RunCount->valueint;
								}
								//开始位置
									json_cmd.StartPosition = cJSON_GetObjectItem(command_root,"StartPosition");
							if(!json_cmd.StartPosition) 
								{ 
									//printf("no StartPosition!\n"); 
//										cmdtype=NOCOMMAND;//如果没有，就直接返回0
								} 
							else
								{
											//printf("StartPosition is %d\r\n",json_cmd.StartPosition->valueint);
											Cmd_From_Server.StartPosition=json_cmd.StartPosition->valueint;
								}
								//结束位置
											json_cmd.EndPosition = cJSON_GetObjectItem(command_root,"EndPosition");
							if(!json_cmd.EndPosition) 
								{ 
									//printf("no EndPosition!\n"); 
//										cmdtype=NOCOMMAND;//如果没有，就直接返回0
								} 
							else
								{
											//printf("EndPosition is %d\r\n",json_cmd.EndPosition->valueint);
											Cmd_From_Server.EndPosition=json_cmd.EndPosition->valueint;
								}
								//目标位置TargetPosition
														json_cmd.TargetPosition = cJSON_GetObjectItem(command_root,"TargetPosition");
							if(!json_cmd.TargetPosition) 
								{ 
									//printf("no TargetPosition!\n"); 
//										cmdtype=NOCOMMAND;//如果没有，就直接返回0
								} 
							else
								{
											//printf("TargetPosition is %d\r\n",json_cmd.TargetPosition->valueint);
											Cmd_From_Server.TargetPosition=json_cmd.TargetPosition->valueint;
								}
							
								//*工作模式WorkMode;
								 json_cmd.WorkMode= cJSON_GetObjectItem(command_root,"WorkMode");
								if(!json_cmd.WorkMode) 
								{ 
									//printf("no WorkMode!\n"); 
//										cmdtype=NOCOMMAND;//如果没有，就直接返回0
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
//										cmdtype=NOCOMMAND;//如果没有，就直接返回0
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
  Trans_to_ServerFormat(Sever_FORMAT_Buf,Status_to_cJSON( cJSON_FORMAT_Buf,*sRobotStatus));//ROBOStatus_TypeDefStructure更新之后通过这个函数发送
  len=strlen(Sever_FORMAT_Buf);
  if(len>10)
  {
    send(SOCK_TCPC2,(uint8_t *)Sever_FORMAT_Buf,len);		//注意此处是SOCK_TCPC2
    return 1;
  }
  return 0;
}


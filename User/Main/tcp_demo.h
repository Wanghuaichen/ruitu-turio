#ifndef __TCP_DEMO_H
#define __TCP_DEMO_H
#include "main.h"
#include "cJSON.h"
extern uint16_t W5500_tcp_server_port;
extern char * ROOM;


typedef struct JSONcommand
	{
			 cJSON *Command;
			 cJSON *Speed;
			 cJSON *RunCount;
			 cJSON *StartPosition;
			 cJSON *EndPosition;
			 cJSON *TargetPosition;
			 cJSON *WorkMode;
			 cJSON *Step;
  } RobotJSON_CMD_TypeDef;
//-----------------------命令socket
	//发送给上位机的握手确认类型结构体,状态socket第一次连接需要发送此类型数据给上位机
typedef struct InitConnect{	
		char 	*		   ID;//机器人的ID号
		char  *      Type;//机器人的状态，对于命令socket连接，此值为"RobotCommand"，对于状态socket连接，此值为“RobotStatus”

	} ShakeHandInit_TypeDef;

	
//命令socket连接成功，上位机发送ID和以及同步时间
	typedef struct InitConnectAck{	
		char 	*		   ID;
		char  *      Time;

	} ShakeHandAck_TypeDef;
	
//-----------------------状态socket,连接上发送一个ShakeHandInit_TypeDef后就直接发送ROBOStatus_TypeDef类型的数据
	
	

	//接收来自服务器的命令，类型结构体
//typedef struct ROBOcommand{	
//		char 	*		   Command;
//		unsigned int Speed;
//		unsigned int RunCount;
//		unsigned int StartPosition;
//		unsigned int EndPosition;
//		unsigned int TargetPosition;
//		char  *		   WorkMode;
//		unsigned int Step;
//	} ROBOCmd_TypeDef;

	
	
	//用于上传状态给服务器，状态类型结构体
typedef struct ROBOstatus{	
	 char 	*	 RunStatus;
	 char   *  CurrentTime;
	  int      			 		 CurrentPositiont;
		unsigned short int CurrentSpeed;
		unsigned short int RunningCount;
		char 				       CurrentTemp;
		float  				 	   CurrentVoltage;
		float						   CurrentAmp;
		unsigned char			 CurrentDir;
		unsigned char			 ControlSystemEnergy;
		unsigned char			 DynamicSystemEnergy;
		unsigned short int Step;
	} ROBOStatus_TypeDef;

void Command_tcp_server(void);//TCP Server回环演示函数
void Status_tcp_client2(void);//TCP Clinet回环演示函数
void Command_tcp_client(void);//TCP Clinet回环演示函数

ROBOCmd_TypeDef GetCommandFromServer(char * DataFromSocket);//服务器命令数据解析，返回值为命令结构体,参数为从socket接收的数据并且已经做了初步的抽希（去掉*****与#####）

char * Status_to_cJSON( ROBOStatus_TypeDef *status);//入口参数为状态结构体，返回值为一个cJSON格式的字符串

char * Trans_to_ServerFormat(char *room,char * data);//字符串加密函数

char * Parse_from_ServerFormat(char * data);//字符串解密函数
	
//命令socket命令接收函数，返回接收到的命令字符串
ROBOCmd_TypeDef * GetCommand_from_Server(void);	
	
//命令socket响应接收函数，返回接收到的响应命令指针
ShakeHandAck_TypeDef * GetAck_from_Server(void);		



	
	
//状态及握手响应发送字符串函数，返回握手的字符串
void TCP_Send( uint8_t * buf);

#endif 


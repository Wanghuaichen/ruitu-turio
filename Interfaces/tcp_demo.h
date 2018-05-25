#ifndef __TCP_DEMO_H
#define __TCP_DEMO_H
#include "include.h"
extern uint16_t W5500_tcp_server_port;
//extern char * ROOM;
//extern uint8 buff[2048]="大家好，我是连接1";				                              	         /*定义一个2KB的缓存*/


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

typedef struct JSON_InitConnectAck
	{
			 cJSON *ID;
			 cJSON *Time;

  } HelloJSON_Ack_TypeDef;
	

	
	
	
//-----------------------命令socket
	//发送给上位机的握手确认类型结构体,状态socket第一次连接需要发送此类型数据给上位机
typedef struct InitConnect{	
		char 	 ID[15];//机器人的ID号
		char  Type[15];//机器人的状态，对于命令socket连接，此值为"RobotCommand"，对于状态socket连接，此值为“RobotStatus”

	} Hello_TypeDef;

	
//命令socket连接成功，上位机发送ID和以及同步时间
	typedef struct InitConnectAck{	
		char 	 ID[15];
		char   Time[20];

	} Hello_Ack_TypeDef;
	
	
	//命令socket响应结构体
	typedef struct CommandAck{	
		char 	Command[10];
		char  Result[10];

	} Command_Ack_TypeDef;
	
//-----------------------状态socket,连接上发送一个ShakeHandInit_TypeDef后就直接发送ROBOStatus_TypeDef类型的数据
	
	

	//接收来自服务器的命令，类型结构体
#pragma pack(1)	
typedef struct ROBOcommand{	
		char 	Command[10];
		uint16_t  Speed;
		uint32_t RunCount;
		uint32_t StartPosition;
		uint32_t EndPosition;
		uint32_t TargetPosition;
		char  WorkMode[20];
		uint16_t Step;
	} ROBOCmd_TypeDef;
#pragma pack()	
	
	//用于上传状态给服务器，状态类型结构体
#pragma pack(1)
typedef struct ROBOstatus{	
	  char 						   RunStatus[10];
		char  						 CurrentTime[20];
	  uint32_t      	   CurrentPositiont;
		uint16_t           CurrentSpeed;
		uint32_t           RunningCount;
		uint8_t            CurrentTemp;
		float  				 	   CurrentVoltage;
		float						   CurrentAmp;
		uint8_t					   CurrentDir;
		float       			 ControlSystemEnergy;
		float       			 DynamicSystemEnergy;
		uint16_t Step;
	} ROBOStatus_TypeDef;
#pragma pack()
void Command_tcp_server(void);//TCP Server回环演示函数
void Status_tcp_client2(void);//TCP Clinet回环演示函数
void Command_tcp_client(void);//TCP Clinet回环演示函数
	
typedef enum { NOCOMMAND=0,COMMAND,HELLO_ACK} CommandType;//
	
	
	
CommandType GetCommandFromServer(char * JsonDataFromSocket);//服务器命令数据解析，返回值为命令结构体,参数为从socket接收的数据并且已经做了初步的抽希（去掉*****与#####）




char * HelloStatusCommand_to_cJSON( char * cJSONROOM, Hello_TypeDef  StatusCmd);
char * CommandAck_to_cJSON( char * cJSONROOM, Command_Ack_TypeDef  Acknowledge);//入口参数为状态结构体，返回值为一个cJSON格式的字符串//命令反馈生成JSON
//char * Status_to_cJSON( ROBOStatus_TypeDef status);//状态生成JSON
char * Status_to_cJSON( char * cJSONROOM,ROBOStatus_TypeDef status);//传入一个变量的指针

void Delete_RobotJSON_CMD_TypeDef(RobotJSON_CMD_TypeDef  *jsonStructure);
void Delete_HelloJSON_Ack_TypeDef(HelloJSON_Ack_TypeDef  *jsonStructure);
char * Trans_to_ServerFormat(char *room,char  data[]);//字符串加密函数
char * Trans_to_ServerFormat2(char *room,char data[]);
char * Parse_from_ServerFormat(char * room, char data[]);//字符串解密函数
	

extern ROBOStatus_TypeDef ROBOStatus_TypeDefStructure;//上传给上位机的状态结构体，全局变量	
////命令socket响应接收函数，返回接收到的响应命令指针
//Hello_Ack_TypeDef * GetAck_from_Server(void);		

//状态及握手响应发送字符串函数，返回握手的字符串
//void TCP_Send( uint8_t * buf);
uint8_t send_robot_status_data(ROBOStatus_TypeDef *sRobotStatus);
#endif 


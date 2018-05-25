#ifndef __TCP_DEMO_H
#define __TCP_DEMO_H
#include "include.h"
extern uint16_t W5500_tcp_server_port;
//extern char * ROOM;
//extern uint8 buff[2048]="��Һã���������1";				                              	         /*����һ��2KB�Ļ���*/


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
	

	
	
	
//-----------------------����socket
	//���͸���λ��������ȷ�����ͽṹ��,״̬socket��һ��������Ҫ���ʹ��������ݸ���λ��
typedef struct InitConnect{	
		char 	 ID[15];//�����˵�ID��
		char  Type[15];//�����˵�״̬����������socket���ӣ���ֵΪ"RobotCommand"������״̬socket���ӣ���ֵΪ��RobotStatus��

	} Hello_TypeDef;

	
//����socket���ӳɹ�����λ������ID���Լ�ͬ��ʱ��
	typedef struct InitConnectAck{	
		char 	 ID[15];
		char   Time[20];

	} Hello_Ack_TypeDef;
	
	
	//����socket��Ӧ�ṹ��
	typedef struct CommandAck{	
		char 	Command[10];
		char  Result[10];

	} Command_Ack_TypeDef;
	
//-----------------------״̬socket,�����Ϸ���һ��ShakeHandInit_TypeDef���ֱ�ӷ���ROBOStatus_TypeDef���͵�����
	
	

	//�������Է�������������ͽṹ��
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
	
	//�����ϴ�״̬����������״̬���ͽṹ��
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
void Command_tcp_server(void);//TCP Server�ػ���ʾ����
void Status_tcp_client2(void);//TCP Clinet�ػ���ʾ����
void Command_tcp_client(void);//TCP Clinet�ػ���ʾ����
	
typedef enum { NOCOMMAND=0,COMMAND,HELLO_ACK} CommandType;//
	
	
	
CommandType GetCommandFromServer(char * JsonDataFromSocket);//�������������ݽ���������ֵΪ����ṹ��,����Ϊ��socket���յ����ݲ����Ѿ����˳����ĳ�ϣ��ȥ��*****��#####��




char * HelloStatusCommand_to_cJSON( char * cJSONROOM, Hello_TypeDef  StatusCmd);
char * CommandAck_to_cJSON( char * cJSONROOM, Command_Ack_TypeDef  Acknowledge);//��ڲ���Ϊ״̬�ṹ�壬����ֵΪһ��cJSON��ʽ���ַ���//���������JSON
//char * Status_to_cJSON( ROBOStatus_TypeDef status);//״̬����JSON
char * Status_to_cJSON( char * cJSONROOM,ROBOStatus_TypeDef status);//����һ��������ָ��

void Delete_RobotJSON_CMD_TypeDef(RobotJSON_CMD_TypeDef  *jsonStructure);
void Delete_HelloJSON_Ack_TypeDef(HelloJSON_Ack_TypeDef  *jsonStructure);
char * Trans_to_ServerFormat(char *room,char  data[]);//�ַ������ܺ���
char * Trans_to_ServerFormat2(char *room,char data[]);
char * Parse_from_ServerFormat(char * room, char data[]);//�ַ������ܺ���
	

extern ROBOStatus_TypeDef ROBOStatus_TypeDefStructure;//�ϴ�����λ����״̬�ṹ�壬ȫ�ֱ���	
////����socket��Ӧ���պ��������ؽ��յ�����Ӧ����ָ��
//Hello_Ack_TypeDef * GetAck_from_Server(void);		

//״̬��������Ӧ�����ַ����������������ֵ��ַ���
//void TCP_Send( uint8_t * buf);
uint8_t send_robot_status_data(ROBOStatus_TypeDef *sRobotStatus);
#endif 


#ifndef __TCP_DEMO_H
#define __TCP_DEMO_H
#include "include.h"

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

typedef struct JSON_InitConnectAck
	{
			 cJSON *ID;
			 cJSON *Time;

  } JSON_Hello_Ack_TypeDef;
		
	
//-----------------------����socket
	//���͸���λ��������ȷ�����ͽṹ��,״̬socket��һ��������Ҫ���ʹ��������ݸ���λ��
typedef struct InitConnect{	
		char 	*		   ID;//�����˵�ID��
		char  *      Type;//�����˵�״̬����������socket���ӣ���ֵΪ"RobotCommand"������״̬socket���ӣ���ֵΪ��RobotStatus��

	} Hello_TypeDef;

	
//����socket���ӳɹ�����λ������ID���Լ�ͬ��ʱ��
	typedef struct InitConnectAck{	
		char 	*		   ID;
		char  *      Time;

	} Hello_Ack_TypeDef;
	
	
	//����socket��Ӧ�ṹ��
	typedef struct CommandAck{	
		char 	*		   Command;
		char  *      Result;

	} Command_Ack_TypeDef;
	
//-----------------------״̬socket,�����Ϸ���һ��ShakeHandInit_TypeDef���ֱ�ӷ���ROBOStatus_TypeDef���͵�����
	
	

	//�������Է�������������ͽṹ��
typedef struct ROBOcommand{	
		char 	*		   Command;
		unsigned int Speed;
		unsigned int RunCount;
		unsigned int StartPosition;
		unsigned int EndPosition;
		unsigned int TargetPosition;
		char  *		   WorkMode;
		unsigned int Step;
	} ROBOCmd_TypeDef;

	
	
	//�����ϴ�״̬����������״̬���ͽṹ��
typedef struct ROBOstatus{	
		char 	          *	 RunStatus;
		char            *  CurrentTime;
	  int      			 		 CurrentPositiont;
		unsigned short int CurrentSpeed;
		unsigned short int RunningCount;
		char 				       CurrentTemp;
		float  				 	   CurrentVoltage;
		float						   CurrentAmp;
		unsigned char			 CurrentDir;
		float       			 ControlSystemEnergy;
		float       			 DynamicSystemEnergy;
		unsigned short int Step;
	} ROBOStatus_TypeDef;

  
extern Hello_TypeDef Command_Hello_TypeStructure;
  
void Command_tcp_server(void);//TCP Server�ػ���ʾ����
void Status_tcp_client2(void);//TCP Clinet�ػ���ʾ����
void Command_tcp_client(void);//TCP Clinet�ػ���ʾ����
	
typedef enum { NOCOMMAND=0,COMMAND,HELLO_ACK} CommandType;//
	
	
	
CommandType GetCommandFromServer(char * DataFromSocket);//�������������ݽ���������ֵΪ����ṹ��,����Ϊ��socket���յ����ݲ����Ѿ����˳����ĳ�ϣ��ȥ��*****��#####��




char * HelloStatusCommand_to_cJSON( Hello_TypeDef * StatusCmd);//���ֽṹ������JSON
char * CommandAck_to_cJSON( Command_Ack_TypeDef * Acknowledge);//���������JSON
char * Status_to_cJSON( ROBOStatus_TypeDef *status);//״̬����JSON











char * Trans_to_ServerFormat(char *room,char * data);//�ַ������ܺ���

char * Parse_from_ServerFormat(char * data);//�ַ������ܺ���
	

	
////����socket��Ӧ���պ��������ؽ��յ�����Ӧ����ָ��
//Hello_Ack_TypeDef * GetAck_from_Server(void);		

//״̬��������Ӧ�����ַ����������������ֵ��ַ���
void TCP_Send( char * buf);

#endif 


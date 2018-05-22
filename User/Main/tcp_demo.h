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
//-----------------------����socket
	//���͸���λ��������ȷ�����ͽṹ��,״̬socket��һ��������Ҫ���ʹ��������ݸ���λ��
typedef struct InitConnect{	
		char 	*		   ID;//�����˵�ID��
		char  *      Type;//�����˵�״̬����������socket���ӣ���ֵΪ"RobotCommand"������״̬socket���ӣ���ֵΪ��RobotStatus��

	} ShakeHandInit_TypeDef;

	
//����socket���ӳɹ�����λ������ID���Լ�ͬ��ʱ��
	typedef struct InitConnectAck{	
		char 	*		   ID;
		char  *      Time;

	} ShakeHandAck_TypeDef;
	
//-----------------------״̬socket,�����Ϸ���һ��ShakeHandInit_TypeDef���ֱ�ӷ���ROBOStatus_TypeDef���͵�����
	
	

	//�������Է�������������ͽṹ��
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

	
	
	//�����ϴ�״̬����������״̬���ͽṹ��
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

void Command_tcp_server(void);//TCP Server�ػ���ʾ����
void Status_tcp_client2(void);//TCP Clinet�ػ���ʾ����
void Command_tcp_client(void);//TCP Clinet�ػ���ʾ����

ROBOCmd_TypeDef GetCommandFromServer(char * DataFromSocket);//�������������ݽ���������ֵΪ����ṹ��,����Ϊ��socket���յ����ݲ����Ѿ����˳����ĳ�ϣ��ȥ��*****��#####��

char * Status_to_cJSON( ROBOStatus_TypeDef *status);//��ڲ���Ϊ״̬�ṹ�壬����ֵΪһ��cJSON��ʽ���ַ���

char * Trans_to_ServerFormat(char *room,char * data);//�ַ������ܺ���

char * Parse_from_ServerFormat(char * data);//�ַ������ܺ���
	
//����socket������պ��������ؽ��յ��������ַ���
ROBOCmd_TypeDef * GetCommand_from_Server(void);	
	
//����socket��Ӧ���պ��������ؽ��յ�����Ӧ����ָ��
ShakeHandAck_TypeDef * GetAck_from_Server(void);		



	
	
//״̬��������Ӧ�����ַ����������������ֵ��ַ���
void TCP_Send( uint8_t * buf);

#endif 


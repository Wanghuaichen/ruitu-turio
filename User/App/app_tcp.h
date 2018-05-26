/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.h
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        ����w5500��tcpӦ�ó���ͷ�ļ�
**************************************************************************************************
*/
#ifndef _APP_TCP_H_
#define _APP_TCP_H_
#include "include.h"
/*--------------- �궨�� --------------*/

/*--------------- �������� --------------*/
typedef enum
{
  Robot_CMD_Auto = 0, // �Զ�
  Robot_CMD_HomingStart, // ���㿪ʼ
  Robot_CMD_Start,    // ��ʼ
  Robot_CMD_Homing,   // ����
  Robot_CMD_Set,      // ���ò���
  Robot_CMD_Stop,     // ֹͣ
  Robot_CMD_Forward,  // ��ǰ
  Robot_CMD_Backward, // ���
  Robot_CMD_Jog,      // �ֶ����ֶ�ģʽ�¿�ʹ��ǰ���ͺ���ָ��˶��̶�����
  Robot_CMD_Dot,      // ����ģʽ
  Robot_CMD_Charging, // ���ģʽ
  Robot_CMD_Error     // ����
}E_MOTOR_STATE;
typedef struct
{
  E_MOTOR_STATE runStatus;           // ����״̬
  char          currentTime[30];     // ��ǰʱ��
  char          currentPosition[11]; // ��ǰλ��
  char          CurrentSpeed[11];    // ��ǰ�ٶ�
  uint16_t      RunningCount;        // ��ǰѲ�����
  uint8_t       CurrentTemp;         // ��ǰ�¶�
  uint16_t      CurrentVoltage;      // ��ǰ��ص�ѹ
  uint16_t      CurrentAmp;          // ��ǰ��ص���
  uint8_t       CurrentDir;          // ��ǰ���� 1���� 0 ����
  uint16_t      ControlSystemEnergy; // ��ǰ�����ٷֱ�
  uint16_t      DynamicSystemEnergy; // ��ǰ�����ٷֱ�
}S_ROBOT_STATUS;

typedef enum
{
  Robot_Work_RealTime = 0,
  Robot_Work_Regular,
  Robot_Work_Daily,
  Robot_Work_Error
}E_WORK_MODE;
typedef struct
{
  E_MOTOR_STATE eComand; // ����
  int16_t      speed;   // �ٶ�
  uint16_t     runCount; // ���д���
  int32_t      startPosition; // ��ʼλ��
  int32_t      endPosition; // ����λ��
  int32_t      targetPosition; // Ŀ��λ��
  E_WORK_MODE  eWorkMode[10];    // ����ģʽ realtime
  int16_t      step;           // �ֶ��˶�����
}S_ROBOT_COMMAND;
//typedef struct ROBOcommand
//{
//    char         Command[10];
//    unsigned int Speed;
//    unsigned int RunCount;
//    unsigned int StartPosition;
//    unsigned int EndPosition;
//    unsigned int TargetPosition;
//    char         WorkMode[10];
//    unsigned int Step;
//}ROBOCmd_TypeDef;

typedef struct
{
  E_MOTOR_STATE eComand;             // ����
  char          speed[6];            // �ٶ�
  uint16_t      runCount;            // ���д���
  char          startPosition[11];   // ��ʼλ��
  char          endPosition[11];     // ����λ��
  char          targetPosition[11];  // Ŀ��λ��
  char          homeOffset[11];      // �����ƫ�ƾ���
  char          homeFastSpeed[11];    // ��������ٶ�
  char          homeSlowSpeed[11];    // ���������ٶ�
  char          PositionAccelerated[11]; // λ��ģʽ���ٶ�
  char          PositionDecelerated[11]; // λ��ģʽ���ٶ�
  E_WORK_MODE   eWorkMode;           // ����ģʽ realtime
  uint16_t      step;                // �ֶ��˶�����
}S_MOTOR_PARAM;
/*--------------- �������� --------------*/
void Command_tcp_client(void);
void Status_tcp_client(void);
void task_tcp_init(void);
void task_tcp(void);
void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus);
void set_robot_command(E_MOTOR_STATE eRobotStatus ,char *buf);
E_MOTOR_STATE get_robot_command(char *buf);
E_WORK_MODE get_robot_run_mode(char *buf);
uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd);
#endif


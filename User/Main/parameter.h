/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : Parameter.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : ���в�����������������
*******************************************************************************/
/*-------------------------------------------------------------
���ڱ����ļ���˵����
1. ����ȫ�ֱ����������ڴ�ͷ�ļ���;
2. �ֲ�����ʹ���շ巨���׵�������ĸСд��������������ĸ��д���磺myVariableDefinition;
3. ȫ�ֱ���������ֲ�������ͬ�����_β׺���磺myVariableDefinition_;
---4. ����������ʹ���׵�������ĸ��д���շ巨���磺MyVariableDefinition;
4. ����������ʹ���»��߸�����Сд��ĸ��������my_variable_definition;
5. �ṹ�塢�����������ʹ��s��u����Ϊǰ׺������ȫ����д��ȫ�ֱ��������ǰ׺s��u����׺_��
    ��sMY_VARIABLE_DEFINITION sMyVariableDefinition_;�ֲ�����������ֲ�������
6. ����������ⶨ�壬ʹ��_TaskΪǰ׺����_TaskMyVariableDefinition;
7. ������غ���ʹ��taskΪǰ׺����task_my_variable_definition;

-----------------------------------------------------------------*/
#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "include.h"

/*--------��������궨��----------------*/
// ͨ�����ͺ궨�壬���ݴ˶����жϲ�ͬ�ӿڽ��յ�����
#define COM_TYPE_RS485             1 // ʹ��485�ӿ�ͨ��ʱͨ������
#define COM_TYPE_RS232             2 // ʹ��232�ӿ�ͨ��ʱͨ������
#define COM_TYPE_CAN               3 // ʹ��can�ӿ�ͨ��ʱͨ������
#define COM_TYPE_ETHERNET          4 // ʹ������ӿ�ͨ��ʱͨ������


// ����ͨ������ָ��� -----������
#define CMD_TASK_UART_RX           0xE1     // ���ڽ�������ָ��-����485��232
#define CMD_TASK_UART_TX           0xE2     // ���ڷ�������ָ��-����485��232
#define CMD_TASK_CAN_RX            0xEA     // can�ڽ�������ָ��
#define CMD_TASK_CAN_TX            0xEB     // can�ڷ�������ָ��
#define CMD_TASK_ETHERNET_RX       0xEC     // ���ڽ�������ָ��
#define CMD_TASK_ETHERNET_TX       0xED     // ���ڷ�������ָ��

// ��������ָ���
#define CMD_TASK_CONFIG            0xA0
///------�ϴ�SN---------------------//
#define CMD_CONFIG_GET_VER                0xA1 // ��ȡ�汾
#define CMD_CONFIG_GET_SN                 0xA8 // ��ȡSN
#define CMD_CONFIG_GET_REMOTE             0xAB // ��ȡһ���ϴ�ң����ָ��Ļ���
//-------����----------------------//
#define CMD_CONFIG_RESET_BOOT             0xA2
//--------�ָ���������-------------------
#define CMD_CONFIG_FACTORY_SET            0xA9

// ��ֵ����

#endif

/*-*************** ȫ�ֱ������� *********************/
#ifdef   GLOBAL_VARIABLE
#define  EXT_GLOBAL
#else
#define  EXT_GLOBAL extern
#endif


/*-***********ϵͳ��ر���******************************/
EXT_GLOBAL  volatile uint32_t     sysTick_;    // ϵͳʱ�Ӽ���
EXT_GLOBAL  volatile uint32_t     delayTick_;  // ��ʱʱ��
EXT_GLOBAL  uint32_t              runTick_;    // ����ʱ�Ӽ���
EXT_GLOBAL  uint8_t               cmdTick_;    // ָ�����


/*-*********������***********************************/
#define TASK_MAX             28  // �����������������
EXT_GLOBAL sTASK*            _TaskFlow[TASK_MAX + 1]; // ����������
EXT_GLOBAL TASK              taskID_;                 // ���������ţ���ʱ����

/*-*********����������*******************************/
EXT_GLOBAL sTASK              _TaskIdle;   // �����������
/*------------------- GPIO������ض��� -------------------------------*/
EXT_GLOBAL uint8_t            ledBlinkingFlag_;
/*-****************************����������*******************************/
EXT_GLOBAL sTASK              _TaskUartRx;
EXT_GLOBAL sTASK              _TaskUartTx;
// ���ڽ������ݷ���궨��
#define UART1_RX_DATA         0x01
#define UART2_RX_DATA         0x02
#define UART3_RX_DATA         0x04
#define UART4_RX_DATA         0x08
#define UART5_RX_DATA         0x10
//--------------------����1����-------------------------//
// ���ݶ���
#define UART1_BUF_LEN              500
#define UART1_DATA_LEN             15
// ����1���ն���
EXT_GLOBAL uint8_t             uart1RxBuf_[UART1_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart1RxCircleBuf_;
// ����1���Ͷ���
EXT_GLOBAL uint8_t             uart1TxBuf_[UART1_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart1TxCircleBuf_;

//--------------------����5����-------------------------//
// ���ݶ���
#define UART3_BUF_LEN              500
#define UART3_DATA_LEN             15
// ����3���ն���
EXT_GLOBAL uint8_t             uart3RxBuf_[UART3_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart3RxCircleBuf_;
// ����3���Ͷ���
EXT_GLOBAL uint8_t             uart3TxBuf_[UART3_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart3TxCircleBuf_;

/*-****************************����������*******************************/
EXT_GLOBAL sTASK            _TaskConfig;
EXT_GLOBAL sCONFIG_INSTRUCT sParamConfig_;
/*-***************************can����*************************************/
EXT_GLOBAL sTASK            _TaskCanRx;
EXT_GLOBAL sCAN_BUF         sCan1Buf_;
EXT_GLOBAL sCAN_BUF         sCan2Buf_;

/*--------------------------------����������------------------------------*/
EXT_GLOBAL sTASK            _TaskTcp;
EXT_GLOBAL S_W5500_CONFIG   sDefaultNetConfig_;

/*---------------------------------����������--------------------------------*/
EXT_GLOBAL uint16_t        encoderValue_[100];
EXT_GLOBAL uint8_t         segmentNum_;
EXT_GLOBAL uint8_t         homingDistance_;
EXT_GLOBAL volatile int64_t         encoderPlusNum_;
EXT_GLOBAL volatile int8_t          irLocationNum_;
/*------------------- �ӿں�����ض��� -------------------------------*/
#define   CANOPNE_GET_NODE_STATE        0x01  // ��ȡ�ڵ��־

EXT_GLOBAL uint8_t         canRxData_[8];
EXT_GLOBAL uint8_t         canRxFlag_;    // can �������ݶ���
#define RS232_SET_MOTOR_PARAM           0x01  // ���õ��������־
EXT_GLOBAL uint8_t         rs232RxFlag_;  // 232 �������ݶ���
/*------------------- �����ض��� -------------------------------*/
EXT_GLOBAL sTASK           _TaskBattery;
EXT_GLOBAL sBATTERY        sBattery_;
EXT_GLOBAL uint8_t         queryRegAddr_;
EXT_GLOBAL uint8_t         batteryStateFlag_;  // 232 �������ݶ���
/*------------------- �������������ض��� -------------------------------*/
EXT_GLOBAL sTASK           _TaskMotorControl;
EXT_GLOBAL sTASK           _TaskMotorState;
EXT_GLOBAL char            recMotorStatus_[10][11];
EXT_GLOBAL uint32_t        motorStatus_[10];
EXT_GLOBAL uint8_t         motorMode_;
EXT_GLOBAL uint8_t         motorPauseFlag_;
EXT_GLOBAL uint8_t         motorFlag_;
EXT_GLOBAL E_MOTOR_STATE   eMotorControlMode_;
EXT_GLOBAL S_MOTOR_PARAM   sMotorParam_;
EXT_GLOBAL S_ROBOT_STATUS  sRobotStatus_;
/*------------------- ��ȡ�¶�ֵ -------------------------------*/
EXT_GLOBAL sTASK           _TaskRead18B20;
/*------------------- ���������� -------------------------------*/
EXT_GLOBAL sTASK           _TaskSensors;
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





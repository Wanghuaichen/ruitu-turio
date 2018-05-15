/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_motor.h
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        ����ӿں���ͷ�ļ�
**************************************************************************************************
*/
#ifndef _API_MOTOR_H_
#define _API_MOTOR_H_
#include "include.h"
/*--------------- �궨�� --------------*/
// ���canopen����
#define DEVICE_ID                      0x01 // �豸ID
// nmt��ָ����
#define NMT_START_REMOTE_NODE              1 // ����Զ�̽ڵ�
#define NMT_STOP_REMOTE_NODE               2 // �ر�Զ�̽ڵ�
#define NMT_ENTER_PREOPERATIONAL_STATE     128 // ����Ԥ����״̬
#define NMT_RESET_NODE                     129 // ��λ���
#define NMT_RESET_COMMUNICTION             130 // ��λͨ��

// ID����
#define SYNCHRONIZATION_CYCLE_ID       0x000600 // ͬ��������������� Cycle synchronization
#define SYNCHRONIZATION_START_ID       0x000600 // ��������ͬ��
#define NMT_BROADCAST_ID               0x000000 // NMT�õĹ㲥ID
#define NMT_NODE_GUARDING_ID           0x000700 // NMT�õĽڵ㱣��ID
/*--------------- �������� --------------*/

/*--------------- �������� --------------*/

void motor_start_node(void);
void motor_stop_node(void);
void motor_set_syn_cycle(void);
void motor_start_syn(void);
uint8_t motor_get_state(uint8_t *buf,uint8_t len);
uint8_t motor_set_position(uint32_t position);
uint8_t motor_set_velocity(uint32_t velocity);
void motor_start_position_mode(void);
#endif


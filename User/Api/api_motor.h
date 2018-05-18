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
//

/**
 �Ĵ������ƺ궨��-λ��ģʽ
  ���ù��̣�
step1:  s r0xc8 0  //����λ��Ϊ����λ��ģʽ��������������
step2:  s r0xca ---//����Ŀ��λ��
step3:  s r0xcb ---//�����ٶ�
step4:  s r0xcc ---//���ü��ٶ�
step5:  s r0xcd ---//���ü��ٶ�
step6:  s r0xcf ---//���ý������ٶ�
step7:  s r0x24 21 //���λ��ģʽʹ��
step8:  t 1        //��ʼλ��ģʽ�˶�
ע�⣺������˶������и���θ�˶�����������˵����ٶȣ��ȷ����ٶ����Ȼ���� t 1���������ܸ��¼Ĵ�����ֵ
*/
#define MOTOR_REG_SET_DESIRED_STATE           "r0x24 "  // ���õ����ģʽ21��
#define MOTOR_REG_SET_POS_PROFILE_TYPE        "r0xc8 "  // ���õ��λ��ģʽ
#define MOTOR_REG_SET_POS_POSITION            "r0xca "  // ���õ��λ�üĴ���
#define MOTOR_REG_SET_POS_VELOCITY            "r0xcb "  // ���õ���ٶȼĴ���
#define MOTOR_REG_SET_POS_ACCELERATION        "r0xcc "  // ���õ�����ٶȼĴ���
#define MOTOR_REG_SET_POS_DECELERATION        "r0xcd "  // ���õ�����ٶȼĴ���
#define MOTOR_REG_SET_POS_MAXIMUM_JERKRATE    "r0xce "  // ���õ��maxinum jerk rate
#define MOTOR_REG_SET_POS_ABORT_DECELERATION  "r0xcf "  // ���õ���������ٶ�
                                                      //
#define MOTOR_REG_UPDATE                      "t 1"  // ��ʼλ���˶�����/���²�������/�����˶�����
#define MOTOR_REG_PAUSE                       "t 0"  // �˶���ͣ�����ʱ������ڵ�ǰλ���Խ���ֹͣ���ٶ�ͣ��
                                                  //
/**
 �Ĵ������ƺ궨��-����ģʽ
 ���ù��̣�
step1:  s r0xc2 529//����ʹ�ø�����λ������Ϊ����
step2:  s r0xc3 ---//������������ǰ�ĸ���
step3:  s r0xc4 ---//�����������غ�ĵ���
step4:  s r0xc5 ---//���ü��ٶ�
step5:  s r0xc6 ---//����ԭ��ƫ����
step6:  s r0x24 21 //ʹ���������λ��ģʽ�£���Ϊ����ģʽ������Ҳ������λ�ã�
step7:  t 2        //��ʼ���л����˶�
*/
#define MOTOR_REG_SET_DESIRED_STATE            "r0x24 "  // ���õ����ģʽ21
#define MOTOR_REG_SET_HOME_HOMING_METHOD       "r0xc2 "  // ���õ���㷽ʽ 529 for Negative limit switch or 513 for the positive
#define MOTOR_REG_SET_HOME_FAST_VELOCITY       "r0xc3 "  // ���õ����������ٶ�
#define MOTOR_REG_SET_HOME_SLOW_VELOCITY       "r0xc4 "  // ���õ��������С�ٶ�
#define MOTOR_REG_SET_HOME_ACC_DECELERATION    "r0xc5 "  // ���õ����/���ٶȼĴ���
#define MOTOR_REG_SET_HOME_OFFSET              "r0xc6 "  // ���õ�����ƫ����
#define MOTOR_REG_SET_HOME_START               "t 2"  // ��ʼ���л����˶�������;Ҫ��ͣ���ɷ���t 0,�����˶��ɷ��� t 1
                                                  //

// ��������ֵ��ʵ���·�ֵ��ϵ
#define MOTOR_COUNTS_VELOCITY       (1009)  // ת���������ٶ���Ҫ�˵ı���
#define MOTOR_COUNTS_POSITION       (101)  // ת��������λ����Ҫ�˵ı���
#define MOTOR_COUNTS_ACCELERATION   (101)  // ת����������ٶ���Ҫ�˵ı���

// �����ȡ���ݼĴ���
#define MOTOR_REG_GET_MONITORING_STATUS     "r0xa0 " // ���������Ĵ���״ָ̬��
#define MOTOR_REG_GET_ACTUAL_POSITION       "r0x32 " // ��������ʵ��λ��ָ��
#define MOTOR_REG_GET_TRAJECTORY_STATUS     "r0xc9 " // ���������˶�״̬�Ĵ���ָ�� 12 ��13λ

// �Ĵ���״̬����
#define MOTOR_REG_STATUS_ENABLE_NOT_ACTIVE        (0x00000800) // �Ĵ�����ǰ���ڷ�ʹ��״̬ 11λ
#define MOTOR_REG_STATUS_HOMING_SUCCESSFULLY      (0x1000) // �Ĵ�������ɹ�״̬
#define MOTOR_REG_STATUS_HOMING_RUNING            (0x2000) // �Ĵ������ڻ��������״̬
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
void task_motor_control_init(void);
void task_motor_control(void);
uint8_t motor_tx_data_processing(char ins,char *reg,char* sendData,uint16_t len);
uint8_t motor_rx_data_processing(char *buf,uint16_t len);
uint8_t motor_mode_home_control(void);
uint8_t motor_mode_position_control(void);
#endif


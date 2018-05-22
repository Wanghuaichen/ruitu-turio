/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_gpio.h
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        оƬ�������ͷ�ļ�
**************************************************************************************************
*/
#ifndef _APP_GPIO_H_
#define _APP_GPIO_H_
#include "include.h"
/*--------------- �궨�� --------------*/
#define OUT_CONTROL_ON                0
#define OUT_CONTROL_OFF               1
#define OUT_CONTROL_BLINKING          2
#define LED_OAS_LEFT_BLINKING         0x01   // ����ϱ�������˸
#define LED_OAS_RIGHT_BLINKING        0x02   // �ұ��ϱ�������˸
#define LED_RUN_BLINKING              0x04   // ���е���˸
#define LED_BATTERY_BLINKING          0x08   // ��ص���˸
#define LED_ETHERNET_BLINKING         0x10   // �������˸
#define RSV_OUT1_BLINKING             0x20   // Ԥ�����1��˸
#define RSV_OUT2_BLINKING             0x40   // Ԥ�����2��˸
#define RSV_OUT3_BLINKING             0x80   // Ԥ�����3��˸
/*--------------- �������� --------------*/

/*--------------- �������� --------------*/

void control_blinking(void);
void control_ethernet_led(uint8_t onoff);
void control_battery_led(uint8_t onoff);
void control_fan2_power(uint8_t onoff);
void control_fan1_power(uint8_t onoff);
void control_route_power(uint8_t onoff);
void control_lidar_power(uint8_t onoff);
void control_motort_enable(uint8_t onoff);
void control_imu_power(uint8_t onoff);
void control_run_led(uint8_t onoff);
void control_reserved_out1(uint8_t onoff);
void control_reserved_out2(uint8_t onoff);
void control_reserved_out3(uint8_t onoff);
void control_right_oas_led(uint8_t onoff);
void control_left_oas_led(uint8_t onoff);
void control_init(void);
void control_all_off(void);
void control_all_on(void);

//�豸����-�������߹رռ����״�ȵ�
void SetFan(uint8_t fan,uint8_t state); //�򿪻�ر� fan��fan1����fan2 state��ENABLE/DISABLE
void SetRadar(uint8_t state);    //���״� or DISABLEĬ��ֻ��һ���״�
void SetRoute(uint8_t state);    //��·���� or DISABL
void SetIMU(uint8_t state);      //��IMU or DISABLE

//  //����LED��״̬������ֻ������LED��
//  void SetTopLed(choice);//����on-2����˸ blinking-1���ر�off-0 ��ǰdefine
//  void SetMidLed(choice);//����2����˸1���ر�0
//  void SetRgbLed(color,choice);//����2��ѡ��R/G/B?������˸1���ر�0  ò��Ҫ����IOȥ��
/*------------------- �������źż����� -------------------------------*/
uint8_t GetLeftObstacleSensor(void);     // 1Ϊ���ϰ� ��0Ϊ���ϰ�
uint8_t GetRightObstacleSensor(void);    // 1Ϊ���ϰ� �� 0Ϊ���ϰ�
void SetLeftObstacleLed(uint8_t state);  // LED_ON/LED_OFF/LED_BLINKING
void SetRightObstacleLed(uint8_t state); // LED_ON/LED_OFF/LED_BLINKING
uint8_t GetIRLoactionSensor(void);    // 1Ϊ���ϰ� �� 0Ϊ���ϰ�

void task_sensors_init(void);
void task_sensors(void);
#endif

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





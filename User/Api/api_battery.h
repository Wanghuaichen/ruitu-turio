/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_battery.h
* @author       zhou
* @version      V1.0
* @date         2018/5/17
* @brief        ��ؽӿڳ���ͷ�ļ�
**************************************************************************************************
*/
#ifndef _API_BATTERY_H_
#define _API_BATTERY_H_
#include "include.h"
/*--------------- �궨�� --------------*/
#define   FAN1          0
#define   FAN2          1
// LED״̬
#define   LED_ON        2
#define   LED_OFF       0
#define   LED_BLINKING  1
// ������״̬
#define   BATTERY_FLAG_GET_PARAM       0x01
//
#define   BATTERY_ADDR                  0x01 // �����ص�ַ
#define   BATTERY_FUN_CODE              0x03 // ���幦����
// �Ĵ�����ַ����
#define   BATTERY_REG_OVER_VOLTAGE         0x00 // ���嵥���ѹ�Ĵ�����ַ
#define   BATTERY_REG_RELEASE_OVER         0x01 // ���嵥���ѹ�Ĵ�����ַ
#define   BATTERY_REG_UNDER_VOLTAGE        0x02 // ���嵥���ѹ�Ĵ�����ַ
#define   BATTERY_REG_RELEASE_UNDER        0x03 // ���嵥���ѹ�Ĵ�����ַ
#define   BATTERY_REG_VOTAGE               0x12 // ���嵥���ѹ�Ĵ�����ַ
#define   BATTERY_REG_VOTAGE_PERCENT       0x28 // ���嵥���ѹ�Ĵ�����ַ
#define   BATTERY_REG_CURRENT              0x13 // ���嵥���ѹ�Ĵ�����ַ
/*--------------- �������� --------------*/
typedef struct
{
  uint16_t batteryVoltage; // ��ѹ
  uint16_t batteryCurrent; // ����
  uint16_t batteryPercent; // �ٷֱ�
}sBATTERY;
/*--------------- �������� --------------*/
void battery_control(uint8_t regAddr);
void battery_tx_processing(uint8_t addr,uint8_t funCode, uint8_t regAddr);
void battery_rx_processing(uint8_t *buf, uint16_t len);
void task_battery_init(void);
void task_battery(void);

#endif



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/






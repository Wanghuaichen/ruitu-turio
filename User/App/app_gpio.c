/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_gpio.c
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        оƬ������Ƴ����ļ�
**************************************************************************************************
*/
#include "include.h"
/**
*@function void control_left_oas_led(uint8_t onoff)
*@brief    ��౨�����ϵƿ���
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_left_oas_led(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~LED_OAS_LEFT_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= LED_OAS_LEFT_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(LED_OAS_LEFT_GPIO_Port, LED_OAS_LEFT_Pin);
  else
    GPIO_ResetBits(LED_OAS_LEFT_GPIO_Port, LED_OAS_LEFT_Pin);
}
/**
*@function void control_right_oas_led(uint8_t onoff)
*@brief    �Ҳ���ϱ����ƿ���
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_right_oas_led(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~LED_OAS_RIGHT_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= LED_OAS_RIGHT_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(LED_OAS_RIGHT_GPIO_Port, LED_OAS_RIGHT_Pin);
  else
    GPIO_ResetBits(LED_OAS_RIGHT_GPIO_Port, LED_OAS_RIGHT_Pin);
}
/**
*@function void control_reserved_out3(uint8_t onoff)
*@brief    Ԥ�����3����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_reserved_out3(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~RSV_OUT3_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= RSV_OUT3_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(RSV_OUT3_GPIO_Port, RSV_OUT3_Pin);
  else
    GPIO_ResetBits(RSV_OUT3_GPIO_Port, RSV_OUT3_Pin);
}
/**
*@function void control_reserved_out2(uint8_t onoff)
*@brief    Ԥ�����2����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_reserved_out2(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~RSV_OUT2_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= RSV_OUT2_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(RSV_OUT2_GPIO_Port, RSV_OUT2_Pin);
  else
    GPIO_ResetBits(RSV_OUT2_GPIO_Port, RSV_OUT2_Pin);
}
/**
*@function void control_reserved_out1(uint8_t onoff)
*@brief    Ԥ�����1����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_reserved_out1(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~RSV_OUT1_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= RSV_OUT1_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(RSV_OUT1_GPIO_Port, RSV_OUT1_Pin);
  else
    GPIO_ResetBits(RSV_OUT1_GPIO_Port, RSV_OUT1_Pin);
}
/**
*@function void control_run_led(uint8_t onoff)
*@brief    ���еƿ���
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_run_led(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~LED_RUN_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= LED_RUN_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(LED_RUN_GPIO_Port, LED_RUN_Pin);
  else
    GPIO_ResetBits(LED_RUN_GPIO_Port, LED_RUN_Pin);
}
/**
*@function void control_imu_power(uint8_t onoff)
*@brief    imu��Դ�������
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   ��
*/
void control_imu_power(uint8_t onoff)
{
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(POWER_IMU_GPIO_Port, POWER_IMU_Pin);
  else
    GPIO_ResetBits(POWER_IMU_GPIO_Port, POWER_IMU_Pin);
}
/**
*@function void control_motort_enable(uint8_t onoff)
*@brief    ������ʹ�ܿ���
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   ��
*/
void control_motort_enable(uint8_t onoff)
{
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
  else
    GPIO_ResetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
}
/**
*@function void control_lidar_power(uint8_t onoff)
*@brief    �״��Դ����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   ��
*/
void control_lidar_power(uint8_t onoff)
{
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(POWER_LIDAR_GPIO_Port, POWER_LIDAR_Pin);
  else
    GPIO_ResetBits(POWER_LIDAR_GPIO_Port, POWER_LIDAR_Pin);
}
/**
*@function void control_route_power(uint8_t onoff)
*@brief    ·������Դ����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   ��
*/
void control_route_power(uint8_t onoff)
{
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(POWER_ROUTE_GPIO_Port, POWER_ROUTE_Pin);
  else
    GPIO_ResetBits(POWER_ROUTE_GPIO_Port, POWER_ROUTE_Pin);
}
/**
*@function void control_fan1_power(uint8_t onoff)
*@brief     ����1��Դ����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   ��
*/
void control_fan1_power(uint8_t onoff)
{
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(POWER_FAN1_GPIO_Port, POWER_FAN1_Pin);
  else
    GPIO_ResetBits(POWER_FAN1_GPIO_Port, POWER_FAN1_Pin);
}
/**
*@function void control_fan2_power(uint8_t onoff)
*@brief     ����2��Դ����
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   ��
*/
void control_fan2_power(uint8_t onoff)
{
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(POWER_FAN2_GPIO_Port, POWER_FAN2_Pin);
  else
    GPIO_ResetBits(POWER_FAN2_GPIO_Port, POWER_FAN2_Pin);
}
/**
*@function void control_battery_led(uint8_t onoff)
*@brief    ��ص��������
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_battery_led(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~LED_BATTERY_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= LED_BATTERY_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
  if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(LED_BATTERY_GPIO_Port, LED_BATTERY_Pin);
  else
    GPIO_ResetBits(LED_BATTERY_GPIO_Port, LED_BATTERY_Pin);
}
/**
*@function void control_ethernet_led(uint8_t onoff)
*@brief    ������������
*@param    onoff ��OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   ��
*/
void control_ethernet_led(uint8_t onoff)
{
  ledBlinkingFlag_ &= ~LED_ETHERNET_BLINKING;
  if (onoff == OUT_CONTROL_BLINKING)
    ledBlinkingFlag_ |= LED_ETHERNET_BLINKING;
  else if (onoff == OUT_CONTROL_ON)
    GPIO_SetBits(LED_ETHERNET_GPIO_Port, LED_ETHERNET_Pin);
  else
    GPIO_ResetBits(LED_ETHERNET_GPIO_Port, LED_ETHERNET_Pin);
}
/**
*@function void control_blinking(void)
*@brief    ��˸���Ƴ��򣬸��ݱ�־��תָ������
*@param    void ��
*@return   ��
*/
void control_blinking(void)
{
  if (ledBlinkingFlag_ & LED_OAS_LEFT_BLINKING)
    gpio_toggle_pin(LED_OAS_LEFT_GPIO_Port, LED_OAS_LEFT_Pin);
  if (ledBlinkingFlag_ & LED_OAS_RIGHT_BLINKING)
    gpio_toggle_pin(LED_OAS_RIGHT_GPIO_Port, LED_OAS_RIGHT_Pin);
  if (ledBlinkingFlag_ & LED_RUN_BLINKING)
    gpio_toggle_pin(LED_RUN_GPIO_Port, LED_RUN_Pin);
  if (ledBlinkingFlag_ & LED_BATTERY_BLINKING)
    gpio_toggle_pin(LED_BATTERY_GPIO_Port, LED_BATTERY_Pin);
  if (ledBlinkingFlag_ & LED_ETHERNET_BLINKING)
    gpio_toggle_pin(LED_ETHERNET_GPIO_Port, LED_ETHERNET_Pin);
  if (ledBlinkingFlag_ & RSV_OUT1_BLINKING)
    gpio_toggle_pin(RSV_OUT1_GPIO_Port, RSV_OUT1_Pin);
  if (ledBlinkingFlag_ & RSV_OUT2_BLINKING)
    gpio_toggle_pin(RSV_OUT2_GPIO_Port, RSV_OUT2_Pin);
  if (ledBlinkingFlag_ & RSV_OUT3_BLINKING)
    gpio_toggle_pin(RSV_OUT3_GPIO_Port, RSV_OUT3_Pin);

}
/**
*@function void control_init(void)
*@brief    ���Ƴ�ʼ��������Ҫ�򿪿����ڳ�ʼ���д�
*@param    void ����
*@return   ��
*/
void control_init(void)
{
  ledBlinkingFlag_ = 0;
  control_battery_led(ON);
  control_ethernet_led(ON);
  control_fan1_power(ON);
  control_fan2_power(ON);
  control_imu_power(ON);
  control_left_oas_led(ON);
  control_lidar_power(ON);
  control_motort_enable(ON);
  control_reserved_out1(ON);
  control_reserved_out2(ON);
  control_reserved_out3(ON);
  control_right_oas_led(ON);
  control_run_led(ON);
  control_route_power(ON);
}
void control_all_on(void)
{
  control_battery_led(ON);
  control_ethernet_led(ON);
  control_fan1_power(ON);
  control_fan2_power(ON);
  control_imu_power(ON);
  control_left_oas_led(ON);
  control_lidar_power(ON);
  control_motort_enable(ON);
  control_reserved_out1(ON);
  control_reserved_out2(ON);
  control_reserved_out3(ON);
  control_right_oas_led(ON);
  control_run_led(ON);
  control_route_power(ON);
}
void control_all_off(void)
{
  control_battery_led(OFF);
  control_ethernet_led(OFF);
  control_fan1_power(OFF);
  control_fan2_power(OFF);
  control_imu_power(OFF);
  control_left_oas_led(OFF);
  control_lidar_power(OFF);
  control_motort_enable(OFF);
  control_reserved_out1(OFF);
  control_reserved_out2(OFF);
  control_reserved_out3(OFF);
  control_right_oas_led(OFF);
  control_run_led(OFF);
  control_route_power(OFF);
}


/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_gpio.c
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        芯片输出控制程序文件
**************************************************************************************************
*/
#include "include.h"

void control_left_oas_led(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(LED_OAS_LEFT_GPIO_Port, LED_OAS_LEFT_Pin);
  else
    GPIO_ResetBits(LED_OAS_LEFT_GPIO_Port, LED_OAS_LEFT_Pin);
}
void control_right_oas_led(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(LED_OAS_RIGNT_GPIO_Port, LED_OAS_RIGNT_Pin);
  else
    GPIO_ResetBits(LED_OAS_RIGNT_GPIO_Port, LED_OAS_RIGNT_Pin);
}
void control_reserved_out3(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(RSV_OUT3_GPIO_Port, RSV_OUT3_Pin);
  else
    GPIO_ResetBits(RSV_OUT3_GPIO_Port, RSV_OUT3_Pin);
}
void control_reserved_out2(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(RSV_OUT2_GPIO_Port, RSV_OUT2_Pin);
  else
    GPIO_ResetBits(RSV_OUT2_GPIO_Port, RSV_OUT2_Pin);
}
void control_reserved_out1(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(RSV_OUT1_GPIO_Port, RSV_OUT1_Pin);
  else
    GPIO_ResetBits(RSV_OUT1_GPIO_Port, RSV_OUT1_Pin);
}
void control_run_led(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(LED_RUN_GPIO_Port, LED_RUN_Pin);
  else
    GPIO_ResetBits(LED_RUN_GPIO_Port, LED_RUN_Pin);
}
void control_imu_power(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(POWER_IMU_GPIO_Port, POWER_IMU_Pin);
  else
    GPIO_ResetBits(POWER_IMU_GPIO_Port, POWER_IMU_Pin);
}
void control_motort_enable(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
  else
    GPIO_ResetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
}
void control_lidar_power(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(POWER_LIDAR_GPIO_Port, POWER_LIDAR_Pin);
  else
    GPIO_ResetBits(POWER_LIDAR_GPIO_Port, POWER_LIDAR_Pin);
}
void control_route_power(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(POWER_ROUTE_GPIO_Port, POWER_ROUTE_Pin);
  else
    GPIO_ResetBits(POWER_ROUTE_GPIO_Port, POWER_ROUTE_Pin);
}
void control_fan1_power(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(POWER_FAN1_GPIO_Port, POWER_FAN1_Pin);
  else
    GPIO_ResetBits(POWER_FAN1_GPIO_Port, POWER_FAN1_Pin);
}
void control_fan2_power(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(POWER_FAN2_GPIO_Port, POWER_FAN2_Pin);
  else
    GPIO_ResetBits(POWER_FAN2_GPIO_Port, POWER_FAN2_Pin);
}
void control_battery_led(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(LED_BATTERY_GPIO_Port, LED_BATTERY_Pin);
  else
    GPIO_ResetBits(LED_BATTERY_GPIO_Port, LED_BATTERY_Pin);
}
void control_ethernet_led(uint8_t onoff)
{
  if (onoff == ON)
    GPIO_SetBits(LED_ETHERNET_GPIO_Port, LED_ETHERNET_Pin);
  else
    GPIO_ResetBits(LED_ETHERNET_GPIO_Port, LED_ETHERNET_Pin);
}
void control_init(void)
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


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
    GPIO_SetBits(LED_OAS_GPIO_Port, LED_OAS_Pin);
  else
    GPIO_ResetBits(LED_OAS_GPIO_Port, LED_OAS_Pin);
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
    GPIO_SetBits(LED_OAS_GPIO_Port, LED_OAS_Pin);
  else
    GPIO_ResetBits(LED_OAS_GPIO_Port, LED_OAS_Pin);
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
    gpio_toggle_pin(LED_OAS_GPIO_Port, LED_OAS_Pin);
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

/*-------------------  ��Դ���� -------------------------------*/
/**
*@function void SetFan(uint8_t fan, uint8_t state)
*@brief    �Է��ȵ�Դ���п���
*@param    fan :FAN1/FAN2
*@param    state ��״̬ENABLE/DISABLE
*@return   ��
*/
void SetFan(uint8_t fan,uint8_t state)
{
  if (state == ENABLE)
  {
    if (fan == FAN1)
      control_fan1_power(OUT_CONTROL_ON);
    else
      control_fan2_power(OUT_CONTROL_ON);
  }
  else
  {
    if (fan == FAN1)
      control_fan1_power(OUT_CONTROL_OFF);
    else
      control_fan2_power(OUT_CONTROL_OFF);
  }
}
/**
*@function void SetRadar(uint8_t state)
*@brief    �״��Դ����
*@param    state ��ENABLE/DISABLE
*@return   ��
*/
void SetRadar(uint8_t state)
{
  if (state == ENABLE)
    control_lidar_power(OUT_CONTROL_ON);
  else
    control_lidar_power(OUT_CONTROL_OFF);
}
/**
*@function void SetRoute(uint8_t state)
*@brief     ·�ɵ�Դ����
*@param    state ��ENABLE/DISABLE
*@return   ��
*/
void SetRoute(uint8_t state)
{
  if (state == ENABLE)
    control_route_power(OUT_CONTROL_ON);
  else
    control_route_power(OUT_CONTROL_OFF);
}
/**
*@function void SetIMU(uint8_t state)
*@brief    imu��Դ����
*@param    state :ENABLE/DISABLE
*@return   ��
*/
void SetIMU(uint8_t state)
{
  if (state == ENABLE)
    control_imu_power(OUT_CONTROL_ON);
  else
    control_imu_power(OUT_CONTROL_OFF);
}
/**
*@function uint8_t GetLeftObstacleSensor(void)
*@brief   ��ȡ������ϱܴ�������ֵ
*@param    void :��
*@return   ��
*/
uint8_t GetLeftObstacleSensor(void)
{
  if (GPIO_ReadInputDataBit(OAS_LEFT_GPIO_Port, OAS_LEFT_Pin) != Bit_RESET)
    return 1;
  else
    return 0;
}
/**
*@function uint8_t GetRightObstacleSensor(void)
*@brief    ��ȡ�ұ��ϴ���������ֵ
*@param    void :��
*@return   ��
*/
uint8_t GetRightObstacleSensor(void)
{
  if (GPIO_ReadInputDataBit(OAS_RIGHT_GPIO_Port, OAS_RIGHT_Pin) != Bit_RESET)
    return 1;
  else
    return 0;
}
/**
*@function void SetLeftObstacleLed(uint8_t state)
*@brief    �������ϱ����ƿ���
*@param    state :LED_ON/LED_OFF/LED_BLINKING
*@return   ��
*/
void SetLeftObstacleLed(uint8_t state)
{
  if (state == LED_ON)
    control_left_oas_led(OUT_CONTROL_ON);
  else if (state == LED_BLINKING)
    control_left_oas_led(OUT_CONTROL_BLINKING);
  else
    control_left_oas_led(OUT_CONTROL_OFF);
}
/**
*@function void SetLeftObstacleLed(uint8_t state)
*@brief    ���Ҳ���ϱ����ƿ���
*@param    state :LED_ON/LED_OFF/LED_BLINKING
*@return   ��
*/
void SetRightObstacleLed(uint8_t state)
{
  if (state == LED_ON)
    control_right_oas_led(OUT_CONTROL_ON);
  else if (state == LED_BLINKING)
    control_right_oas_led(OUT_CONTROL_BLINKING);
  else
    control_right_oas_led(OUT_CONTROL_OFF);
}

/**
*@function uint8_t GetIRLoactionSensor(void)
*@brief    ��ȡ��綨λ�ź�
*@param    void :��
*@return   ��
*/
uint8_t GetIRLoactionSensor(void)
{
  if (GPIO_ReadInputDataBit(IR_LOCATION_GPIO_Port, IR_LOCATION_Pin) != Bit_RESET)
    return 1;
  else
    return 0;
}
/**
*@function void task_sensors_init(void)
*@brief    �����������ʼ��
*@param    void ����
*@return   ��
*/
void task_sensors_init(void)
{
  _TaskSensors.fun = task_sensors;
  _TaskSensors.state = TASK_STATE_RUN;
}
/**
*@function void task_sensors(void)
*@brief    ����������
*@return   ��
*/
void task_sensors(void)
{
  #define FILTER_TIMES   2
  static uint8_t leftFilter = 0,rightFilter = 0;
  _TaskSensors.interval = 5;
  _TaskSensors.state    = TASK_STATE_DELAY;
   // �ж������Ͽ����Ƿ����ϰ�����������ӦLED
  if (GetLeftObstacleSensor() == 0)
  {
    if (++leftFilter > FILTER_TIMES) // ��ʱ�ж�
    {
      motorPauseFlag_ |= MOTOR_PAUSE_OBSTACLE_SENSOR_LEFT;
      control_left_oas_led(OUT_CONTROL_ON);
    }
  }
  else
  {
    leftFilter = 0;
    motorPauseFlag_ &= ~MOTOR_PAUSE_OBSTACLE_SENSOR_LEFT;
    control_left_oas_led(OUT_CONTROL_OFF);
  }
  // �ж��Ҳ���Ͽ����Ƿ����ϰ�����������ӦLED
  if (GetRightObstacleSensor() == 0)
  {
    if (++rightFilter > FILTER_TIMES) // ��ʱ�ж�
    {
      motorPauseFlag_ |= MOTOR_PAUSE_OBSTACLE_SENSOR_RIGHT;
      control_right_oas_led(OUT_CONTROL_ON);
    }
  }
  else
  {
    rightFilter = 0;
    motorPauseFlag_ &= ~MOTOR_PAUSE_OBSTACLE_SENSOR_RIGHT;
    control_right_oas_led(OUT_CONTROL_OFF);
  }
  if ((IR_LOCATION_GPIO_Port->IDR & IR_LOCATION_Pin) != (uint32_t)Bit_RESET)
  {
    if (irLocationNum_ > 3)
      segmentNum_++;
    else if (irLocationNum_ < -3)
    {
      segmentNum_--;
    }
    irLocationNum_ = 0;
    RSV_OUT1_GPIO_Port->BRR = RSV_OUT1_Pin;
    irLocationNum_ =  0;
  }
}

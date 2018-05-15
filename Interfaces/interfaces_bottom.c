/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         interfaces_bottom.c
* @author       zhou
* @version      V1.0
* @date         2018/5/14
* @brief        �׵��ýӿڳ����ļ�
**************************************************************************************************
*/
#include "include.h"
/**
*@function void SetCAN(uint8_t state)
*@brief    ͨ��canopen���õ��
*@param    state��ENABLE / DISABLE
*@return   ��
*@date     2018/5/14
*/
void SetCAN(uint8_t state)
{
  if (state == DISABLE) // �رսڵ�
  {
    motor_stop_node();
  }
  else
  {
    motor_set_syn_cycle(); // ����ͬ������
    motor_start_syn();     // ����ͬ��
    motor_start_node();    // �����ڵ�
  }
}
/**
*@function void SetMotor(uint8_t state)
*@brief    ���õ�ѹenable��״̬
*@param    state��ENABLE/DISABLE
*@return   ��
*@date     2018/5/14
*/
void SetMotor(uint8_t state)
{
  if (state == DISABLE)
    GPIO_ResetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
  else
    GPIO_SetBits(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin);
}

/**
*@function uint8_t GetMotorState(uint8_t *buf, uint8_t len)
*@brief    ��ȡ���״̬,
*@param    buf:״̬����
*@param    len:״̬���ݳ���
*@return   1:�ɹ� 0:ʧ��
*@date     2018/5/14
*/
uint8_t GetMotorState(uint8_t *buf,uint8_t len)
{
  return motor_get_state(buf,len);
}
/**
*@function uint8_t SetMotorTargetPosVel(MotorPosVel *motorParam)
*@brief    ���õ��Ŀ��λ�ú��ٶ�
*@param    motorParam ����Ҫ���õĲ���
*@return   0:λ�����ô��� 1���ٶ����ô��� 2�����óɹ�
*/
uint8_t SetMotorTargetPosVel(MotorPosVel *motorParam)
{
  if (motor_set_position(motorParam->position) != 1)
    //return 0;
   delay_us(10000);
  if (motor_set_velocity(motorParam->velocity) != 1)
    return 1;
  return 2;

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
*@function void test_hardware(void)
*@brief    Ӳ�����Գ���
*@param    void :��
*@return   ��
*/
void test_hardware(void)
{
//  if (GetLeftObstacleSensor() == 1)
//    SetLeftObstacleLed(LED_ON);
//  else
//    SetLeftObstacleLed( LED_OFF);
//  if (GetRightObstacleSensor() == 1)
//    SetRightObstacleLed(LED_ON);
//  else
//    SetRightObstacleLed( LED_OFF);
  if (GetIRLoactionSensor() == 0)
  {
    SetLeftObstacleLed(LED_ON);
    SetRightObstacleLed(LED_ON);
  }
  else
  {
    SetLeftObstacleLed(LED_OFF);
    SetRightObstacleLed(LED_OFF);
  }

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
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





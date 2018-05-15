/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         interfaces_bottom.c
* @author       zhou
* @version      V1.0
* @date         2018/5/14
* @brief        底调用接口程序文件
**************************************************************************************************
*/
#include "include.h"
/**
*@function void SetCAN(uint8_t state)
*@brief    通过canopen设置电机
*@param    state：ENABLE / DISABLE
*@return   无
*@date     2018/5/14
*/
void SetCAN(uint8_t state)
{
  if (state == DISABLE) // 关闭节点
  {
    motor_stop_node();
  }
  else
  {
    motor_set_syn_cycle(); // 设置同步周期
    motor_start_syn();     // 开启同步
    motor_start_node();    // 开启节点
  }
}
/**
*@function void SetMotor(uint8_t state)
*@brief    设置电压enable口状态
*@param    state：ENABLE/DISABLE
*@return   无
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
*@brief    获取电机状态,
*@param    buf:状态数据
*@param    len:状态数据长度
*@return   1:成功 0:失败
*@date     2018/5/14
*/
uint8_t GetMotorState(uint8_t *buf,uint8_t len)
{
  return motor_get_state(buf,len);
}
/**
*@function uint8_t SetMotorTargetPosVel(MotorPosVel *motorParam)
*@brief    设置电机目标位置和速度
*@param    motorParam ：需要设置的参数
*@return   0:位置设置错误 1：速度设置错误 2：设置成功
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
/*-------------------  电源控制 -------------------------------*/
/**
*@function void SetFan(uint8_t fan, uint8_t state)
*@brief    对风扇电源进行控制
*@param    fan :FAN1/FAN2
*@param    state ：状态ENABLE/DISABLE
*@return   无
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
*@brief    雷达电源控制
*@param    state ：ENABLE/DISABLE
*@return   无
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
*@brief     路由电源控制
*@param    state ：ENABLE/DISABLE
*@return   无
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
*@brief    imu电源控制
*@param    state :ENABLE/DISABLE
*@return   无
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
*@brief   获取输入的障避传感器的值
*@param    void :空
*@return   无
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
*@brief    读取右避障传感器输入值
*@param    void :空
*@return   无
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
*@brief    对左侧避障报警灯控制
*@param    state :LED_ON/LED_OFF/LED_BLINKING
*@return   无
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
*@brief    对右侧避障报警灯控制
*@param    state :LED_ON/LED_OFF/LED_BLINKING
*@return   无
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
*@brief    硬件测试程序
*@param    void :空
*@return   无
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
*@brief    获取光电定位信号
*@param    void :空
*@return   无
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





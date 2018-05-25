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
/**
*@function void control_left_oas_led(uint8_t onoff)
*@brief    左侧报警避障灯控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    右侧避障报警灯控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    预留输出3控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    预留输出2控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    预留输出1控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    运行灯控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    imu电源输出控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   无
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
*@brief    电机输出使能控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   无
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
*@brief    雷达电源控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   无
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
*@brief    路由器电源控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   无
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
*@brief     风扇1电源控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   无
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
*@brief     风扇2电源控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF
*@return   无
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
*@brief    电池灯输出控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    网络灯输出控制
*@param    onoff ：OUT_CONTROL_ON/OUT_CONTROL_OFF/OUT_CONTROL_BLINKING
*@return   无
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
*@brief    闪烁控制程序，根据标志翻转指定引脚
*@param    void 空
*@return   无
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
*@brief    控制初始化，将需要打开控制在初始化中打开
*@param    void ：空
*@return   无
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
/**
*@function void task_sensors_init(void)
*@brief    传感器任务初始化
*@param    void ：空
*@return   无
*/
void task_sensors_init(void)
{
  _TaskSensors.fun = task_sensors;
  _TaskSensors.state = TASK_STATE_RUN;
}
/**
*@function void task_sensors(void)
*@brief    传感器任务
*@return   无
*/
void task_sensors(void)
{
  #define FILTER_TIMES   2
  static uint8_t leftFilter = 0,rightFilter = 0;
  _TaskSensors.interval = 5;
  _TaskSensors.state    = TASK_STATE_DELAY;
   // 判断左侧避障开关是否有障碍，并操作对应LED
  if (GetLeftObstacleSensor() == 0)
  {
    if (++leftFilter > FILTER_TIMES) // 延时判断
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
  // 判断右侧避障开关是否有障碍，并操作对应LED
  if (GetRightObstacleSensor() == 0)
  {
    if (++rightFilter > FILTER_TIMES) // 延时判断
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

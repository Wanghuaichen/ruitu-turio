/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_gpio.h
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        gpio控制头文件
**************************************************************************************************
*/

#ifndef _OCP_GPIO_H_
#define _OCP_GPIO_H_
#include "include.h"
/*----------------------- 宏定义 -------------------  */
// OA : obstacle avoidance 避障
// RSV: reserved  预留

#define LED_SYS_Pin              GPIO_Pin_3
#define LED_SYS_GPIO_Port        GPIOC
#define ENCODER_Z_Pin            GPIO_Pin_0
#define ENCODER_Z_GPIO_Port      GPIOA
#define ENCODER_B_Pin            GPIO_Pin_1
#define ENCODER_B_GPIO_Port      GPIOA
#define ENCODER_A_Pin            GPIO_Pin_2
#define ENCODER_A_GPIO_Port      GPIOA
#define IR_LOCATION_Pin          GPIO_Pin_3
#define IR_LOCATION_GPIO_Port    GPIOA
#define W5500_NSS_Pin            GPIO_Pin_4
#define W5500_NSS_GPIO_Port      GPIOA
#define W5500_NINT_Pin           GPIO_Pin_4
#define W5500_NINT_GPIO_Port     GPIOC
#define W5500_RSTN_Pin           GPIO_Pin_5
#define W5500_RSTN_GPIO_Port     GPIOC
#define LED_OAS_LEFT_Pin         GPIO_Pin_12
#define LED_OAS_LEFT_GPIO_Port   GPIOB
#define RSV_OUT3_Pin             GPIO_Pin_13
#define RSV_OUT3_GPIO_Port       GPIOB
#define RSV_OUT2_Pin             GPIO_Pin_14
#define RSV_OUT2_GPIO_Port       GPIOB
#define RSV_OUT1_Pin             GPIO_Pin_15
#define RSV_OUT1_GPIO_Port       GPIOB
#define LED_RUN_Pin              GPIO_Pin_6
#define LED_RUN_GPIO_Port        GPIOC
#define POWER_IMU_Pin            GPIO_Pin_7
#define POWER_IMU_GPIO_Port      GPIOC
#define MOTOR_ENABLE_Pin         GPIO_Pin_8
#define MOTOR_ENABLE_GPIO_Port   GPIOC
#define LED_OAS_RIGNT_Pin        GPIO_Pin_9
#define LED_OAS_RIGNT_GPIO_Port  GPIOC
#define RS485_CON_Pin            GPIO_Pin_8
#define RS485_CON_GPIO_Port      GPIOA
#define POWER_LIDAR_Pin          GPIO_Pin_15
#define POWER_LIDAR_GPIO_Port    GPIOA
#define POWER_ROUTE_Pin          GPIO_Pin_10
#define POWER_ROUTE_GPIO_Port    GPIOC
#define POWER_FAN1_Pin           GPIO_Pin_11
#define POWER_FAN1_GPIO_Port     GPIOC
#define POWER_FAN2_Pin           GPIO_Pin_12
#define POWER_FAN2_GPIO_Port     GPIOC
#define LED_BATTERY_Pin          GPIO_Pin_2
#define LED_BATTERY_GPIO_Port    GPIOD
#define LED_ETHERNET_Pin         GPIO_Pin_3
#define LED_ETHERNET_GPIO_Port   GPIOB
#define RSV_IN1_Pin              GPIO_Pin_6
#define RSV_IN1_GPIO_Port        GPIOB
#define RSV_IN2_Pin              GPIO_Pin_5
#define RSV_IN2_GPIO_Port        GPIOB
#define RSV_IN3_Pin              GPIO_Pin_4
#define RSV_IN3_GPIO_Port        GPIOB
#define OAS_RIGHT_Pin            GPIO_Pin_8
#define OAS_RIGHT_GPIO_Port      GPIOB
#define OAS_LEFT_Pin             GPIO_Pin_9
#define OAS_LEFT_GPIO_Port       GPIOB
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/
void gpio_config_init(void);
void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





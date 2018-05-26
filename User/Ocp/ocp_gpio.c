/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_gpio.c
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        gpio控制文件
**************************************************************************************************
*/
#include "include.h"

void gpio_paramter_config(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;       //  定义GPIO初始化结构体        */


  //*Configure GPIO pin Output Level */
  GPIO_ResetBits(GPIOC, LED_SYS_Pin|W5500_RSTN_Pin|LED_RUN_Pin
                          |POWER_IMU_Pin|MOTOR_ENABLE_Pin|POWER_ROUTE_Pin
                          |POWER_FAN1_Pin|POWER_FAN2_Pin);

  //*Configure GPIO pin Output Level */
  GPIO_ResetBits(GPIOA, W5500_NSS_Pin|RS485_CON_Pin|POWER_LIDAR_Pin);

  //*Configure GPIO pin Output Level */
  GPIO_ResetBits(GPIOB, LED_OAS_Pin|RSV_OUT3_Pin|RSV_OUT2_Pin|RSV_OUT1_Pin
                          |LED_ETHERNET_Pin|RSV_IN3_Pin);

  //*Configure GPIO pin Output Level */
  GPIO_ResetBits(LED_BATTERY_GPIO_Port, LED_BATTERY_Pin);

  /**
    Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin PCPin PCPin PCPin
                           PCPin PCPin */
  GPIO_InitStruct.GPIO_Pin = LED_SYS_Pin|W5500_RSTN_Pin|LED_RUN_Pin
                             | POWER_IMU_Pin | MOTOR_ENABLE_Pin | MOTOR_HOMING_Pin| POWER_ROUTE_Pin
                          |POWER_FAN1_Pin|POWER_FAN2_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**
    Configure GPIO pins : PAPin PAPin PAPin PAPin
   */
  GPIO_InitStruct.GPIO_Pin = W5500_NINT_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  /**
    Configure GPIO pins : PAPin PAPin PAPin PAPin
   */
  GPIO_InitStruct.GPIO_Pin = IR_LOCATION_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**
  Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.GPIO_Pin = W5500_NSS_Pin|RS485_CON_Pin|POWER_LIDAR_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**
    Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin */
  GPIO_InitStruct.GPIO_Pin = LED_OAS_Pin|RSV_OUT3_Pin|RSV_OUT2_Pin|RSV_OUT1_Pin
                          |LED_ETHERNET_Pin|RSV_IN3_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**
  Configure GPIO pin : PtPin */
  GPIO_InitStruct.GPIO_Pin = LED_BATTERY_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(LED_BATTERY_GPIO_Port, &GPIO_InitStruct);

  /**
    Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.GPIO_Pin = RSV_IN1_Pin|RSV_IN2_Pin|RSV_IN3_Pin|OAS_RIGHT_Pin|OAS_LEFT_Pin|KEY2_IN_Pin|KEY1_IN_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void gpio_exti_config(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;//定义中断所需要的结构体，就像串口初始化
  EXTI_DeInit();//复位外部中断
 //初始化外部中断 8
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);//将中断线8配置到GPIOB-8管脚
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;//指定配置外部中断8
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//配制成中断模式
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//配制成下降沿处罚
  EXTI_Init(&EXTI_InitStructure);//将结构体给EXTI_Init函数

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);

  EXTI_InitStructure.EXTI_Line = EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line8|EXTI_Line9;//指定配置外部中断8
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//配制成中断模式
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//配制成下降沿处罚
  EXTI_Init(&EXTI_InitStructure);//将结构体给EXTI_Init函数

}
void gpio_NIVC_config(void)
{
  NVIC_InitTypeDef
  NVIC_INITStruture;//定义NVIC结构体
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//定义为组2，也就是2抢占位，2响应位
  NVIC_INITStruture.NVIC_IRQChannel = EXTI3_IRQn; //
  NVIC_INITStruture.NVIC_IRQChannelPreemptionPriority = 1;//配置抢占优先级
  NVIC_INITStruture.NVIC_IRQChannelSubPriority = 0;//配置响应优先级
  NVIC_INITStruture.NVIC_IRQChannelCmd = ENABLE;//使能中断线
  NVIC_Init(&NVIC_INITStruture);//初始化刚刚配置的中断

  NVIC_INITStruture.NVIC_IRQChannel = EXTI4_IRQn; //
  NVIC_INITStruture.NVIC_IRQChannelPreemptionPriority = 1;//配置抢占优先级
  NVIC_INITStruture.NVIC_IRQChannelSubPriority = 0;//配置响应优先级
  NVIC_INITStruture.NVIC_IRQChannelCmd = ENABLE;//使能中断线
  NVIC_Init(&NVIC_INITStruture);//初始化刚刚配置的中断

  NVIC_INITStruture.NVIC_IRQChannel = EXTI9_5_IRQn;//
  NVIC_INITStruture.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_INITStruture.NVIC_IRQChannelSubPriority = 0;
  NVIC_INITStruture.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_INITStruture);

  NVIC_EnableIRQ(EXTI4_IRQn);
}
/**
*@function void gpio_config_init(void)
*@brief    gpio配置初始化，包括时钟、管脚中断等
*@param    void ：空
*@return   无
*/
void gpio_config_init(void)
{
  //*-----------使能相关模块时钟 -----------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                         |RCC_APB2Periph_GPIOD
                         |RCC_APB2Periph_GPIOA
                         |RCC_APB2Periph_GPIOC
                         |RCC_APB2Periph_AFIO, ENABLE);              // /*  使能GPIO外设时钟            */
  /**
  SWJ接口设置
  */
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  gpio_paramter_config();
  gpio_exti_config();
  gpio_NIVC_config();
}
/**
*@function void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
*@brief    翻转对应端口的管脚状态
*@param    GPIOx：端口号
*@param    GPIO_Pin：管脚号
*@return   无
*@date     2018/5/4
*/
void gpio_toggle_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  //  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





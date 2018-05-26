/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_gpio.c
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        gpio�����ļ�
**************************************************************************************************
*/
#include "include.h"

void gpio_paramter_config(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;       //  ����GPIO��ʼ���ṹ��        */


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
  EXTI_InitTypeDef EXTI_InitStructure;//�����ж�����Ҫ�Ľṹ�壬���񴮿ڳ�ʼ��
  EXTI_DeInit();//��λ�ⲿ�ж�
 //��ʼ���ⲿ�ж� 8
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);//���ж���8���õ�GPIOB-8�ܽ�
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;//ָ�������ⲿ�ж�8
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//���Ƴ��ж�ģʽ
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//���Ƴ��½��ش���
  EXTI_Init(&EXTI_InitStructure);//���ṹ���EXTI_Init����

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);

  EXTI_InitStructure.EXTI_Line = EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line8|EXTI_Line9;//ָ�������ⲿ�ж�8
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//���Ƴ��ж�ģʽ
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//���Ƴ��½��ش���
  EXTI_Init(&EXTI_InitStructure);//���ṹ���EXTI_Init����

}
void gpio_NIVC_config(void)
{
  NVIC_InitTypeDef
  NVIC_INITStruture;//����NVIC�ṹ��
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����Ϊ��2��Ҳ����2��ռλ��2��Ӧλ
  NVIC_INITStruture.NVIC_IRQChannel = EXTI3_IRQn; //
  NVIC_INITStruture.NVIC_IRQChannelPreemptionPriority = 1;//������ռ���ȼ�
  NVIC_INITStruture.NVIC_IRQChannelSubPriority = 0;//������Ӧ���ȼ�
  NVIC_INITStruture.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж���
  NVIC_Init(&NVIC_INITStruture);//��ʼ���ո����õ��ж�

  NVIC_INITStruture.NVIC_IRQChannel = EXTI4_IRQn; //
  NVIC_INITStruture.NVIC_IRQChannelPreemptionPriority = 1;//������ռ���ȼ�
  NVIC_INITStruture.NVIC_IRQChannelSubPriority = 0;//������Ӧ���ȼ�
  NVIC_INITStruture.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж���
  NVIC_Init(&NVIC_INITStruture);//��ʼ���ո����õ��ж�

  NVIC_INITStruture.NVIC_IRQChannel = EXTI9_5_IRQn;//
  NVIC_INITStruture.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_INITStruture.NVIC_IRQChannelSubPriority = 0;
  NVIC_INITStruture.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_INITStruture);

  NVIC_EnableIRQ(EXTI4_IRQn);
}
/**
*@function void gpio_config_init(void)
*@brief    gpio���ó�ʼ��������ʱ�ӡ��ܽ��жϵ�
*@param    void ����
*@return   ��
*/
void gpio_config_init(void)
{
  //*-----------ʹ�����ģ��ʱ�� -----------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                         |RCC_APB2Periph_GPIOD
                         |RCC_APB2Periph_GPIOA
                         |RCC_APB2Periph_GPIOC
                         |RCC_APB2Periph_AFIO, ENABLE);              // /*  ʹ��GPIO����ʱ��            */
  /**
  SWJ�ӿ�����
  */
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  gpio_paramter_config();
  gpio_exti_config();
  gpio_NIVC_config();
}
/**
*@function void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
*@brief    ��ת��Ӧ�˿ڵĹܽ�״̬
*@param    GPIOx���˿ں�
*@param    GPIO_Pin���ܽź�
*@return   ��
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





/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_timer.c
* @author       zhou
* @version      V1.0
* @date         2018/5/10
* @brief        芯片上定时器程序文件
**************************************************************************************************
*/
#include "include.h"

/**
*@function void tim2_encode_io_config(void)
*@brief    定时器2编码器模式管脚配置
*@return   无
*/
void tim2_encode_io_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/**
*@function void tim2_encoder_NVIC_config(void)
*@brief    定时器2编码器模式中断配置
*@return   无
*/
void tim2_encoder_NVIC_config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/**
*@function void tim2_encoder_param_config(void)
*@brief   定时器2编码器模式参数配置
*@return   无
*/
void tim2_encoder_param_config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;

  //* Timer configuration in Encoder mode */
  TIM_DeInit(ENCODER_TIMER);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling //设定计数器分频系数为0，不分频
  TIM_TimeBaseStructure.TIM_Period = (ENCODER_TIM_PERIOD - 1);
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割 T_dts = T_ck_int
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数
  TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure);

  TIM_EncoderInterfaceConfig(ENCODER_TIMER, TIM_EncoderMode_TI12,
                           TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter =ICx_FILTER;//选择输入比较滤波器
  TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);

  // Clear all pending interrupts
  TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);//清除TIM1的更新标志位
  TIM_ITConfig(ENCODER_TIMER, TIM_IT_Update, ENABLE);

  //Reset counter
  ENCODER_TIMER->CNT = 0;

  TIM_Cmd(ENCODER_TIMER, ENABLE);
}
/**
*@function void tim2_encoder_init(void)
*@brief    定时器初始化，主要为编码器模式并且配置中断
*@param    void ：空
*@return   无
*/
void tim2_encoder_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能TIM1时钟
  tim2_encoder_NVIC_config();
  tim2_encode_io_config();
  tim2_encoder_param_config();
}




/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





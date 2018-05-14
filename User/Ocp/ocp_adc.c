/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_adc.c
* @author       zhou
* @version      V1.0
* @date         2018/5/9
* @brief        芯片内ADC配置文件
**************************************************************************************************
*/
#include "include.h"
void adc_NVIC_config(void);
void adc_gpio_config(void);
void adc_paramter_config(void);
void adc_config_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // 开启管脚时钟
  RCC_ADCCLKConfig(RCC_PCLK2_Div8);
  adc_NVIC_config();
  adc_gpio_config();
  adc_paramter_config();
}
void adc_NVIC_config(void)
{
#if (0)
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;//ADC1和ADC2 中断向量
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                        //0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif
}
void adc_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); // 开启管脚时钟

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void adc_paramter_config(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  //* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC_Mode_RegSimult;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;;     //扫描
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;   //连续
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 2;
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_DiscModeChannelCountConfig(ADC1,1);
  //* ADC1 regular channels configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_28Cycles5);  // L
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_28Cycles5);  // R
  //* Enable ADC1 */
  
  ADC_DiscModeCmd(ADC1,ENABLE);
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  //* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  //* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  //* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));


}

void get_adc_value(uint16_t *buf)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发所以对SWSTART置位。

    //while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
    delay_us(100);
    buf[0] = ADC_GetConversionValue(ADC1);//返回最近一次转换结果

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发所以对SWSTART置位。
    //delay_us(100);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

    buf[1] = ADC_GetConversionValue(ADC1);//返回最近一次转换结果

    ADC_SoftwareStartConvCmd(ADC1, DISABLE); //软件触发所以对SWSTART置位。
}










/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/

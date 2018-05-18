/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_timer.c
* @author       zhou
* @version      V1.0
* @date         2018/5/10
* @brief        оƬ�϶�ʱ�������ļ�
**************************************************************************************************
*/
#include "include.h"
//����������ƫ�Ƶ�ַ
//NVIC_VectTab:��ַ
//Offset:ƫ����
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)
{
  SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
  //���ڱ�ʶ����������CODE��������RAM��
}
//����NVIC����
//NVIC_Group:NVIC���� 0~4 �ܹ�5��
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)
{
  u32 temp,temp1;
  temp1=(~NVIC_Group)&0x07;//ȡ����λ
  temp1<<=8;
  temp=SCB->AIRCR;  //��ȡ��ǰ������
  temp&=0X0000F8FF; //�����ǰ����
  temp|=0X05FA0000; //д��Կ��
  temp|=temp1;
  SCB->AIRCR=temp;  //���÷���
}
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)
{
  u32 temp;
  MY_NVIC_PriorityGroupConfig(NVIC_Group);//���÷���
  temp=NVIC_PreemptionPriority<<(4-NVIC_Group);
  temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
  temp&=0xf;//ȡ����λ
  NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//ʹ���ж�λ(Ҫ����Ļ�,�෴������OK)
  NVIC->IP[NVIC_Channel]|=temp<<4;//������Ӧ���ȼ����������ȼ�
}
void Timer3_Init(void)
{
  RCC->APB1ENR|=1<<1;//TIM3ʱ��ʹ��
  TIM3->ARR = 99;      //�趨�������Զ���װֵ
  TIM3->PSC = 7199;      //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
  TIM3->DIER|=1<<0;   //��������ж�
  TIM3->DIER|=1<<6;   //�������ж�
  TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��
  MY_NVIC_Init(1,3,TIM3_IRQn,2);
}

void Encoder_Init_TIM5(void)
{
  RCC->APB1ENR|=1<<0;     //TIM2ʱ��ʹ��
  RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
  GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
  GPIOA->CRL|=0X00000044;//��������
  /* �Ѷ�ʱ����ʼ��Ϊ������ģʽ */
  TIM2->PSC = 0x0;//Ԥ��Ƶ��
  TIM2->ARR = ENCODER_TIM_PERIOD-1;//�趨�������Զ���װֵ
  TIM2->CCMR1 |= 1<<0;          //����ģʽ��IC1FP1ӳ�䵽TI1��
  TIM2->CCMR1 |= 1<<8;          //����ģʽ��IC2FP2ӳ�䵽TI2��
  TIM2->CCER |= 0<<1;           //IC1������
  TIM2->CCER |= 0<<5;           //IC2������
  TIM2->SMCR |= 3<<0;           //SMS='011' ���е�������������غ��½�����Ч
  TIM2->CNT = COUNTER_RESET;
  TIM2->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}

uint16_t Read_Encoder(void)
{
  return (uint16_t)(TIM2->CNT);
}
void tim2_encode_io_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void tim2_encoder_NVIC_config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void tim2_encoder_param_config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;

  //* Timer configuration in Encoder mode */
  TIM_DeInit(ENCODER_TIMER);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling //�趨��������Ƶϵ��Ϊ0������Ƶ
  TIM_TimeBaseStructure.TIM_Period = (ENCODER_TIM_PERIOD - 1);
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ� T_dts = T_ck_int
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM���ϼ���
  TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure);

  TIM_EncoderInterfaceConfig(ENCODER_TIMER, TIM_EncoderMode_TI12,
                           TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter =ICx_FILTER;//ѡ������Ƚ��˲���
  TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);

  // Clear all pending interrupts
  TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);//���TIM1�ĸ��±�־λ
  TIM_ITConfig(ENCODER_TIMER, TIM_IT_Update, ENABLE);

  //Reset counter
  ENCODER_TIMER->CNT = 0;

  TIM_Cmd(ENCODER_TIMER, ENABLE);
}
void tim2_encoder_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ��TIM1ʱ��
  tim2_encoder_NVIC_config();
  tim2_encode_io_config();
  tim2_encoder_param_config();
}




/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





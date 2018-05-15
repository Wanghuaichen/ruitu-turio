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
	TIM2->SMCR |= 3<<0;	          //SMS='011' ���е�������������غ��½�����Ч
	TIM2->CNT = COUNTER_RESET;
	TIM2->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
}

uint16_t Read_Encoder(void)
{
  return (uint16_t)(TIM2->CNT);
}






/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





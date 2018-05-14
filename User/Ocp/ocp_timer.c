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
//设置向量表偏移地址
//NVIC_VectTab:基址
//Offset:偏移量			 
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 	   	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//设置NVIC的向量表偏移寄存器
	//用于标识向量表是在CODE区还是在RAM区
}
//设置NVIC分组
//NVIC_Group:NVIC分组 0~4 总共5组 		   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//取后三位
	temp1<<=8;
	temp=SCB->AIRCR;  //读取先前的设置
	temp&=0X0000F8FF; //清空先前分组
	temp|=0X05FA0000; //写入钥匙
	temp|=temp1;	   
	SCB->AIRCR=temp;  //设置分组	    	  				   
}
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//设置分组
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//取低四位  
	NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//使能中断位(要清除的话,相反操作就OK) 
	NVIC->IP[NVIC_Channel]|=temp<<4;//设置响应优先级和抢断优先级   	    	  				   
} 
void Timer3_Init(void)
{
  RCC->APB1ENR|=1<<1;//TIM3时钟使能
  TIM3->ARR = 99;      //设定计数器自动重装值
  TIM3->PSC = 7199;      //预分频器7200,得到10Khz的计数时钟
  TIM3->DIER|=1<<0;   //允许更新中断
  TIM3->DIER|=1<<6;   //允许触发中断
  TIM3->CR1|=0x01;    //使能定时器
  MY_NVIC_Init(1,3,TIM3_IRQn,2);
}

void Encoder_Init_TIM5(void)
{
	RCC->APB1ENR|=1<<0;     //TIM2时钟使能
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟
	GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
	GPIOA->CRL|=0X00000044;//浮空输入
	/* 把定时器初始化为编码器模式 */ 
	TIM2->PSC = 0x0;//预分频器
	TIM2->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
  TIM2->CCMR1 |= 1<<0;          //输入模式，IC1FP1映射到TI1上
  TIM2->CCMR1 |= 1<<8;          //输入模式，IC2FP2映射到TI2上
  TIM2->CCER |= 0<<1;           //IC1不反向
  TIM2->CCER |= 0<<5;           //IC2不反向
	TIM2->SMCR |= 3<<0;	          //SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM2->CNT = COUNTER_RESET;
	TIM2->CR1 |= 0x01;    //CEN=1，使能定时器
//  RCC->APB1ENR|=1<<3;     //TIM5时钟使能
//  RCC->APB2ENR|=1<<2;    //使能PORTA时钟
//  GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
//	GPIOA->CRL|=0X00000044;//浮空输入
//	/* 把定时器初始化为编码器模式 */ 
//	TIM5->PSC = 0x0;//预分频器
//	TIM5->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
//  TIM5->CCMR1 |= 1<<0;          //输入模式，IC1FP1映射到TI1上
//  TIM5->CCMR1 |= 1<<8;          //输入模式，IC2FP2映射到TI2上
//  TIM5->CCER |= 0<<1;           //IC1不反向
//  TIM5->CCER |= 0<<5;           //IC2不反向
//	TIM5->SMCR |= 3<<0;	          //SMS='011' 所有的输入均在上升沿和下降沿有效
//	TIM5->CNT = COUNTER_RESET;
//	TIM5->CR1 |= 0x01;    //CEN=1，使能定时器
////  GPIOA->CRL&=0XFFFFF00F;//PA0 PA1
////  GPIOA->CRL|=0X00000440;//浮空输入
////  /* 把定时器初始化为编码器模式 */
////  TIM5->PSC = 0x0;//预分频器
////  TIM5->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值
////  TIM5->CCMR1 |= 1<<8;          //输入模式，IC2FP2映射到TI2上
////  TIM5->CCMR2 |= 1<<0;          //输入模式，IC1FP1映射到TI1上
////  TIM5->CCER |= 0<<5;           //IC2不反向
////  TIM5->CCER |= 0<<9;           //IC2不反向
////  TIM5->SMCR |= 3<<0;           //SMS='011' 所有的输入均在上升沿和下降沿有效
////  TIM5->CNT = COUNTER_RESET;
////  TIM5->CR1 |= 0x01;    //CEN=1，使能定时器
}

uint16_t Read_Encoder(void)
{
  return (uint16_t)(TIM2->CNT);
}






/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





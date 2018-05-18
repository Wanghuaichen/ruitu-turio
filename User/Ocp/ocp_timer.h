/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_timer.h
* @author       zhou
* @version      V1.0
* @date         2018/5/10
* @brief        оƬ�϶�ʱ��ͷ�ļ�
**************************************************************************************************
*/
#ifndef _OCP_TIMER_H_
#define _OCP_TIMER_H_
#include "include.h"
/*--------------- �궨�� --------------*/
#define ENCODER_TIMER   TIM2  // Encoder unit connected to TIM2
#define COUNTER_RESET          0
#define ENCODER_TIM_PERIOD     (u16)(40)
#define ICx_FILTER      (u8) 6 // 6<-> 670nsec
/*--------------- �������� --------------*/

/*--------------- �������� --------------*/
void Timer3_Init(void);
void Encoder_Init_TIM5(void);
uint16_t Read_Encoder(void);
void tim2_encoder_init(void);
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





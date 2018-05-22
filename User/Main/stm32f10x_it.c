/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include "include.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
#ifndef RTE_CMSIS_RTOS_RTX
void SVC_Handler(void)
{
}
#endif

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
#ifndef RTE_CMSIS_RTOS_RTX
void PendSV_Handler(void)
{
}
#endif

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
#ifndef RTE_CMSIS_RTOS_RTX
void SysTick_Handler(void)
{
  uint8_t i;
  sysTick_++;
  for (i = 0; i < taskID_; i++)
  {
      if (_TaskFlow[i]->state == TASK_STATE_DELAY)
      {
          if (--_TaskFlow[i]->interval == 0) _TaskFlow[i]->state = TASK_STATE_RUN;
      }
      else if (_TaskFlow[i]->state == TASK_STATE_RUN)
      {
          _TaskFlow[i]->timeOut++;
      }
  }
}
#endif
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
/**
  * @brief  This function handles ETH interrupt request.
  * @param  None
  * @retval None
  */
void ETH_IRQHandler(void)
{

}
/**
  * @brief  This function handles USART1_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
  uint16_t rxData;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);        /* 清除接收中断标志  */
    rxData = (uint16_t)(USART1->DR & (uint16_t)0x01FF);   /* 读取数据 */
    Circle_Write_Byte(&sUart1RxCircleBuf_,rxData);
  }
  if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
  {
    USART_ClearITPendingBit(USART1,USART_IT_IDLE);            /* 清除接收中断标志   */
    rxData = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
    _TaskUartRx.info |= UART1_RX_DATA;
    _TaskUartRx.state = TASK_STATE_RUN;
  }

}
/**
  * @brief  This function handles USART3_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
  uint16_t rxData;
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
  {
    USART_ClearITPendingBit(USART3,USART_IT_IDLE);                  /* 清除接收中断标志             */
    rxData = (uint16_t)(USART3->DR & (uint16_t)0x01FF);
    _TaskUartRx.info |= UART3_RX_DATA;
    _TaskUartRx.state = TASK_STATE_RUN;
  }
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART3,USART_IT_RXNE);                  /* 清除接收中断标志             */
    rxData = (uint16_t)(USART3->DR & (uint16_t)0x01FF);             /* 读取数据 */
    Circle_Write_Byte(&sUart3RxCircleBuf_,rxData);
  }


}
/**
  * @brief  This function handles CAN1_RX0_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
  {
    CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);                                       /*  清除中断标志                */

    CAN_Receive(CAN1,CAN_FIFO0,&sCan1Buf_.rxMsg[sCan1Buf_.top++]);                    /* 获取发数据                */
    if ( sCan1Buf_.top >= CAN_BUF_LENGTH)
      sCan1Buf_.top = 0;
  }
}
/**
  * @brief  This function handles EXTI3_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
  if(SET == EXTI_GetFlagStatus(EXTI_Line3))
  {
    EXTI_ClearFlag(EXTI_Line3);

  }
}
/**
  * @brief  This function handles EXTI4_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
  if(SET == EXTI_GetFlagStatus(EXTI_Line4))
  {
    EXTI_ClearFlag(EXTI_Line4);

  }
}
/**
  * @brief  This function handles EXTI9_5_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
  if(SET == EXTI_GetFlagStatus(EXTI_Line5))
  {
    EXTI_ClearFlag(EXTI_Line5);

  }
  else if(SET == EXTI_GetFlagStatus(EXTI_Line6))
  {
    EXTI_ClearFlag(EXTI_Line6);

  }
  else if(SET == EXTI_GetFlagStatus(EXTI_Line8))
  {
    EXTI_ClearFlag(EXTI_Line8);

  }
  else if(SET == EXTI_GetFlagStatus(EXTI_Line9))
  {
    EXTI_ClearFlag(EXTI_Line9);

  }
}
void TIM3_IRQHandler(void)
{

//  uint16_t encoderNew = 0;
  if(TIM3->SR&0X0001)//10ms定时中断
  {
      TIM3->SR&=~(1<<0);           //===清除定时器1中断标志位
 //     encoderNew = Read_Encoder();     //===读取编码器的位置数据 初始值是10000，详见encoder.c 和encoder.h
//      if ((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF)
//      {
//        TIM2->SR &= ~TIM_SR_UIF;
//        if (encoderNew > 32786)
//          encoderUpdata--;
//        else
//          encoderUpdata++;
//      }
//      encoderPlusNum_ = (int64_t)(encoderUpdata*65535) + (int64_t)encoderNew;
//      encoderPosition_ =(double_t)(encoderPlusNum_/ 39.37);
//      //encoderPosition_ *= DIV_FREQ;
  }

}
void TIM2_IRQHandler(void)
{
  uint16_t encoderNew = 0;
  if ((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF)
  {
    TIM2->SR &= ~TIM_SR_UIF;
    encoderNew = (uint16_t)(TIM2->CNT);
    if (encoderNew > 20)
    {
      encoderPlusNum_--;
      sRobotStatus_.CurrentDir = 0;
      if ((IR_LOCATION_GPIO_Port->IDR & IR_LOCATION_Pin) == (uint32_t)Bit_RESET)
        irLocationNum_++;
    }
    else
    {
      encoderPlusNum_++;
      sRobotStatus_.CurrentDir = 1;
      if ((IR_LOCATION_GPIO_Port->IDR & IR_LOCATION_Pin) == (uint32_t)Bit_RESET)
        irLocationNum_--;
      if ((0 - irLocationNum_) > 28)
      {
        //MOTOR_ENABLE_GPIO_Port->BRR = MOTOR_ENABLE_Pin;
        RSV_OUT1_GPIO_Port->BSRR = RSV_OUT1_Pin;
      }
    }
  }
}
/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/



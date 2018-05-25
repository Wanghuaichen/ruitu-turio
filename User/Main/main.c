/**
*************************(C) COPYRIGHT 2017 ********************************************
* @file         main.c
* @author       zhou
* @version      V1.0
* @date         2018/1/10
* @brief        main函数运行文件
**************************************************************************************************
*/
#include "include.h"

static void system_setup(void);

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif
PUTCHAR_PROTOTYPE
{
//    HAL_UART_Transmit(&huart5 ,(uint8_t *)&ch, 1, 0xFFFF);
    //HAL_UART_Transmit_IT(&huart1,(uint8_t *)&ch, 1); // 长度无法变化
  USART_SendData(USART3, (uint16_t)ch);
//  while( USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
  {
  } //等待字符发送完毕
  return ch;
}

int main (void)
{
  system_setup();
  param_default_set();
  w5500_restart();
  w5500_config_gateway(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
  w5500_config_ip(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
  w5500_config_macAddress(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
 // w5500_config_subnetMask(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
////  /* Initilaize the LwIP satck */
  socket_buf_init(txsize, rxsize);    /*初始化8个Socket的发送接收缓存大小*/

 SetMotor(ENABLE);
 task_init();
  while(1)
  {
      task_run();
  }
}


/**
  * @brief  Setup STM32 system (clocks, Ethernet, GPIO, NVIC) and STM3210C-EVAL resources.
  * @param  None
  * @retval None
  */
void system_setup(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  //* Setup STM32 clock, PLL and Flash configuration) */
  SystemInit();

//  //*---gpio 初始化----      */
  gpio_config_init();
//  //* Configure the uart */
  uart_init();
//  //* Configure the can */
  can1_init();
 /// configure the spi
  spi1_init();
  // adc 配置初始化
  adc_config_init();
  //* SystTick configuration: an interrupt every 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000);
  //* Update the SysTick IRQ priority should be higher than the Ethernet IRQ */
  //* The Localtime should be updated during the Ethernet packets processing */
  NVIC_SetPriority (SysTick_IRQn, 1);
  // 编码器用定时器初始化
  tim2_encoder_init();
  /* Configure the param */
  task_uart_rx_init();

}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /**
     User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /**
     Infinite loop */
  while (1)
  {
  }
}
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





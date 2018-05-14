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
uint8_t motorTest[8];
uint32_t canID = 0x701;
uint16_t adcValue[100][2];
int main (void)
{

  uint32_t ti = 0;
  uint8_t step = 0;
  system_setup();
  sDefaultNetConfig_.localIP[0] = 192;
  sDefaultNetConfig_.localIP[1] = 168;
  sDefaultNetConfig_.localIP[2] = 1;
  sDefaultNetConfig_.localIP[3] = 19;

  sDefaultNetConfig_.gateWay[0] = 192;
  sDefaultNetConfig_.gateWay[1] = 168;
  sDefaultNetConfig_.gateWay[2] = 1;
  sDefaultNetConfig_.gateWay[3] = 1;

  sDefaultNetConfig_.macAddress[0] = 0x1A;
  sDefaultNetConfig_.macAddress[1] = 0x2A;
  sDefaultNetConfig_.macAddress[2] = 0x3A;
  sDefaultNetConfig_.macAddress[3] = 0x4A;
  sDefaultNetConfig_.macAddress[4] = 0x5A;
  sDefaultNetConfig_.macAddress[5] = 0x6A;


  sDefaultNetConfig_.subnetMask[0] = 255;
  sDefaultNetConfig_.subnetMask[1] = 255;
  sDefaultNetConfig_.subnetMask[2] = 255;
  sDefaultNetConfig_.subnetMask[3] = 0;

  sDefaultNetConfig_.localPort = 502;
  w5500_restart();
 // w5500_config_gateway(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
  w5500_config_ip(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
  w5500_config_macAddress(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
 // w5500_config_subnetMask(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
////  /* Initilaize the LwIP satck */
  socket_buf_init(txsize, rxsize);    /*初始化8个Socket的发送接收缓存大小*/
 // printf("good job!");
  while(1)
  {
    ti++;
    if (ti > 5000)
    {
      switch(step++)
      {
        case 1:
          canID = 0x701;
          can_tx_data_package(CAN1,motorTest,8,canID,CAN_RTR_REMOTE);break;
        case 2:
          canID = 0x00;
          motorTest[0] = START_REMOTE_NODE;
          can_tx_data_package(CAN1,motorTest,8,canID,CAN_RTR_DATA);break;
        case 3:
          canID = 0x701;
          can_tx_data_package(CAN1,motorTest,8,canID,CAN_RTR_REMOTE);break;
        case 4:
          canID = 0x00;
          motorTest[0] = STOP_REMOTE_NODE;
          can_tx_data_package(CAN1,motorTest,8,canID,CAN_RTR_DATA);break;
        case 5:
          canID = 0x701;
          can_tx_data_package(CAN1,motorTest,8,canID,CAN_RTR_REMOTE);break;
        default: break;
      }
      if (step % 2)
       ;// control_all_off();
      else
        control_all_on();
      ti = 0;
      gpio_toggle_pin(LED_SYS_GPIO_Port,LED_SYS_Pin);
      get_adc_value(adcValue[step]);
      adcValue[step][1] = computer_tempature(adcValue[step][0]);
      if (step >= 100)
        step = 0;
    }
    do_tcp_server();
//    USART_SendData(USART3,0x036);
//    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
//      {
//      } //等待字符发送完毕
//      delay_us(100000);
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

  //* Enable USART2 clock */
  // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);



//  //* Enable GPIOs and ADC1 clocks */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
//                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO |
//             RCC_APB2Periph_ADC1, ENABLE);
//  //*---gpio 初始化----      */
  gpio_config_init();
//  //* Configure the uart */
  uart_init();

//  //* Configure the can */
  can1_init();
 /// configure the spi
  spi1_init();
adc_config_init();
  //* SystTick configuration: an interrupt every 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000);
Timer3_Init();
Encoder_Init_TIM5();
  //* Update the SysTick IRQ priority should be higher than the Ethernet IRQ */
  //* The Localtime should be updated during the Ethernet packets processing */
  NVIC_SetPriority (SysTick_IRQn, 1);

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
  {}
}
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





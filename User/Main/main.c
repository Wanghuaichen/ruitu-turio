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
uint8_t battary[8] = {0x01,0x03,0x00,0x12,0x00,0x01,0x24,0x0F};
uint8_t motorTest[8];
uint32_t canID = 0x701;
uint16_t adcValue[100][2];

extern double_t encoderPosition_ = 0;
extern int32_t encoderUpdata = 0;
struct record {const char *precision;double lat,lon;const char *address,*city,*state,*zip,*country; };
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
  w5500_config_gateway(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
  w5500_config_ip(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
  w5500_config_macAddress(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
 // w5500_config_subnetMask(&sDefaultNetConfig_, W5500_WRITE_PARAMETER);
////  /* Initilaize the LwIP satck */
  socket_buf_init(txsize, rxsize);    /*初始化8个Socket的发送接收缓存大小*/
 // printf("good job!");

queryRegAddr_ = BATTERY_REG_VOTAGE;
 SetMotor(ENABLE);
 task_init();
// motor_start_position_mode();
// printf ("%s %s %s%d\n","i","r0","0x",8000);
//control_reserved_out1(OUT_CONTROL_ON);
  while(1)
  {
    ti++;
    if (ti > 200000)
    {
      switch(step++)
      {

//        case 4:SetMotorTargetPosVel(&motorP);break;
//        case 2: SetCAN(ENABLE);break;
//        case 3: GetMotorState(motorTest,8);break;
//        case 5: motor_start_position_mode();break;
//      case 1:queryRegAddr_ = BATTERY_REG_VOTAGE;break;
//      case 2:queryRegAddr_ = BATTERY_REG_VOTAGE_PERCENT;break;
//      case 3:queryRegAddr_ = BATTERY_REG_CURRENT;break;
//      case 1:printf ("%s\n","r");break;
//      case 5:printf ("%s %s %s%d\n","i","r0","0x",8000);break;
//       case 3:printf ("%s %s %d\n","i","r3",1000);break;
//        case 5:printf ("%s %s %d\n","i","r4",300);break;
//        case 7:printf ("%s %s %s%d\n","i","r0","0x",8001);break;
       case 3:  _TaskMotorControl.state = TASK_STATE_RUN;
        _TaskMotorControl.progressBar = 0;
        break;
        default: break;
      }

//      get_adc_value(adcValue[step]);
//      adcValue[step][1] = computer_tempature(adcValue[step][0]);
      if (step >= 20)
        step = 10;
      battery_control(queryRegAddr_);
         ti = 0;
      }
    //



    //  printf ("%s %s %s%d\n","i","r0","0x",8000);

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
 // Encoder_Init_TIM5();
 tim2_encoder_init();
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
  {
  }
}
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





/**
*************************(C) COPYRIGHT 2017 ********************************************
* @file         bsp_uart.c
* @author       zhou
* @version      V1.0
* @date         2018/1/11
* @brief        串口配置文件
**************************************************************************************************
*/
#include "include.h"

static void usart1_NVIC_config(void);
static void usart1_gpio_config(void);
static void usart1_parameter_config(void);
static void usart1_init(void);
static void usart3_NVIC_config(void);
static void usart3_gpio_config(void);
static void usart3_parameter_config(void);
static void usart3_init(void);


/**
*@function void Uart_Init(void)
*@brief    串口初始化，所有串口在这里初始化
*@return   无
*@date     2018/1/11
*/
void uart_init(void)
{
  usart1_init();
  usart3_init();
}
/**
*@function void Uart1_NVIC_Config(void)
*@brief    串口1中断配置
*@return   无
*@date     2018/1/11
*/
static void usart1_NVIC_config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
/**
*@function void uart1_gpio_config(void)
*@brief    uart1引脚配置
*@return   无
*@date     2018/5/4
*/
static void usart1_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    ///*  定义GPIO初始化结构体        */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //  使能GPIO外设时钟
  // 重映射端口连接模
  GPIO_PinRemapConfig(GPIO_Remap_USART1,DISABLE);        // 引脚连接模块不重映射        */

  //   GPIO引脚始化
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;          // 设置RX引脚模式              */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;           // 设置TX引脚模式              */
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

}
/**
*@function void uart1_parameter_config(void)
*@brief    uart1参数配置,包括波特率等
*@return   无
*@date     2018/5/4
*/
static void usart1_parameter_config(void)
{
  USART_InitTypeDef USART_InitStructure;  ///*  定义USART初始化结构体       */

  //  UART1设置始化
  USART_InitStructure.USART_BaudRate  = 115200;              // 波特率
  USART_InitStructure.USART_WordLength= USART_WordLength_8b; // 数据位
  USART_InitStructure.USART_StopBits  = USART_StopBits_1;    // 停止位
  USART_InitStructure.USART_Parity    = USART_Parity_No;     // 校验模式
  USART_InitStructure.USART_Mode      = USART_Mode_Rx|USART_Mode_Tx; // 接收和发送模式
  USART_InitStructure.USART_HardwareFlowControl =
                      USART_HardwareFlowControl_None;   // 硬件流控制
  USART_Init(USART1,&USART_InitStructure);              // 初始化

  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //  使能UART1空闲中断
  USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);  //  使能UART1空闲中断

  //启动外设运行
  USART_Cmd(USART1,ENABLE);  // 启动USART1外设
}
/**
*@function void uart1_init(void)
*@brief   uart1初始化,时钟\中断\gpio\参数
*@param    void
*@return   无
*@date     2018/5/4
*/
void usart1_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);   //  使能USART1外设时钟
  usart1_NVIC_config();                  // 允许Uart1外设中断
  usart1_gpio_config();                  // gpio配置
  usart1_parameter_config();             // 参数配置
}
/**
*@function void Uart1_NVIC_Config(void)
*@brief    串口1中断配置
*@return   无
*@date     2018/1/11
*/
static void usart3_NVIC_config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
/**
*@function void uart1_gpio_config(void)
*@brief    uart1引脚配置
*@return   无
*@date     2018/5/4
*/
static void usart3_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    ///*  定义GPIO初始化结构体        */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //  使能GPIO外设时钟

  //   GPIO引脚始化
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;          // 设置RX引脚模式              */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;           // 设置TX引脚模式              */
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB,&GPIO_InitStructure);

}
/**
*@function void uart1_parameter_config(void)
*@brief    uart1参数配置,包括波特率等
*@return   无
*@date     2018/5/4
*/
static void usart3_parameter_config(void)
{
  USART_InitTypeDef USART_InitStructure;  ///*  定义USART初始化结构体       */

  //  UART1设置始化
  USART_InitStructure.USART_BaudRate  = 115200;              // 波特率
  USART_InitStructure.USART_WordLength= USART_WordLength_8b; // 数据位
  USART_InitStructure.USART_StopBits  = USART_StopBits_1;    // 停止位
  USART_InitStructure.USART_Parity    = USART_Parity_No;     // 校验模式
  USART_InitStructure.USART_Mode      = USART_Mode_Rx|USART_Mode_Tx; // 接收和发送模式
  USART_InitStructure.USART_HardwareFlowControl =
                      USART_HardwareFlowControl_None;   // 硬件流控制
  USART_Init(USART3,&USART_InitStructure);              // 初始化

  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);  //  使能UART1空闲中断
  USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);  //  使能UART1空闲中断

  //启动外设运行
  USART_Cmd(USART3,ENABLE);  // 启动USART3外设
}
/**
*@function void uart1_init(void)
*@brief   uart1初始化,时钟\中断\gpio\参数
*@param    void
*@return   无
*@date     2018/5/4
*/
void usart3_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   //  使能USART3外设时钟
  usart3_NVIC_config();                  // 允许Uart1外设中断
  usart3_gpio_config();                  // gpio配置
  usart3_parameter_config();             // 参数配置
}
/**
*@function void rs485_select_tx_rx(uint8_t rxTx)
*@brief    因485为半双工所以需要所选是发送还是接收模式
*@param    rxTx：RS485_TX：发送模式@
*@               RS485_RX: 接收模式
*@return   无
*@date     2018/5/9
*/
void rs485_select_tx_rx(uint8_t rxTx)
{
  if (rxTx == RS485_TX)
    GPIO_SetBits(RS485_CON_GPIO_Port,RS485_CON_Pin);
  else
    GPIO_ResetBits(RS485_CON_GPIO_Port,RS485_CON_Pin);
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





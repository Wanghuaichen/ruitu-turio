/**
*************************(C) COPYRIGHT 2017 ********************************************
* @file         bsp_uart.c
* @author       zhou
* @version      V1.0
* @date         2018/1/11
* @brief        ���������ļ�
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
*@brief    ���ڳ�ʼ�������д����������ʼ��
*@return   ��
*@date     2018/1/11
*/
void uart_init(void)
{
  usart1_init();
  usart3_init();
}
/**
*@function void Uart1_NVIC_Config(void)
*@brief    ����1�ж�����
*@return   ��
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
*@brief    uart1��������
*@return   ��
*@date     2018/5/4
*/
static void usart1_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    ///*  ����GPIO��ʼ���ṹ��        */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //  ʹ��GPIO����ʱ��
  // ��ӳ��˿�����ģ
  GPIO_PinRemapConfig(GPIO_Remap_USART1,DISABLE);        // ��������ģ�鲻��ӳ��        */

  //   GPIO����ʼ��
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;          // ����RX����ģʽ              */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;           // ����TX����ģʽ              */
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

}
/**
*@function void uart1_parameter_config(void)
*@brief    uart1��������,���������ʵ�
*@return   ��
*@date     2018/5/4
*/
static void usart1_parameter_config(void)
{
  USART_InitTypeDef USART_InitStructure;  ///*  ����USART��ʼ���ṹ��       */

  //  UART1����ʼ��
  USART_InitStructure.USART_BaudRate  = 9600;              // ������
  USART_InitStructure.USART_WordLength= USART_WordLength_8b; // ����λ
  USART_InitStructure.USART_StopBits  = USART_StopBits_1;    // ֹͣλ
  USART_InitStructure.USART_Parity    = USART_Parity_No;     // У��ģʽ
  USART_InitStructure.USART_Mode      = USART_Mode_Rx|USART_Mode_Tx; // ���պͷ���ģʽ
  USART_InitStructure.USART_HardwareFlowControl =
                      USART_HardwareFlowControl_None;   // Ӳ��������
  USART_Init(USART1,&USART_InitStructure);              // ��ʼ��

  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //  ʹ��UART1�����ж�
  USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);  //  ʹ��UART1�����ж�

  //������������
  USART_Cmd(USART1,ENABLE);  // ����USART1����
}
/**
*@function void uart1_init(void)
*@brief   uart1��ʼ��,ʱ��\�ж�\gpio\����
*@param    void
*@return   ��
*@date     2018/5/4
*/
void usart1_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);   //  ʹ��USART1����ʱ��
  usart1_NVIC_config();                  // ����Uart1�����ж�
  usart1_gpio_config();                  // gpio����
  usart1_parameter_config();             // ��������
}
/**
*@function void Uart1_NVIC_Config(void)
*@brief    ����1�ж�����
*@return   ��
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
*@brief    uart1��������
*@return   ��
*@date     2018/5/4
*/
static void usart3_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    ///*  ����GPIO��ʼ���ṹ��        */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //  ʹ��GPIO����ʱ��

  //   GPIO����ʼ��
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;          // ����RX����ģʽ              */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;           // ����TX����ģʽ              */
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB,&GPIO_InitStructure);

}
/**
*@function void uart1_parameter_config(void)
*@brief    uart1��������,���������ʵ�
*@return   ��
*@date     2018/5/4
*/
static void usart3_parameter_config(void)
{
  USART_InitTypeDef USART_InitStructure;  ///*  ����USART��ʼ���ṹ��       */

  //  UART1����ʼ��
  USART_InitStructure.USART_BaudRate  = 9600;              // ������
  USART_InitStructure.USART_WordLength= USART_WordLength_8b; // ����λ
  USART_InitStructure.USART_StopBits  = USART_StopBits_1;    // ֹͣλ
  USART_InitStructure.USART_Parity    = USART_Parity_No;     // У��ģʽ
  USART_InitStructure.USART_Mode      = USART_Mode_Rx|USART_Mode_Tx; // ���պͷ���ģʽ
  USART_InitStructure.USART_HardwareFlowControl =
                      USART_HardwareFlowControl_None;   // Ӳ��������
  USART_Init(USART3,&USART_InitStructure);              // ��ʼ��

  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);  //  ʹ��UART1�����ж�
  USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);  //  ʹ��UART1�����ж�

  //������������
  USART_Cmd(USART3,ENABLE);  // ����USART3����
}
/**
*@function void uart1_init(void)
*@brief   uart1��ʼ��,ʱ��\�ж�\gpio\����
*@param    void
*@return   ��
*@date     2018/5/4
*/
void usart3_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   //  ʹ��USART3����ʱ��
  usart3_NVIC_config();                  // ����Uart1�����ж�
  usart3_gpio_config();                  // gpio����
  usart3_parameter_config();             // ��������
}
/**
*@function void rs485_select_tx_rx(uint8_t rxTx)
*@brief    ��485Ϊ��˫��������Ҫ��ѡ�Ƿ��ͻ��ǽ���ģʽ
*@param    rxTx��RS485_TX������ģʽ@
*@               RS485_RX: ����ģʽ
*@return   ��
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





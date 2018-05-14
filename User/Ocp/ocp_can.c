/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         can.c
* @author       zhou
* @version      V1.0
* @date         2017-08-11
* @brief        can通信函数文件
**************************************************************************************************
*/
#include "include.h"

//*------------ 以下是can1端口配置 -------------------------------*/
/**
*@function void can1_nvic_config(void)
*@brief    can中断初始化函数
*@return   无
*@date     2018/5/4
*/
void can1_NVIC_config(void)//CAN RX0 中断优先级配置
{
  NVIC_InitTypeDef NVIC_InitStructure;//Configure the NVIC Preemption Priority Bits

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;//enabling interrupt
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
*@function void can1_gpio_config(void)
*@brief    can1对应管脚配置
*@return   无
*@date     2018/5/4
*/
void can1_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//使能PORTA时钟
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1,DISABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    //初始化IO

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化IO
}

/**
*@function void can1_parameter_config(void)
*@brief    can1参数配置，包括通信参数、波特率及过滤器等
*@return   无
*@date     2018/5/4
*/
void can1_parameter_config(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  //CanTxMsg TxMessage;

  //* CAN register init */
  CAN_DeInit(CAN1); //将外设CAN的全部寄存器重设为缺省值
  CAN_StructInit(&CAN_InitStructure);//把CAN_InitStruct中的每一个参数按缺省值填入

  //* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;         //没有使能时间触发模式
  CAN_InitStructure.CAN_ABOM = ENABLE;          //使能自动离线管理
  CAN_InitStructure.CAN_AWUM = DISABLE;         //没有使能自动唤醒模式
  CAN_InitStructure.CAN_NART = DISABLE;         //没有使能非自动重传模式
  CAN_InitStructure.CAN_RFLM = DISABLE;         //没有使能接收FIFO锁定模式
  CAN_InitStructure.CAN_TXFP = DISABLE;         //没有使能发送FIFO优先级
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //CAN设置为正常模式
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;      //重新同步跳跃宽度1个时间单位
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;      //时间段1为3个时间单位
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;      //时间段2为2个时间单位
  CAN_InitStructure.CAN_Prescaler = 24;         //时间单位长度为24
  CAN_Init(CAN1,&CAN_InitStructure);          //波特率为：72M/2/24(1+3+2)=0.1 即250K

  //* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 1;                   //指定过滤器为1
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; //指定过滤器为标识符屏蔽位模式
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//过滤器位宽为32位
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;              //过滤器标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;               //过滤器标识符的低16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;          //过滤器屏蔽标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;           //过滤器屏蔽标识符的低16位值

  //_____|_高16位值|__低16位值__
  //0x F | FF      |F   F |FFF
  //保留 | 目的地址|源地址|保留
  //
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;// 设定了指向过滤器的FIFO为0
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;// 使能过滤器
  CAN_FilterInit(&CAN_FilterInitStructure);// 按上面的参数初始化过滤器

  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); //使能FIFO0消息挂号中断//CAN FIFO0 message pending interrupt enable
}
/**
*@function void can1_init(void)
*@brief    can1初始化时钟、io、参数和中断
*@param    void
*@return   无
*@date     2018/5/4
*/
void can1_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  can1_NVIC_config(); //CAN中断初始化
  can1_gpio_config();//CAN管脚初始化
  can1_parameter_config();//CAN初始化N模块

}

/*------------------------------- 以下是can2端口配置 -------------------------------*/
#ifdef  ENABLE_CAN2  // 如果使用can2 ，107存在can2103芯片不存在
/**
*@function void can2_NVIC_config(void)
*@brief
*@return
*@date     2018/5/4
*/
void can2_NVIC_config(void)//CAN RX0 中断优先级配置
{
  NVIC_InitTypeDef NVIC_InitStructure;//Configure the NVIC Preemption Priority Bits

  NVIC_InitStructure.NVIC_IRQChannel=CAN2_RX1_IRQn;//enabling interrupt
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
*@function void can2_gpio_config(void)
*@brief    can2接口gpio配置
*@return   无
*@date     2018/5/4
*/
void can2_gpio_config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         //PB6-CANTX2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽
  GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化IO

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;         //PB5-CANRX2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化IO
  GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//使能CAN2时钟
}

/**
*@function void can2_parameter_config(void)
*@brief    can2接口参数配置，包括时钟、过滤器等
*@return   无
*@date     2018/5/4
*/
void can2_parameter_config(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  //CanTxMsg TxMessage;

  //* CAN register init */
  CAN_DeInit(CAN2); //将外设CAN的全部寄存器重设为缺省值
  CAN_StructInit(&CAN_InitStructure);//把CAN_InitStruct中的每一个参数按缺省值填入

  //* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE;         //没有使能时间触发模式
  CAN_InitStructure.CAN_ABOM=ENABLE;          //使能自动离线管理
  CAN_InitStructure.CAN_AWUM=DISABLE;         //没有使能自动唤醒模式
  CAN_InitStructure.CAN_NART=DISABLE;         //没有使能非自动重传模式
  CAN_InitStructure.CAN_RFLM=DISABLE;         //没有使能接收FIFO锁定模式
  CAN_InitStructure.CAN_TXFP=DISABLE;         //没有使能发送FIFO优先级
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; //CAN设置为正常模式
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      //重新同步跳跃宽度1个时间单位
  CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      //时间段1为3个时间单位
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      //时间段2为2个时间单位
  CAN_InitStructure.CAN_Prescaler=24;         //时间单位长度为24
  CAN_Init(CAN2,&CAN_InitStructure);          //波特率为：72M/2/24(1+3+2)=0.1 即250K

  //* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=14;                  //指定过滤器为1
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //指定过滤器为标识符屏蔽位模式
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;//过滤器位宽为32位
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;              //过滤器标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;               //过滤器标识符的低16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;          //过滤器屏蔽标识符的高16位值
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;           //过滤器屏蔽标识符的低16位值
  //CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;        //过滤器屏蔽标识符的高16位值
  //CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;         //过滤器屏蔽标识符的低16位值
  //_____|_高16位值|__低16位值__
  //0x F | FF      |F   F |FFF
  //保留 | 目的地址|源地址|保留
  //
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO1; // 设定了指向过滤器的FIFO为1
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;        // 使能过滤器
  CAN_FilterInit(&CAN_FilterInitStructure);                   //  按上面的参数初始化过滤器
  CAN_ITConfig(CAN2,CAN_IT_FMP1, ENABLE);                     //使能FIFO0消息挂号中断//CAN FIFO1 message pending interrupt enable
}

/**
*@function void CAN2Init(void)
*@brief    can2初始化，时钟、中断、参数配置和gpio
*@param    void
*@return   无
*@date     2018/5/4
*/
void can2_init(void)
{
  can2_gpio_config();//CAN管脚初始化
  can2_parameter_config();//CA初始化N模块
  can2_NVIC_config(); //CAN中断初始化
}
#endif

/**
*@brief   can口发送函数
*@param     hcan：要发送的口 buf：要发送的数据 len：数据长度
*@param   addr：DCU地址 instr：发送指令
*@return    1：成功 0：失败
*/
uint8_t can_tx_data_package(CAN_TypeDef *hcan, uint8_t *buf, uint8_t len, uint32_t identifier,uint8_t frameMode)
{
  u16 i = 0;
  uint8_t mbox;
  CanTxMsg TxMessage;          // can报文数据

  TxMessage.StdId = identifier;      // 定义id
  TxMessage.RTR = frameMode;       // 数据帧or远程帧
  TxMessage.IDE = CAN_ID_STD;    // 标准帧
  TxMessage.DLC = len;           // 数据长度
                               //
  for (i=0;i<8;i++)            // 填充数据
    TxMessage.Data[i] = buf[i];

  mbox = CAN_Transmit(hcan,&TxMessage);    // 发送数据并获取邮箱号

  while((CAN_TransmitStatus(hcan, mbox)!=CAN_TxStatus_Ok)&&(i<0xFFF))i++; //等待发送结束

  if (i < 0xFFF)  // 返回值
    return 1;
  else
    return 0;
}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/







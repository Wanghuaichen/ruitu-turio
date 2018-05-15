/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         can.c
* @author       zhou
* @version      V1.0
* @date         2017-08-11
* @brief        canͨ�ź����ļ�
**************************************************************************************************
*/
#include "include.h"

//*------------ ������can1�˿����� -------------------------------*/
/**
*@function void can1_nvic_config(void)
*@brief    can�жϳ�ʼ������
*@return   ��
*@date     2018/5/4
*/
void can1_NVIC_config(void)//CAN RX0 �ж����ȼ�����
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
*@brief    can1��Ӧ�ܽ�����
*@return   ��
*@date     2018/5/4
*/
void can1_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//ʹ��PORTAʱ��
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1,DISABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    //��ʼ��IO

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��IO
}

/**
*@function void can1_parameter_config(void)
*@brief    can1�������ã�����ͨ�Ų����������ʼ���������
*@return   ��
*@date     2018/5/4
*/
void can1_parameter_config(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  //CanTxMsg TxMessage;

  //* CAN register init */
  CAN_DeInit(CAN1); //������CAN��ȫ���Ĵ�������Ϊȱʡֵ
  CAN_StructInit(&CAN_InitStructure);//��CAN_InitStruct�е�ÿһ��������ȱʡֵ����

  //* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;         //û��ʹ��ʱ�䴥��ģʽ
  CAN_InitStructure.CAN_ABOM = ENABLE;          //ʹ���Զ����߹���
  CAN_InitStructure.CAN_AWUM = DISABLE;         //û��ʹ���Զ�����ģʽ
  CAN_InitStructure.CAN_NART = DISABLE;         //û��ʹ�ܷ��Զ��ش�ģʽ
  CAN_InitStructure.CAN_RFLM = DISABLE;         //û��ʹ�ܽ���FIFO����ģʽ
  CAN_InitStructure.CAN_TXFP = DISABLE;         //û��ʹ�ܷ���FIFO���ȼ�
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //CAN����Ϊ����ģʽ
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;      //����ͬ����Ծ���1��ʱ�䵥λ
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;      //ʱ���1Ϊ3��ʱ�䵥λ
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;      //ʱ���2Ϊ2��ʱ�䵥λ
  CAN_InitStructure.CAN_Prescaler = 6;         //ʱ�䵥λ����Ϊ24
  CAN_Init(CAN1,&CAN_InitStructure);          //������Ϊ��72M/2/24(1+3+2)=0.1 ��250K

  //* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 1;                   //ָ��������Ϊ1
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; //ָ��������Ϊ��ʶ������λģʽ
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//������λ��Ϊ32λ
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;              //��������ʶ���ĸ�16λֵ
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;               //��������ʶ���ĵ�16λֵ
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;          //���������α�ʶ���ĸ�16λֵ
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;           //���������α�ʶ���ĵ�16λֵ

  //_____|_��16λֵ|__��16λֵ__
  //0x F | FF      |F   F |FFF
  //���� | Ŀ�ĵ�ַ|Դ��ַ|����
  //
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;// �趨��ָ���������FIFOΪ0
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;// ʹ�ܹ�����
  CAN_FilterInit(&CAN_FilterInitStructure);// ������Ĳ�����ʼ��������

  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); //ʹ��FIFO0��Ϣ�Һ��ж�//CAN FIFO0 message pending interrupt enable
}
/**
*@function void can1_init(void)
*@brief    can1��ʼ��ʱ�ӡ�io���������ж�
*@param    void
*@return   ��
*@date     2018/5/4
*/
void can1_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  can1_NVIC_config(); //CAN�жϳ�ʼ��
  can1_gpio_config();//CAN�ܽų�ʼ��
  can1_parameter_config();//CAN��ʼ��Nģ��

}

/*------------------------------- ������can2�˿����� -------------------------------*/
#ifdef  ENABLE_CAN2  // ���ʹ��can2 ��107����can2103оƬ������
/**
*@function void can2_NVIC_config(void)
*@brief
*@return
*@date     2018/5/4
*/
void can2_NVIC_config(void)//CAN RX0 �ж����ȼ�����
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
*@brief    can2�ӿ�gpio����
*@return   ��
*@date     2018/5/4
*/
void can2_gpio_config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         //PB6-CANTX2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��IO

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;         //PB5-CANRX2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��IO
  GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//ʹ��CAN2ʱ��
}

/**
*@function void can2_parameter_config(void)
*@brief    can2�ӿڲ������ã�����ʱ�ӡ���������
*@return   ��
*@date     2018/5/4
*/
void can2_parameter_config(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  //CanTxMsg TxMessage;

  //* CAN register init */
  CAN_DeInit(CAN2); //������CAN��ȫ���Ĵ�������Ϊȱʡֵ
  CAN_StructInit(&CAN_InitStructure);//��CAN_InitStruct�е�ÿһ��������ȱʡֵ����

  //* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE;         //û��ʹ��ʱ�䴥��ģʽ
  CAN_InitStructure.CAN_ABOM=ENABLE;          //ʹ���Զ����߹���
  CAN_InitStructure.CAN_AWUM=DISABLE;         //û��ʹ���Զ�����ģʽ
  CAN_InitStructure.CAN_NART=DISABLE;         //û��ʹ�ܷ��Զ��ش�ģʽ
  CAN_InitStructure.CAN_RFLM=DISABLE;         //û��ʹ�ܽ���FIFO����ģʽ
  CAN_InitStructure.CAN_TXFP=DISABLE;         //û��ʹ�ܷ���FIFO���ȼ�
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; //CAN����Ϊ����ģʽ
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      //����ͬ����Ծ���1��ʱ�䵥λ
  CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      //ʱ���1Ϊ3��ʱ�䵥λ
  CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      //ʱ���2Ϊ2��ʱ�䵥λ
  CAN_InitStructure.CAN_Prescaler=24;         //ʱ�䵥λ����Ϊ24
  CAN_Init(CAN2,&CAN_InitStructure);          //������Ϊ��72M/2/24(1+3+2)=0.1 ��250K

  //* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=14;                  //ָ��������Ϊ1
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; //ָ��������Ϊ��ʶ������λģʽ
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;//������λ��Ϊ32λ
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;              //��������ʶ���ĸ�16λֵ
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;               //��������ʶ���ĵ�16λֵ
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;          //���������α�ʶ���ĸ�16λֵ
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;           //���������α�ʶ���ĵ�16λֵ
  //CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;        //���������α�ʶ���ĸ�16λֵ
  //CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;         //���������α�ʶ���ĵ�16λֵ
  //_____|_��16λֵ|__��16λֵ__
  //0x F | FF      |F   F |FFF
  //���� | Ŀ�ĵ�ַ|Դ��ַ|����
  //
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO1; // �趨��ָ���������FIFOΪ1
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;        // ʹ�ܹ�����
  CAN_FilterInit(&CAN_FilterInitStructure);                   //  ������Ĳ�����ʼ��������
  CAN_ITConfig(CAN2,CAN_IT_FMP1, ENABLE);                     //ʹ��FIFO0��Ϣ�Һ��ж�//CAN FIFO1 message pending interrupt enable
}

/**
*@function void CAN2Init(void)
*@brief    can2��ʼ����ʱ�ӡ��жϡ��������ú�gpio
*@param    void
*@return   ��
*@date     2018/5/4
*/
void can2_init(void)
{
  can2_gpio_config();//CAN�ܽų�ʼ��
  can2_parameter_config();//CA��ʼ��Nģ��
  can2_NVIC_config(); //CAN�жϳ�ʼ��
}
#endif

/**
*@function uint8_t can_tx_data_package(CAN_TypeDef *hcan, uint8_t *buf, uint8_t len, uint32_t identifier, uint8_t frameMode)
*@brief    can����ָ��
*@param    hcan���õ�can��
*@param    buf�����͵�����
*@param    len���������ݳ���
*@param    identifier����ʶ��
*@param    frameMode��ָ���ʽ����֡��CAN_RTR_Data Զ��֡��CAN_RTR_Remote
*@return   1���ɹ� 2��ʧ��
*@date     2018/5/14
*/
uint8_t can_tx_data_package(CAN_TypeDef *hcan, uint8_t *buf, uint8_t len, uint32_t identifier,uint8_t frameMode)
{
  u16 i = 0;
  uint8_t mbox;
  CanTxMsg TxMessage;          // can��������

  TxMessage.StdId = identifier;      // ����id
  TxMessage.RTR = frameMode;       // ����֡orԶ��֡
  TxMessage.IDE = CAN_ID_STD;    // ��׼֡
  TxMessage.DLC = len;           // ���ݳ���
                               //
  for (i=0;i<8;i++)            // �������
    TxMessage.Data[i] = buf[i];

  mbox = CAN_Transmit(hcan,&TxMessage);    // �������ݲ���ȡ�����

  while((CAN_TransmitStatus(hcan, mbox)!=CAN_TxStatus_Ok)&&(i<0xFFF))i++; //�ȴ����ͽ���

  if (i < 0xFFF)  // ����ֵ
    return 1;
  else
    return 0;
}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/







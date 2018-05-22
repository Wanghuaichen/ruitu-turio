/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_18B20.c
* @author       zhou
* @version      V1.0
* @date         2018/5/22
* @brief        18B20���������ļ�
**************************************************************************************************
*/
#include "include.h"
void set_dq_output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;       //  ����GPIO��ʼ���ṹ��        */
    GPIO_InitStruct.GPIO_Pin = DS18B20_DQ_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(DS18B20_DQ_GPIO_Port, &GPIO_InitStruct);
}
void set_dq_input(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;       //  ����GPIO��ʼ���ṹ��        */

  GPIO_InitStruct.GPIO_Pin = DS18B20_DQ_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DS18B20_DQ_GPIO_Port, &GPIO_InitStruct);
}
//��ʼ������
unsigned char Init_DS18B20(void)
{

    unsigned char i;
    unsigned x=0;

    DQ_OUT;                //port output
    DQ_HIGH;       //PUSH up bus

    delay_us(3);     //3us short delay

    DQ_LOW;      //PULL down BUS

    for(i=0;i<5;i++)
    delay_us(500);     //500us delay


    DQ_HIGH;           //release bus with pullup resistance

    delay_us(100);         //100us delay

    DQ_IN;
    _NOP();

    if(DQ_RD)
      x=1;             //no device presence

    DQ_OUT;

    for(i=0;i<4;i++)
       delay_us(500);           //500us delay

    return(x);
}
//����18B20������
void DS18b20int(void)
{

  Init_DS18B20();
  WriteOneChar(0xCC); // ����������кŵĲ���
  WriteOneChar(0x4E);
  WriteOneChar(0x24);
  WriteOneChar(0x12);
  WriteOneChar(0x5f);  //�趨�¶ȴ���������Ϊ11λ��
}
//��һ���ֽ�
unsigned char ReadOneChar(void)
{
  unsigned char i=0;
  unsigned char dat =0X00;

  DQ_OUT;              //port out

  for (i=8;i>0;i--)
  {
    dat>>=1;               //data right shift
//    DQ_HIGH;             //PUSH UP BUS
//    delay_us(3);           //3us delay
    DQ_LOW;              //PULL down BUS
    delay_us(2);        //2us delay
    DQ_HIGH;      //release bus
    delay_us(7);        //7us delay

    DQ_IN;
    _NOP();

    if(DQ_RD)     //master sample bus
      dat|=(1<<7);
    delay_us(40);//(60);        //60us delay,between two writesolts
    DQ_OUT;
    DQ_HIGH;             //PUSH UP BUS
    delay_us(10);           //3us delay
  }
  return(dat);
}


//дһ���ֽ�
void WriteOneChar(unsigned char dat)
{
  unsigned char i=0;

  DQ_OUT;             //port out
  for (i=8; i>0; i--)
  {
//          DQ_HIGH;          //PUSH UP BUS
//    delay_us(3);      //3us delay
    DQ_LOW;
    delay_us(6);//(3);      //3us delay

    if(dat&0x01)      //data least bit-> 1
       DQ_HIGH;     //PUSH UP BUS
    else
       DQ_LOW;      //PULL down BUS

    delay_us(40);//(140);       //140us delay
    dat>>=1;          //data right shift
    DQ_HIGH;
    delay_us(10);//(3);       //3us delay,between two readsolts
   }
}


//��ȡ�¶�
//��ȡ�¶�
void ReadTemperature(void)
{
  unsigned char a=0;
  unsigned char b=0;




  Init_DS18B20();
  WriteOneChar(0xCC); // ����������кŵĲ���
  WriteOneChar(0x44); // �����¶�ת��
  delay_ms(420);

  Init_DS18B20();
  WriteOneChar(0xCC); //����������кŵĲ���
  WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
  a=ReadOneChar(); //�¶ȵ�λ
  b=ReadOneChar();   //�¶ȸ�λ
   if((b&0xf0)!=0x0f)  //�ж��Ƿ������ȡ��������ȫ������0
   {
     Temperature[0]=(((b&0x07)<<4)|((a&0xf0)>>4)); //�¶�����λ
    Temperature[1] =(((a&0x0e)*10)); //�¶�С��λ��С����ڶ�λ��1��ʾ����.0��ʾ��
   }
    else
    {
         Temperature[0]=0;
         Temperature[1]=0;
    }
}

//�˿������߳�ʼ��Ϊ�����
void ds18b20_port_init(void)
{
   DQ_HIGH;
   DQ_OUT;
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





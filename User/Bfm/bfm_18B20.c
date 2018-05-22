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
void set_DQ_OUTPUTput(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;       //  ����GPIO��ʼ���ṹ��

  GPIO_InitStruct.GPIO_Pin = DS18B20_DQ_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(DS18B20_DQ_GPIO_Port, &GPIO_InitStruct);
}
void set_DQ_INPUTput(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;       //  ����GPIO��ʼ���ṹ��        */

  GPIO_InitStruct.GPIO_Pin = DS18B20_DQ_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DS18B20_DQ_GPIO_Port, &GPIO_InitStruct);
}
uint8_t get_pin_input_data(void)
{
  if (GPIO_ReadInputDataBit(DS18B20_DQ_GPIO_Port, DS18B20_DQ_Pin) != Bit_RESET)
    return 1;
  else
    return 0;
}
//��ʼ������
unsigned char Init_DS18B20(void)
{

    unsigned char i;
    unsigned x=0;

    DQ_OUTPUT;       //port output
    DQ_OUT_HIGH;     //PUSH up bus
    delay_us(3);     //3us short delay
    DQ_OUT_LOW;      //PULL down BUS
    delay_us(500);     //500us delay
    DQ_OUT_HIGH;           //release bus with pullup resistance
    delay_us(100);         //100us delay
    DQ_INPUT;
    if(DQ_READ_DATA)
      x = 1;             //no device presence
    DQ_OUTPUT;

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
  DQ_OUTPUT;              //port out

  for (i=8;i>0;i--)
  {
    dat>>=1;               //data right shift
    DQ_OUT_LOW;              //PULL down BUS
    delay_us(2);        //2us delay
    DQ_OUT_HIGH;      //release bus
    delay_us(7);        //7us delay
    DQ_INPUT;
    delay_us(40);

    if(DQ_READ_DATA)     //master sample bus
      dat|=(1<<7);
    delay_us(1);//(60);        //60us delay,between two writesolts
    DQ_OUTPUT;
    DQ_OUT_HIGH;             //PUSH UP BUS
    delay_us(3);           //3us delay
  }
  return(dat);
}


//дһ���ֽ�
void WriteOneChar(unsigned char dat)
{
  unsigned char i=0;

  DQ_OUTPUT;             //port out
  for (i=8; i>0; i--)
  {
    DQ_OUT_LOW;
    delay_us(6);//(3);      //3us delay
    if(dat&0x01)            //data least bit-> 1
       DQ_OUT_HIGH;         //PUSH UP BUS
    else
       DQ_OUT_LOW;          //PULL down BUS
    delay_us(70);//(140);   //140us delay
    dat>>=1;                //data right shift
    DQ_OUT_HIGH;
    delay_us(3);//(3);      //3us delay,between two readsolts
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
  }
  else
  {
    Temperature[0]=0;
  }
}

//�˿������߳�ʼ��Ϊ�����
void ds18b20_port_init(void)
{
   DQ_OUT_HIGH;
   DQ_OUTPUT;
}

void task_read_18b20_init(void)
{

}
void task_read_18b20(void)
{
  uint8_t tempH,tempL;
  uint8_t bar = TASK_BAR_CMD;
  if (_TaskRead18B20.progressBar == bar++)
  {
    Init_DS18B20();
    WriteOneChar(0xCC); // ����������кŵĲ���
    WriteOneChar(0x44); // �����¶�ת��
    _TaskRead18B20.interval = 500;
    _TaskRead18B20.state    = TASK_STATE_DELAY;
    _TaskRead18B20.progressBar++;
  }
  else if (_TaskRead18B20.progressBar == bar++)
  {
    Init_DS18B20();
    WriteOneChar(0xCC); //����������кŵĲ���
    WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
    tempL = ReadOneChar(); //�¶ȵ�λ
    tempH = ReadOneChar();   //�¶ȸ�λ
    if((tempH&0xf0)!=0x0f)  //�ж��Ƿ������ȡ��������ȫ������0
      sRobotStatus_.CurrentTemp = (((tempH & 0x07) << 4)|((tempL & 0xf0) >> 4)); //�¶�����λ
    _TaskRead18B20.interval = 5000;
    _TaskRead18B20.state    = TASK_STATE_DELAY;
    _TaskRead18B20.progressBar++;
  }
}
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





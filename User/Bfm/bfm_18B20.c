/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_18B20.c
* @author       zhou
* @version      V1.0
* @date         2018/5/22
* @brief        18B20操作程序文件
**************************************************************************************************
*/
#include "include.h"
void set_dq_output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;       //  定义GPIO初始化结构体        */
    GPIO_InitStruct.GPIO_Pin = DS18B20_DQ_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(DS18B20_DQ_GPIO_Port, &GPIO_InitStruct);
}
void set_dq_input(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;       //  定义GPIO初始化结构体        */

  GPIO_InitStruct.GPIO_Pin = DS18B20_DQ_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DS18B20_DQ_GPIO_Port, &GPIO_InitStruct);
}
//初始化函数
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
//配置18B20参数。
void DS18b20int(void)
{

  Init_DS18B20();
  WriteOneChar(0xCC); // 跳过读序号列号的操作
  WriteOneChar(0x4E);
  WriteOneChar(0x24);
  WriteOneChar(0x12);
  WriteOneChar(0x5f);  //设定温度传感器精度为11位、
}
//读一个字节
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


//写一个字节
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


//读取温度
//读取温度
void ReadTemperature(void)
{
  unsigned char a=0;
  unsigned char b=0;




  Init_DS18B20();
  WriteOneChar(0xCC); // 跳过读序号列号的操作
  WriteOneChar(0x44); // 启动温度转换
  delay_ms(420);

  Init_DS18B20();
  WriteOneChar(0xCC); //跳过读序号列号的操作
  WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
  a=ReadOneChar(); //温度低位
  b=ReadOneChar();   //温度高位
   if((b&0xf0)!=0x0f)  //判断是否低于零度。低于零度全部返回0
   {
     Temperature[0]=(((b&0x07)<<4)|((a&0xf0)>>4)); //温度整数位
    Temperature[1] =(((a&0x0e)*10)); //温度小数位，小数点第二位置1表示正负.0表示正
   }
    else
    {
         Temperature[0]=0;
         Temperature[1]=0;
    }
}

//端口数据线初始化为输出高
void ds18b20_port_init(void)
{
   DQ_HIGH;
   DQ_OUT;
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





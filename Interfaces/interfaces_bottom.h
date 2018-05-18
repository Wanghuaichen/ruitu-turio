/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         interfaces_bottom.h
* @author       zhou
* @version      V1.0
* @date         2018/5/14
* @brief        底层调用接口头文件
**************************************************************************************************
*/
#ifndef _INTERFACES_BOTTON_H_
#define _INTERFACES_BOTTON_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
#define   FAN1          0
#define   FAN2          1
// LED状态
#define   LED_ON        2
#define   LED_OFF       0
#define   LED_BLINKING  1

#define   WHELL_CICRUMFERENCE               // 轮子周长
#define   DIV_FREQ                      1   // 分频系数
#define   ENCODER_NUMBER               1024 // 编码数
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/



//函数接口需求
//版本：V0.1
//最后修改时间：2018年5月9日
//--------------------------------------------------------------------------------------------------------------------------------------------
//命名规则
//（1）和上位机以及IC-3173视觉控制器的命令和数据都是用Send和Receive打头
// (2) 和传感器以及下位机直连的设备交互的都是用Set/set或者Get打头

//  // -------------------------------485----------
//  void GetBatteryInfo(void);//读取电池数据，返回 float电压，float电流，以及电量
//
/*---------------------------------GPIO/EXTI-----------------------*/
//设备控制-开启或者关闭激光雷达等等
void SetFan(uint8_t fan,uint8_t state); //打开或关闭 fan：fan1或者fan2 state：ENABLE/DISABLE
void SetRadar(uint8_t state);    //打开雷达 or DISABLE默认只有一个雷达
void SetRoute(uint8_t state);    //打路由器 or DISABL
void SetIMU(uint8_t state);      //打开IMU or DISABLE

//  //设置LED灯状态，本次只有三个LED灯
//  void SetTopLed(choice);//常亮on-2、闪烁 blinking-1、关闭off-0 提前define
//  void SetMidLed(choice);//常亮2、闪烁1、关闭0
//  void SetRgbLed(color,choice);//常亮2（选择R/G/B?）、闪烁1、关闭0  貌似要两个IO去控
/*------------------- 传感器信号及控制 -------------------------------*/
uint8_t GetLeftObstacleSensor(void);     // 1为有障碍 ，0为无障碍
uint8_t GetRightObstacleSensor(void);    // 1为有障碍 ， 0为无障碍
void SetLeftObstacleLed(uint8_t state);  // LED_ON/LED_OFF/LED_BLINKING
void SetRightObstacleLed(uint8_t state); // LED_ON/LED_OFF/LED_BLINKING
uint8_t GetIRLoactionSensor(void);    // 1为有障碍 ， 0为无障碍
                                         //
//获取编码器的状态
extern double_t encoderPosition_;
extern int32_t encoderUpdata;
//
//  int32_t GetEncoderRelativePosition(void) ;//编码器区间位置
//  int32_t GetEncoderAbsolutePosition(void) ;//编码器绝对位置
//  void ResetEncoderRelativePosition(void) ;//编码器区间相对位置 清零
//  void ResetEncoderAbsolutePosition(void) ;//编码器绝对位置 清零
//
//  //获取数字量传感器的状态------------------------------------------------------------------------------------------------------------------------------------
//  u8 GetSickSensorState(void);//光电开关的值--注意：光电开关的判断方法应该用输入捕获？中断？光电有效时候编码器的相对区间位置清零，光电的数量加减1
//  u16 GetSickNum(void); //获取光电的计数值
//  void ResetSickNum(void);
//  u8 GetBackFrontSensorState(void);//获取前后避障传感器的值，
//  float GetBoardTemperature(void);//第一个PT100的温度 ,这个PT100安装在电路板上
//  float GetICTemperature(void);//第二个PT100的温度，这个PT100安装在IC-3173上
//
//
//
//  //发送回零完成信号给IC3173
//  void SendHomingCompletingSignal_to_IC3173(void);//1代表到达原点，对应的GPIO输出高电平，0代表未达到原点，对应的GPIO输出低电平,主要用在回零过程中。
//
//  //获取原点开关信号---模式开关为homing以及光电开关为高电平且编码器脉冲数大于阈值（EncThreshod个脉冲） #define EncThreshod 300 ，这三种情况都成立的时候，在开关引脚输出高电平
//  //应该在中断服务程序里面处理
//  //在终端里面实现以下函数
//  void SetLimitSwitch(enbale);//DISABLE连接到电机驱动器的LimitSwitch管脚输出高低电平
//
//
//
//
//
/*---------------------CAN--RS232--Motor--------------------------------------------*/
void SetCAN(uint8_t state) ; //NMT ENABLE/DISABLE
void SetMotor(uint8_t state);//使能电机or DISABLE
uint8_t GetMotorState(uint8_t *buf,uint8_t len); // 获取电机节点状态

//获取电机运动参数
 typedef struct motordata{
  int32_t position;  // 位置
  int32_t velocity;    // 速度
 }MotorPosVel;
uint8_t SetMotorTargetPosVel(MotorPosVel *motorParam);
//  void SetMotorADcceleration(acceleration,deceleration);
//
//

//   //最好positon和velocity是全局变量
//  MotorPosVel GetMotorPosVel(void);// 返回一个结构体，
//  void ResetMotorPos(void);
//  float GetMotorCurrent(void);//获取电机电流，
//







//
//
//  //--------------------------------TCP/IP-----JSON格式----------------------
//  //接收上位机命令
//  ReceiveCommand_from_Server();//返回一个结构体， json数据格式如下
//  {
//  "RobotStatus": {
//    "RunStatus": "Auto",    // Stop, Auto, Charging, Jog
//  "CurrentTime": "2017-10-13 17:27:30",
//  "CurrentPosition":2010,   // I32
//  "CurrentSpeed": 390,      // I16
//  "RunningCount": 10,     // U16
//  "CurrentTemp": 47,            // I8
//  "CurrentVoltage": 22.38     // Float(控制系统电池的工作电压)
//  "CurrentAmp": 400.2         // Float（控制系统电池的工作电流）
//  "CurrentDir": true         // true-正，false-负
//  "ControlSystemEnergy": 50%   //float,显示百分数
//  "DynamicSystemEnergy": 60%   //float,显示百分数
//  }
//  }
//
//
//  //控制反馈只在"完成配置"和"手自动"操作时反馈
//  {
//  "Response":{
//  "Command": "Jog",   // "Auto", "Set", "Stop"
//   "Result": "OK"：   // "Error:"
//  }
//  }
//
//
//
//
//  //发送数据给上位机
//  SendStatus_to_Server();//返回一个结构体，
//
//
//  //json格式如下
//  {
//  "RobotCommand": {
//  "Command": "Jog",   // "Auto", "Set", "Stop", "Forward", "Backward","Jog","Dot"
//  "Speed": 400,       // I16
//  "RunCount":2,       // U16
//  "StartPosition": 0,   // I32
//  "EndPosition": 10000 ,  // I32
//  "TargetPosition":12000,  //I32
//  "WorkMode": "RealTime" ,      // "Regular", "Daily"
//  "Step": 20          // I16
//  }
//  }


void test_hardware(void);
#endif












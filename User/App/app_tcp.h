/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.h
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        基于w5500的tcp应用程序头文件
**************************************************************************************************
*/
#ifndef _APP_TCP_H_
#define _APP_TCP_H_
#include "include.h"
/*--------------- 宏定义 --------------*/

/*--------------- 变量定义 --------------*/
typedef enum
{
  Robot_CMD_Auto = 0, // 自动
  Robot_CMD_HomingStart, // 回零开始
  Robot_CMD_Start,    // 开始
  Robot_CMD_Homing,   // 回零
  Robot_CMD_Set,      // 设置参数
  Robot_CMD_Stop,     // 停止
  Robot_CMD_Forward,  // 向前
  Robot_CMD_Backward, // 向后
  Robot_CMD_Jog,      // 手动：手动模式下可使用前进和后退指令，运动固定步长
  Robot_CMD_Dot,      // 引导模式
  Robot_CMD_Charging, // 充电模式
  Robot_CMD_Error     // 错误
}E_MOTOR_STATE;
typedef struct
{
  E_MOTOR_STATE runStatus;           // 运行状态
  char          currentTime[30];     // 当前时间
  char          currentPosition[11]; // 当前位置
  char          CurrentSpeed[11];    // 当前速度
  uint16_t      RunningCount;        // 当前巡检次数
  uint8_t       CurrentTemp;         // 当前温度
  uint16_t      CurrentVoltage;      // 当前电池电压
  uint16_t      CurrentAmp;          // 当前电池电流
  uint8_t       CurrentDir;          // 当前方向 1：正 0 ：负
  uint16_t      ControlSystemEnergy; // 当前电量百分比
  uint16_t      DynamicSystemEnergy; // 当前电量百分比
}S_ROBOT_STATUS;

typedef enum
{
  Robot_Work_RealTime = 0,
  Robot_Work_Regular,
  Robot_Work_Daily,
  Robot_Work_Error
}E_WORK_MODE;
typedef struct
{
  E_MOTOR_STATE eComand; // 命令
  int16_t      speed;   // 速度
  uint16_t     runCount; // 运行次数
  int32_t      startPosition; // 开始位置
  int32_t      endPosition; // 结束位置
  int32_t      targetPosition; // 目标位置
  E_WORK_MODE  eWorkMode[10];    // 工作模式 realtime
  int16_t      step;           // 手动运动步长
}S_ROBOT_COMMAND;
//typedef struct ROBOcommand
//{
//    char         Command[10];
//    unsigned int Speed;
//    unsigned int RunCount;
//    unsigned int StartPosition;
//    unsigned int EndPosition;
//    unsigned int TargetPosition;
//    char         WorkMode[10];
//    unsigned int Step;
//}ROBOCmd_TypeDef;

typedef struct
{
  E_MOTOR_STATE eComand;             // 命令
  char          speed[6];            // 速度
  uint16_t      runCount;            // 运行次数
  char          startPosition[11];   // 开始位置
  char          endPosition[11];     // 结束位置
  char          targetPosition[11];  // 目标位置
  char          homeOffset[11];      // 回零后偏移距离
  char          homeFastSpeed[11];    // 回零最快速度
  char          homeSlowSpeed[11];    // 回零最慢速度
  char          PositionAccelerated[11]; // 位置模式加速度
  char          PositionDecelerated[11]; // 位置模式减速度
  E_WORK_MODE   eWorkMode;           // 工作模式 realtime
  uint16_t      step;                // 手动运动步长
}S_MOTOR_PARAM;
/*--------------- 函数定义 --------------*/
void Command_tcp_client(void);
void Status_tcp_client(void);
void task_tcp_init(void);
void task_tcp(void);
void robot_tx_data_conversion(S_ROBOT_STATUS *sStatus);
void set_robot_command(E_MOTOR_STATE eRobotStatus ,char *buf);
E_MOTOR_STATE get_robot_command(char *buf);
E_WORK_MODE get_robot_run_mode(char *buf);
uint8_t robot_rx_date_coversion(ROBOCmd_TypeDef *sRobotCmd);
#endif


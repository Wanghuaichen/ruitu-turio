/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : Parameter.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : 所有参数都将定义在这里
*******************************************************************************/
/*-------------------------------------------------------------
关于变量的几点说明：
1. 所有全局变量都定义在此头文件中;
2. 局部变量使用驼峰法，首单词首字母小写，其它单词首字母大写，如：myVariableDefinition;
3. 全局变量定义与局部变量相同，需加_尾缀，如：myVariableDefinition_;
---4. 程序名定义使用首单词首字母大写的驼峰法，如：MyVariableDefinition;
4. 程序名定义使用下画线隔开的小写字母命名，如my_variable_definition;
5. 结构体、联合体等名称使用s、u等做为前缀，其它全部大写，全局变量定义加前缀s或u及后缀_，
    如sMY_VARIABLE_DEFINITION sMyVariableDefinition_;局部变量定义如局部变量。
6. 任务变量特殊定义，使用_Task为前缀，如_TaskMyVariableDefinition;
7. 任务相关函数使用task为前缀，如task_my_variable_definition;

-----------------------------------------------------------------*/
#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "include.h"

/*--------任务命令宏定义----------------*/
// 通信类型宏定义，根据此定义判断不同接口接收的数据
#define COM_TYPE_RS485             1 // 使用485接口通信时通信类型
#define COM_TYPE_RS232             2 // 使用232接口通信时通信类型
#define COM_TYPE_CAN               3 // 使用can接口通信时通信类型
#define COM_TYPE_ETHERNET          4 // 使用网络接口通信时通信类型


// 串口通信任务指令定义 -----无意义
#define CMD_TASK_UART_RX           0xE1     // 串口接收任务指令-包括485和232
#define CMD_TASK_UART_TX           0xE2     // 串口发送任务指令-包括485和232
#define CMD_TASK_CAN_RX            0xEA     // can口接收任务指令
#define CMD_TASK_CAN_TX            0xEB     // can口发送任务指令
#define CMD_TASK_ETHERNET_RX       0xEC     // 网口接收任务指令
#define CMD_TASK_ETHERNET_TX       0xED     // 网口发送任务指令

// 配置任务指令定义
#define CMD_TASK_CONFIG            0xA0
///------上传SN---------------------//
#define CMD_CONFIG_GET_VER                0xA1 // 获取版本
#define CMD_CONFIG_GET_SN                 0xA8 // 获取SN
#define CMD_CONFIG_GET_REMOTE             0xAB // 获取一次上传遥控器指令的机会
//-------重启----------------------//
#define CMD_CONFIG_RESET_BOOT             0xA2
//--------恢复出厂设置-------------------
#define CMD_CONFIG_FACTORY_SET            0xA9


#endif

/*-*************** 全局变量定义 *********************/
#ifdef   GLOBAL_VARIABLE
#define  EXT_GLOBAL
#else
#define  EXT_GLOBAL extern
#endif


/*-***********系统相关变量******************************/
EXT_GLOBAL  volatile uint32_t     sysTick_;    // 系统时钟计数
EXT_GLOBAL  volatile uint32_t     delayTick_;  // 延时时钟
EXT_GLOBAL  uint32_t              runTick_;    // 运行时钟计数
EXT_GLOBAL  uint8_t               cmdTick_;    // 指令计数


/*-*********任务定义***********************************/
#define TASK_MAX        28  // 可运行任务个数定义
EXT_GLOBAL sTASK*       _TaskFlow[TASK_MAX + 1]; // 定义任务数
EXT_GLOBAL TASK         taskID_;                 // 定义任务编号，暂时无用

/*-*********空闲任务定义*******************************/
EXT_GLOBAL sTASK        _TaskIdle;   // 定义空闲任务

/*-****************************串口任务定义*******************************/
EXT_GLOBAL sTASK              _TaskUartRx;
EXT_GLOBAL sTASK              _TaskUartTx;
// 串口接收数据分类宏定义
#define UART1_RX_DATA         0x01
#define UART2_RX_DATA         0x02
#define UART3_RX_DATA         0x04
#define UART4_RX_DATA         0x08
#define UART5_RX_DATA         0x10
//--------------------串口1定义-------------------------//
// 数据定义
#define UART1_BUF_LEN              500
#define UART1_DATA_LEN             15
// 串口1接收定义
EXT_GLOBAL uint8_t             uart1RxBuf_[UART1_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart1RxCircleBuf_;
// 串口1发送定义
EXT_GLOBAL uint8_t             uart1TxBuf_[UART1_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart1TxCircleBuf_;

//--------------------串口5定义-------------------------//
// 数据定义
#define UART3_BUF_LEN              500
#define UART3_DATA_LEN             15
// 串口3接收定义
EXT_GLOBAL uint8_t             uart3RxBuf_[UART3_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart3RxCircleBuf_;
// 串口3发送定义
EXT_GLOBAL uint8_t             uart3TxBuf_[UART3_BUF_LEN];
EXT_GLOBAL sCIRCLE_BUF         sUart3TxCircleBuf_;

/*-****************************配置任务定义*******************************/
EXT_GLOBAL sTASK            _TaskConfig;
EXT_GLOBAL sCONFIG_INSTRUCT sParamConfig_;
/*-***************************can任务*************************************/
EXT_GLOBAL sTASK            _TaskCanRx;
EXT_GLOBAL sCAN_BUF         sCan1Buf_;
EXT_GLOBAL sCAN_BUF         sCan2Buf_;

/*--------------------------------网络任务定义------------------------------*/
EXT_GLOBAL S_W5500_CONFIG   sDefaultNetConfig_;

/*---------------------------------编码器任务--------------------------------*/
EXT_GLOBAL uint16_t        encoderValue_[100];
EXT_GLOBAL uint8_t         encoderNum_;
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





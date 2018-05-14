/******************** (C) COPYRIGHT PEOPLE ******************************
* File Name          : task.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.12.2
* Description        : 任务文件头文件
*******************************************************************************/
#ifndef  _TASK_H_
#define  _TASK_H_

#include "include.h"
/*******************宏定义*************************/

//*************任务相关定义***********************/
//#define TASK_MAX                28
//#define NULL                   0
#define TASK_BAR_CMD             0
#define TASK_INFO_NORMAL         1
#define TASK_INFO_ERROR          0
// 任务状态
#define   TASK_STATE_RUN     0x01
#define   TASK_STATE_DELAY   0x02
#define   TASK_STATE_SLEEP   0x03
// 空闲任务定义
#define CMD_TASK_IDLE         0xE0     // 空闲任务指令-无意义
// 任务结构体
typedef uint8_t  TASK;
typedef struct
{
    volatile TASK        state;               // 任务状态
    TASK                 progressBar;         // 进度条
    TASK                 command;             // 指令
    TASK                 port;           // 接口
    volatile TASK        info;                // 信息
    TASK                 rxLen;               // 接收数据长度
    TASK                 txLen;               // 发送数据长度
    uint32_t             interval;            // 间隙
    volatile uint32_t    timeOut;             // 超时
    void                 *rxBuf;              // 接收数据储存区，初始化时赋值
    void                 *txBuf;              // 发送
    void                 (*init)(void);       // 初始化函数
    void                 (*alteration)(void); // 变更函数
    void                 (*fun)(void);        // 任务函数
}sTASK;

/**********************函数定义**********************/
void task_init(void);
void task_add(uint8_t taskId,sTASK* taskname,void (*init)(void));
void task_cmd(uint8_t *buf, uint8_t len,uint8_t port);
void task_run(void);
void task_idle_init(void);
void task_idle(void);

#endif



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





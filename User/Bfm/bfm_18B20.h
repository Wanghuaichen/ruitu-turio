/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_18B20.h
* @author       zhou
* @version      V1.0
* @date         2018/5/22
* @brief        18B20操控程序头文件
**************************************************************************************************
*/
#ifndef _bfm_18B20.h_H_
#define _bfm_18B20.h_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
#define DQ_OUTPUT     set_dq_output()
#define DQ_INPUT      set_dq_input()
#define DQ_OUT_HIGH   GPIO_SetBits(DS18B20_DQ_GPIO_Port, DS18B20_DQ_Pin);
#define DQ_OUT_LOW    GPIO_ResetBits(DS18B20_DQ_GPIO_Port, DS18B20_DQ_Pin);
#define DQ_READ_DATA  get_pin_input_data();
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/
void task_read_18b20(void);
void task_read_18b20_init(void);
#endif


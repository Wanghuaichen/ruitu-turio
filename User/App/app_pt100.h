/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_pt100.h
* @author       zhou
* @version      V1.0
* @date         2018/5/11
* @brief        pt100控制程序头文件
**************************************************************************************************
*/
#ifndef _APP_PT100_H_
#define _APP_PT100_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
#define REFERENCE_RESISTANCE            200   // 参考电阻值
#define REFERENCE_GAIN                  (REFERENCE_RESISTANCE * 10000) // 参考电阻值
#define DIVIDER_RESISTANCE              1000 // 分压电阻
#define REFERENCE_AD_VALUE              2048  // 参考电压对应的AD值
#define A_ACCURACY                      3908 // 0.390802
#define GAIN                            10
#define AD_GANI                         (4096*GAIN)
/**
    采样电压计算：Vsamp = （adc_value/4096）*3.3
    计算桥臂压差：Vdif = (Rx/(divider_resistance + Rx))
                       - (refernce_resistance/(divider_resistance +refernce_resistance))
    放大电压:因为有基准电压为3.3/2,放大电压 Vamp = Vsamp - 3.3/2
    增益:A = 80
    Vamp = A * Vdif
    联立得到:Rx = (2048-adc_value）*computer_factor+refernce_resistance
    computer_factor = （（3.3/4096）/ 80）* divider_resistance
    */
#define COMPUTER_FACTOR                     1007  // 计算因子0.1007080078125 增益10000倍，不用进行float计算
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/

uint16_t computer_tempature(uint16_t adcValue);
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





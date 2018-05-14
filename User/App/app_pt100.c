/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_pt100.c
* @author       zhou
* @version      V1.0
* @date         2018/5/11
* @brief        pt100控制程序文件
**************************************************************************************************
*/
#include "include.h"
/**
*@function uint16_t computer_tempature(uint16_t adcValue)
*@brief    温度值计算
*@param    adcValue
*@return
*@date     2018/5/11
*/
uint16_t computer_tempature(uint16_t adcValue)
{
//   uint32_t sampValue,computerValue = 0;
//   uint16_t rxValue;
//   if (adcValue > REFERENCE_AD_VALUE)
//     sampValue = adcValue - REFERENCE_AD_VALUE;
//   else
//     sampValue = REFERENCE_AD_VALUE - adcValue;
//  // computerValue = (sampValue * COMPUTER_FACTOR) /3851;
//   //rxValue = (uint16_t)(computerValue/100 +0.5);
//   rxValue = (uint16_t)(((sampValue * COMPUTER_FACTOR) /3851) + 0.5);
//   return rxValue;
  uint32_t sampValue,computerValue = 0;
  uint32_t medianValue[5];
  uint32_t rxValue;
  uint16_t tmepValue;
  if (adcValue > REFERENCE_AD_VALUE)
    sampValue = adcValue - REFERENCE_AD_VALUE;
  else
    sampValue = REFERENCE_AD_VALUE - adcValue;
  sampValue = adcValue;
  // Rx = (R2*R3 + R3* (R1+R2)VB/Vin )/ (R1- (R1+R2)*VB/ Vin)
  // medianValue1 = (R2*R3 + R3* (R1+R2)VB/Vin ) *100
  medianValue[0] = (REFERENCE_RESISTANCE * DIVIDER_RESISTANCE);
  medianValue[1] = (DIVIDER_RESISTANCE * (DIVIDER_RESISTANCE + REFERENCE_RESISTANCE));
  medianValue[4] = ((medianValue[1]/AD_GANI) * sampValue) ;
  // medianValue2 = (R1- (R1+R2)*VB/ Vin)*100
  medianValue[2] = (DIVIDER_RESISTANCE * 1000);
  medianValue[5] = (((DIVIDER_RESISTANCE + REFERENCE_RESISTANCE) * sampValue * 1000)/AD_GANI);
  medianValue[2] += medianValue[5];
  medianValue[3] = (medianValue[0] - medianValue[4]) * 1000;
  rxValue = (medianValue[3]/medianValue[2])*10000;
  tmepValue = ((rxValue - 1000000)/3851)*10;
  return tmepValue;
}

//uint16_t computer_rx(uint16_t adcValue)
//{
//  uint32_t sampValue,computerValue = 0;
//  uint32_t medianValue1,medianValue2;
//  uint32_t rxValue;
//  uint16_t tmepValue;
//  if (adcValue > REFERENCE_AD_VALUE)
//    sampValue = adcValue - REFERENCE_AD_VALUE;
//  else
//    sampValue = REFERENCE_AD_VALUE - adcValue;

//  // Rx = (R2*R3 + R3* (R1+R2)VB/Vin )/ (R1- (R1+R2)*VB/ Vin)
//  // medianValue1 = (R2*R3 + R3* (R1+R2)VB/Vin ) *100
//  medianValue1 = ((REFERENCE_RESISTANCE * DIVIDER_RESISTANCE) +
//    (DIVIDER_RESISTANCE* (DIVIDER_RESISTANCE+ REFERENCE_RESISTANCE)/AD_GANI))*1000;
//  // medianValue2 = (R1- (R1+R2)*VB/ Vin)*100
//  medianValue2 = ( DIVIDER_RESISTANCE - ((DIVIDER_RESISTANCE+ REFERENCE_RESISTANCE)/AD_GANI))*1000;
//  rxValue = (medianValue1/medianValue2)*1000;
//  tmepValue = (rxValue - 100000000)/358100;

//}
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





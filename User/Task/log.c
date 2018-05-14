/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : log.c
* Author             : ME
* Version            : V1.0
* Date               : 2017.7.18
* Description        : log件
*******************************************************************************/

#include "include.h"
/**
*@brief	 打印函数初始化
*@param	 无
*@return 无
*/
void PrintfInit(void)
{
	PrintfChannelNet   = PRINTF_CHANNEL_DISABLE;  // 不通过网络打印
	PrintfChannelRS485 = PRINTF_CHANNEL_DISABLE;  // 不通过485打印
	PrintfChannelUsart = PRINTF_CHANNEL_ENABLE;   // 通过串口打印
	
	PrintfMessageTest = PRINTF_MESSAGE_DISABLE;  // 打印错误信息禁止 ；其实没有用
	PrintfMessageLog   = PRINTF_MESSAGE_ENABLE;   // 允许打印log信息
}
/**
*@brief	  选择打印的通道，需要外部设置，根据硬件资源不同修改，
					在参数里定义全局变量选择，默认都不打印
					此版本限制打印长度为
*@param	  *format：任意格式数据
*@return  无
*/
void PrintfChannel(uint8_t length)
{

	if (PrintfChannelNet == PRINTF_CHANNEL_ENABLE)   // 若网口打印允许
		;//tcp_write(0,printBuf,length);                       // 打印内容
	if (PrintfChannelRS485 == PRINTF_CHANNEL_ENABLE) // 若485口打印
	{
//		 SetTxDMA(&sUart2TxDMA_,printBuf,length);      // 打印内容写入缓存
//		_TaskUart2Tx.state = TASK_STATE_RUN;           // 启动发送数据任务
	}
	if (PrintfChannelUsart == PRINTF_CHANNEL_ENABLE) // 若串口打印
	{
//		SetTxDMA(&sUart5TxDMA_,printBuf,length);       // 打印内容写入缓存   
//		_TaskUart5Tx.state = TASK_STATE_RUN;           // 启协发送数据任务
	}
  
}

/**
*@brief	  log打印用此函数，然后转向PrintfChannel
*@param	  format：需要打印的数据
*@return  无
*/
void LogPrintf(const char *format, ...)
{
	uint8_t length;
	if (PrintfMessageLog == PRINTF_MESSAGE_ENABLE)    // 打印LOG允许
	{
		// 以下是将打印内容转成uint8_t数组内容
	  va_list args;
		va_start(args, format);
		length = vsnprintf((char*)printBuf, sizeof(printBuf), (char*)format, args); //格式化内容
		va_end(args);
		if (length > PRINTF_LENGTH) // 内容不能超过打印长度
			return;
		PrintfChannel(length);     // 开启打印
	}
}

/**
*@brief	 test调试用打印用此函数，然后转向PrintfChannel
*@param	 format：需要打印的数据
*@return 无
*/
void TestPrintf(const char *format, ...) // 与LOG打印完全相同
{
	uint8_t length;
	if (PrintfMessageTest == PRINTF_MESSAGE_ENABLE)
	{
		va_list args;
		va_start(args, format);
		length = vsnprintf((char*)printBuf, sizeof(printBuf), (char*)format, args);//格式化内容
		va_end(args);
		if (length > PRINTF_LENGTH)
			return;
		PrintfChannel(length);
	}
	
}










/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : task.c
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : 任务文件
*******************************************************************************/
#define GLOBAL_VARIABLE
#include "include.h"

/*
 * 任务初始化：调用任务增加函数，将任务增加到任务数组内
 */
void task_init(void)
{
  taskID_ = 0;  // 任务数量

  task_add(taskID_++, &_TaskUartRx, task_uart_rx_init);
  task_add(taskID_++, &_TaskUartTx, task_uart_tx_init);
  task_add(taskID_++, &_TaskConfig, task_config_init);
  task_add(taskID_++, &_TaskMotorControl, task_motor_control_init);
  task_add(taskID_++, &_TaskIdle, task_idle_init);
}

/*
 *  任务增加：对新任务做初始化默认配置，并调用任务本身的初始化函数进行单独配置
 */
void task_add(uint8_t taskId, sTASK *taskname, void (*init)(void))
{
  _TaskFlow[taskId] = taskname;              // 任务名称
  _TaskFlow[taskId]->init        = init;                  // 任务初始化函数
  _TaskFlow[taskId]->state       = TASK_STATE_SLEEP;      // 任务状态
  _TaskFlow[taskId]->interval    = 0;                     // 任务间隔
  _TaskFlow[taskId]->progressBar = TASK_BAR_CMD;          // 任务步骤
  _TaskFlow[taskId]->alteration  = NULL;                  // 任务变更函数
  _TaskFlow[taskId]->info        = TASK_INFO_NORMAL;      // 任务状态
  _TaskFlow[taskId]->timeOut     = 0;                     // 任务超时间隔
  _TaskFlow[taskId]->rxBuf       = NULL;                  // 任务接收数据缓存
  _TaskFlow[taskId]->txBuf       = NULL;                  // 任务发送函数缓存 -- 未用
  _TaskFlow[taskId]->rxLen       = 0;                     // 接收数据长度
  _TaskFlow[taskId]->txLen       = 0;                     // 发送数据长度
  _TaskFlow[taskId]->init();                              // 执行任务初始化函数

}
/*
 * 命令任务处理：通过匹配指令将接收的数据内容复制到任务协议栈中
 */
void task_cmd(uint8_t *buf, uint8_t len, uint8_t port)
{
  uint8_t i;
  for (i = 0; i < taskID_; i++)          // 循环每一个任务的指令
  {
    if (buf[0] == _TaskFlow[i]->command) // 若参数内指令等任务指令，此参数为此任务的协议
    {
      _TaskFlow[i]->port = port;
      if (_TaskFlow[i]->rxBuf != NULL)   // 任务配置参数的情况，写入参数
      {
        memcpy(_TaskFlow[i]->rxBuf, buf, len);  // 复制参数，注意长度没有判断可能会出错，接收时必需确保接收长度等于协议长度
      }
      _TaskFlow[i]->state = TASK_STATE_RUN; // 开启任务运行状态

      // 根据是否变更任务参数的情况执行操作
      // 任务变更函数指在不打断当前函数执行的前提下更改任务参数，一般用于循环执行的函数
      // 其它函数指从头开始运行函数
      if (NULL != *(_TaskFlow[i]->alteration))
        _TaskFlow[i]->alteration(); // 若有任务变更函数执行
      else
        _TaskFlow[i]->progressBar = TASK_BAR_CMD;                       // 若无任务变更函数，从开始执行
    }

  }
}
/*
 * 任务运地函数
 */
void task_run(void)
{
  uint8_t i;
//  uint32_t oldtick;
  for (i = 0; i < taskID_; i++)                    // 轮询任务数组内每一个任务
  {
    if (TASK_STATE_RUN == _TaskFlow[i]->state)    // 若任务状态为运行状态，运行任务函数
    {
 //     oldtick = sysTick_;
      _TaskFlow[i]->fun();                       // 运行任务函数
//      if (((sysTick_ - oldtick) > 1) && (sysTick_ > oldtick))
//        printf("运行超时！任务号;%d 超时时间:%d", i, sysTick_ - oldtick);
    }
  }

}

/*
 * 空闲任务初始化
 */
void task_idle_init(void)
{
  runTick_ = 0;    // 任务计数变量
                   //   HAL_IWDG_Start(&hiwdg); // 开看门狗
  _TaskIdle.command = CMD_TASK_IDLE;  // 任务指令
  _TaskIdle.fun     = task_idle;       // 任务函数
  _TaskIdle.state   = TASK_STATE_RUN; // 任务状态

}
/*
 * 空闲任务
 */
void task_idle(void)
{
  runTick_++;            // 任务内部计数
                         // 系统灯闪烁控制，500ms翻转一次IO口
  if ((runTick_ % 5) == 0)
  {
    gpio_toggle_pin(LED_SYS_GPIO_Port, LED_SYS_Pin);
    control_blinking();
  }
  test_hardware();
  if ((IR_LOCATION_GPIO_Port->IDR & IR_LOCATION_Pin) != (uint32_t)Bit_RESET)
  {
//    if (((irLocationNum_ - 0) > 2) && ((irLocationNum_ - 0) < 15))
//    {      
//      encoderNum_++;
//    }
//    else if (((0 - irLocationNum_) > 2) && (( 0 - irLocationNum_) < 10))
//    {
//      encoderNum_--;
//    }
//    else if (( 0 - irLocationNum_) > 15)
//    {
//      encoderNum_ = 0;
//      printf( "%s %d\n","t",0);
//    }

    RSV_OUT1_GPIO_Port->BRR = RSV_OUT1_Pin;
    irLocationNum_ =  0;
  }
    
  // HAL_IWDG_Refresh(&hiwdg);           // 喂狗
  _TaskIdle.interval = 100;              // 延时也可用于控制喂狗间隔
  _TaskIdle.state    = TASK_STATE_DELAY; // 任务状态设置

}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





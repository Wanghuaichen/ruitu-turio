/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : task.c
* Author             : ME
* Version            : V1.0
* Date               : 2016.11.18
* Description        : �����ļ�
*******************************************************************************/
#define GLOBAL_VARIABLE
#include "include.h"

/*
 * �����ʼ���������������Ӻ��������������ӵ�����������
 */
void task_init(void)
{
  taskID_ = 0;  // ��������

  task_add(taskID_++, &_TaskUartRx, task_uart_rx_init);
  task_add(taskID_++, &_TaskUartTx, task_uart_tx_init);
  task_add(taskID_++, &_TaskConfig, task_config_init);
  task_add(taskID_++, &_TaskMotorControl, task_motor_control_init);
  task_add(taskID_++, &_TaskIdle, task_idle_init);
}

/*
 *  �������ӣ�������������ʼ��Ĭ�����ã�������������ĳ�ʼ���������е�������
 */
void task_add(uint8_t taskId, sTASK *taskname, void (*init)(void))
{
  _TaskFlow[taskId] = taskname;              // ��������
  _TaskFlow[taskId]->init        = init;                  // �����ʼ������
  _TaskFlow[taskId]->state       = TASK_STATE_SLEEP;      // ����״̬
  _TaskFlow[taskId]->interval    = 0;                     // ������
  _TaskFlow[taskId]->progressBar = TASK_BAR_CMD;          // ������
  _TaskFlow[taskId]->alteration  = NULL;                  // ����������
  _TaskFlow[taskId]->info        = TASK_INFO_NORMAL;      // ����״̬
  _TaskFlow[taskId]->timeOut     = 0;                     // ����ʱ���
  _TaskFlow[taskId]->rxBuf       = NULL;                  // ����������ݻ���
  _TaskFlow[taskId]->txBuf       = NULL;                  // �����ͺ������� -- δ��
  _TaskFlow[taskId]->rxLen       = 0;                     // �������ݳ���
  _TaskFlow[taskId]->txLen       = 0;                     // �������ݳ���
  _TaskFlow[taskId]->init();                              // ִ�������ʼ������

}
/*
 * ����������ͨ��ƥ��ָ����յ��������ݸ��Ƶ�����Э��ջ��
 */
void task_cmd(uint8_t *buf, uint8_t len, uint8_t port)
{
  uint8_t i;
  for (i = 0; i < taskID_; i++)          // ѭ��ÿһ�������ָ��
  {
    if (buf[0] == _TaskFlow[i]->command) // ��������ָ�������ָ��˲���Ϊ�������Э��
    {
      _TaskFlow[i]->port = port;
      if (_TaskFlow[i]->rxBuf != NULL)   // �������ò����������д�����
      {
        memcpy(_TaskFlow[i]->rxBuf, buf, len);  // ���Ʋ�����ע�ⳤ��û���жϿ��ܻ��������ʱ����ȷ�����ճ��ȵ���Э�鳤��
      }
      _TaskFlow[i]->state = TASK_STATE_RUN; // ������������״̬

      // �����Ƿ���������������ִ�в���
      // ����������ָ�ڲ���ϵ�ǰ����ִ�е�ǰ���¸������������һ������ѭ��ִ�еĺ���
      // ��������ָ��ͷ��ʼ���к���
      if (NULL != *(_TaskFlow[i]->alteration))
        _TaskFlow[i]->alteration(); // ��������������ִ��
      else
        _TaskFlow[i]->progressBar = TASK_BAR_CMD;                       // �����������������ӿ�ʼִ��
    }

  }
}
/*
 * �����˵غ���
 */
void task_run(void)
{
  uint8_t i;
//  uint32_t oldtick;
  for (i = 0; i < taskID_; i++)                    // ��ѯ����������ÿһ������
  {
    if (TASK_STATE_RUN == _TaskFlow[i]->state)    // ������״̬Ϊ����״̬������������
    {
 //     oldtick = sysTick_;
      _TaskFlow[i]->fun();                       // ����������
//      if (((sysTick_ - oldtick) > 1) && (sysTick_ > oldtick))
//        printf("���г�ʱ�������;%d ��ʱʱ��:%d", i, sysTick_ - oldtick);
    }
  }

}

/*
 * ���������ʼ��
 */
void task_idle_init(void)
{
  runTick_ = 0;    // �����������
                   //   HAL_IWDG_Start(&hiwdg); // �����Ź�
  _TaskIdle.command = CMD_TASK_IDLE;  // ����ָ��
  _TaskIdle.fun     = task_idle;       // ������
  _TaskIdle.state   = TASK_STATE_RUN; // ����״̬

}
/*
 * ��������
 */
void task_idle(void)
{
  runTick_++;            // �����ڲ�����
                         // ϵͳ����˸���ƣ�500ms��תһ��IO��
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
    
  // HAL_IWDG_Refresh(&hiwdg);           // ι��
  _TaskIdle.interval = 100;              // ��ʱҲ�����ڿ���ι�����
  _TaskIdle.state    = TASK_STATE_DELAY; // ����״̬����

}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





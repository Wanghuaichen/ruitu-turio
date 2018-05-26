/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_motor.h
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        电机接口函数头文件
**************************************************************************************************
*/
#ifndef _API_MOTOR_H_
#define _API_MOTOR_H_
#include "include.h"
/*--------------- 宏定义 --------------*/
// 针对canopen定义
#define DEVICE_ID                      0x01 // 设备ID

// nmt令指定义
#define NMT_START_REMOTE_NODE              1 // 开启远程节点
#define NMT_STOP_REMOTE_NODE               2 // 关闭远程节点
#define NMT_ENTER_PREOPERATIONAL_STATE     128 // 进入预运行状态
#define NMT_RESET_NODE                     129 // 复位结点
#define NMT_RESET_COMMUNICTION             130 // 复位通信

// ID定义
#define SYNCHRONIZATION_CYCLE_ID       0x000600 // 同步两个电机的周期 Cycle synchronization
#define SYNCHRONIZATION_START_ID       0x000600 // 启动周期同步
#define NMT_BROADCAST_ID               0x000000 // NMT用的广播ID
#define NMT_NODE_GUARDING_ID           0x000700 // NMT用的节点保护ID
// 定义运动状态
#define MOTOR_MODE_POSITION       0  // 定义运动为位置模式
#define MOTOR_MODE_HOMING         1  // 定义运动为回零模式
// 定义暂停标志
#define MOTOR_PAUSE_ENABLE_NOT_ACTIVE      0x01 // 因使能状态未激活暂停
#define MOTOR_PAUSE_OBSTACLE_SENSOR_LEFT   0x02 // 因左避障传感器信号暂停
#define MOTOR_PAUSE_OBSTACLE_SENSOR_RIGHT  0x04 // 因右避障传感器信号暂停
#define MOTOR_PAUSE_COMMAND_PAUSE          0x08 // 因上位机下发暂停指令暂停
#define MOTOR_PAUSE_PUT_RIGHT              0x80 // 允许状态清除后自动恢复支行标志，可设置
// 定义电机状态
#define MOTOR_STATE_COMMUNICATION_ERROR    0x10 // 电机状态为通信失败
#define MOTOR_STATE_HOMING_STATE           0x20 // 电机当前回零状态 置位为回零成功。否则为正在回零中
#define MOTOR_STATE_MOVE_COMPLETE          0x40 // 电机当前回零状态 置位为回零成功。否则为正在回零中
/**
 寄存器控制宏定义-位置模式
  配置过程：
step1:  s r0xc8 0  //设置位置为绝对位置模式，采用梯形曲线
step2:  s r0xca ---//设置目标位置
step3:  s r0xcb ---//设置速度
step4:  s r0xcc ---//设置加速度
step5:  s r0xcd ---//设置减速度
step6:  s r0xcf ---//设置紧急减速度
step7:  s r0x24 21 //电机位置模式使能
step8:  t 1        //开始位置模式运动
注意：如果在运动过程中更改胃运动参数，比如说提高速度，先发送速度命令，然后发送 t 1，这样才能更新寄存器的值
*/
#define MOTOR_REG_SET_DESIRED_STATE           "r0x24 "  // 配置电机工模式21：
#define MOTOR_REG_SET_POS_PROFILE_TYPE        "r0xc8 "  // 配置电机位置模式
#define MOTOR_REG_SET_POS_POSITION            "r0xca "  // 配置电机位置寄存器
#define MOTOR_REG_SET_POS_VELOCITY            "r0xcb "  // 配置电机速度寄存器
#define MOTOR_REG_SET_POS_ACCELERATION        "r0xcc "  // 配置电机加速度寄存器
#define MOTOR_REG_SET_POS_DECELERATION        "r0xcd "  // 配置电机减速度寄存器
#define MOTOR_REG_SET_POS_MAXIMUM_JERKRATE    "r0xce "  // 配置电机maxinum jerk rate
#define MOTOR_REG_SET_POS_ABORT_DECELERATION  "r0xcf "  // 配置电机紧急减速度
                                                      //
#define MOTOR_REG_UPDATE                      "t 1"  // 开始位置运动命令/更新参数命令/继续运动命令
#define MOTOR_REG_PAUSE                       "t 0"  // 运动暂停命令，此时电机回在当前位置以紧急停止加速度停下
                                                  //
/**
 寄存器控制宏定义-回零模式
 配置过程：
step1:  s r0xc2 529//设置使用负向限位开关作为触发
step2:  s r0xc3 ---//设置碰到开关前的高速
step3:  s r0xc4 ---//设置碰到开关后的低速
step4:  s r0xc5 ---//设置减速度
step5:  s r0xc6 ---//设置原点偏移量
step6:  s r0x24 21 //使电机工作在位置模式下（因为回零模式本质上也是在跑位置）
step7:  t 2        //开始进行回零运动
*/
#define MOTOR_REG_SET_DESIRED_STATE            "r0x24 "  // 配置电机工模式21
#define MOTOR_REG_SET_HOME_HOMING_METHOD       "r0xc2 "  // 配置电回零方式 529 for Negative limit switch or 513 for the positive
#define MOTOR_REG_SET_HOME_FAST_VELOCITY       "r0xc3 "  // 配置电机回零最大速度
#define MOTOR_REG_SET_HOME_SLOW_VELOCITY       "r0xc4 "  // 配置电机回零最小速度
#define MOTOR_REG_SET_HOME_ACC_DECELERATION    "r0xc5 "  // 配置电机加/减速度寄存器
#define MOTOR_REG_SET_HOME_OFFSET              "r0xc6 "  // 配置电机零点偏移量
#define MOTOR_REG_SET_HOME_START               "t 2"  // 开始进行回零运动，若中途要急停，可发送t 0,继续运动可发送 t 1
                                                  //

// 定义设置值与实际下发值关系
#define MOTOR_COUNTS_VELOCITY       (1009)  // 转换成脉冲速度需要乘的倍数
#define MOTOR_COUNTS_POSITION       (101)  // 转换成脉冲位置需要乘的倍数
#define MOTOR_COUNTS_ACCELERATION   (101)  // 转换成脉冲加速度需要乘的倍数

// 定义读取数据寄存器
#define MOTOR_REG_GET_MONITORING_STATUS     "r0xa0 " // 读控制器寄存器状态指令
#define MOTOR_REG_GET_ACTUAL_POSITION       "r0x32 " // 读控制器实际位置指令
#define MOTOR_REG_GET_TRAJECTORY_STATUS     "r0xc9 " // 读控制器运动状态寄存器指令 12 、13位
#define MOTOR_REG_GET_ACTUAL_VELOCITY       "r0x18 " // 读控制器实际速度

// 寄存器状态定义
#define MOTOR_REG_STATUS_ENABLE_NOT_ACTIVE        (0x00000800) // 寄存器当前处于非使能状态 0xa0  11位
#define MOTOR_REG_STATUS_MOVE_COMPLETE            (0x08000000) // 寄存器当前处于运动完成状态 0xa0 27位
#define MOTOR_REG_STATUS_HOMING_SUCCESSFULLY      (0x1000) // 寄存器回零成功状态     0xc9 12位
#define MOTOR_REG_STATUS_HOMING_RUNING            (0x2000) // 寄存器正在回零过程中状态 0xc9 13位
/*--------------- 变量定义 --------------*/

/*--------------- 函数定义 --------------*/

void motor_start_node(void);
void motor_stop_node(void);
void motor_set_syn_cycle(void);
void motor_start_syn(void);
//uint8_t motor_get_state(uint8_t *buf,uint8_t len);

void motor_get_state(void);
uint8_t motor_set_position(uint32_t position);
uint8_t motor_set_velocity(uint32_t velocity);
void motor_start_position_mode(void);
void task_motor_control_init(void);
void task_motor_control(void);
void task_motor_state_init(void);
void task_motor_state(void);
uint8_t motor_tx_data_processing(char ins,char *reg,char* sendData,uint16_t len);
uint8_t motor_rx_data_processing(char *buf,uint16_t len);
uint8_t motor_mode_control(E_MOTOR_STATE* mode);
uint8_t motor_mode_control_homing(uint8_t step);
uint8_t motor_mode_control_position(uint8_t step, E_MOTOR_STATE mode);
void motor_state_Processing(void);
uint8_t motor_mode_control_stop(uint8_t step);
uint8_t motor_mode_control_start(uint8_t step);
uint8_t motor_mode_control_home_start(uint8_t step);
uint8_t GetMotorState(uint8_t *buf,uint8_t len);
void SetMotor(uint8_t state);
void SetCAN(uint8_t state);
#endif


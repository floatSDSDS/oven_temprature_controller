/*
 * Timer.h
 *
 *  Created on: 2015年8月24日
 *      Author: Administrator
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "system.h"
#include "device.h"

#ifdef TIMER_C_

	#define TIMER_C_Extern

#else

	#define TIMER_C_Extern  extern

#endif


//中断标志
#define Interrupt   1
#define UnInterrupt 0


//volatile uint16_t TimerCounter;

//一大坨全局变量
TIMER_C_Extern volatile uint32_t TimerCounter;			//定时器计数器
TIMER_C_Extern volatile uint8_t TimerIntFlag;			//定时器中断标志
TIMER_C_Extern volatile uint8_t Flag;					//控制模式/调整模式切换标志
TIMER_C_Extern volatile uint8_t Label;					//参数更改标签
TIMER_C_Extern volatile uint32_t Vout;					//AD采样输出电压
TIMER_C_Extern volatile float temp;						//当前温度
TIMER_C_Extern volatile uint32_t  ui32SysClock;			//系统时钟
TIMER_C_Extern int tempz;								//当前温度整数部分
TIMER_C_Extern int tempd;								//
TIMER_C_Extern int settemp1;							//采样值
TIMER_C_Extern int T_set;								//给定温度的设定值
TIMER_C_Extern int T_temp;								//给定温度的调整值
TIMER_C_Extern char tempc[20];							//
TIMER_C_Extern volatile float speeda;					//PID控制器输出值
TIMER_C_Extern int ton;									//占空比中开烤箱的时间



TIMER_C_Extern float P_temp;							//Kp调整值
TIMER_C_Extern float I_temp;							//Ki调整值
TIMER_C_Extern float D_temp;							//Kd调整值


TIMER_C_Extern int pidbz;


//声明并实现一个全局pid结构体
TIMER_C_Extern struct _pid{
	float SetSpeed;
	float ActualSpeed;
	float err;
	float err_max;
	float err_next;
	float err_last;
	float integral;
	float integral_max;
	float voltage;
	float zuizhong;
	float Kp,Ti,Td;
}pid;


/* Private function prototypes -----------------------------------------------*/
void TIMER_Init(void);



#endif /* TIMER_H_ */

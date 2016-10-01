/*
 * Timer.c
 *
 *  Created on: 2015年8月24日
 *      Author: Administrator
 */

#define TIMER_C_

#include "Timer.h"
#include "led.h"
#include "Button.h"
#include "ADC.h"
#include "LCM.h"

/******************************************************************************
  * 函数：  TIMER_Init()
  * 描述：  定时器初始化
  * 输入值：无
  *	返回值：无
  ******************************************************************************/

void TIMER_Init()
{

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); 	//使能外设定时器
	 TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);//将TIMER0B配置为16位周期定时器
	 TimerLoadSet(TIMER0_BASE, TIMER_B,10000000/1000);            //设置周期
	 IntMasterEnable();
	 TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT); //使能TIMER输出中断
	 IntEnable(INT_TIMER0B);  							//使能处理器的TIMER0B中断
	 TimerEnable(TIMER0_BASE, TIMER_B); 				//打开TIMER0B

	 Flag=0;
	 TimerCounter = 5;
	 TimerIntFlag = UnInterrupt;
}



/******************************************************************************
  * 函数：  TIMER0B_Handler()
  * 描述：  定时器中断函数
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void TIMER0B_Handler()
{
	TimerCounter ++;
		if(TimerCounter%100==0){
			Button_run();
			DelayMs(5);
		}
		if(TimerCounter%2000==0){
			if(Flag==1){
				if(TimerCounter%4000==0){
					speeda=PID_realize(settemp1,temp);					//得到偏差
					ton = (int)speeda*36;
					TimerCounter = 0;
					}
				Vout=ADC_SampleValue();									//获取采样序列
				temp=5.0/4096*Vout/8000*1000000-427;					//获取当前温度
				tempz=(int)temp;										//获取当前温度整数部分
				settemp1=T_set;											//赋采样值
				UARTprintf("%d.%02d\n",tempz,(int)((temp-tempz)*100));	//串口输出
				WriteFloat(4,1,temp);									//屏幕更新
			}
		}
		//控制电烤箱开闭
		if(Flag==1){
			if(speeda==100){
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);
			}
			else if(speeda<=0){
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);
			}
			//PWM实现
			else{
				if(TimerCounter>ton){
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);
				}
				else{
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);
				}
			}
		}
		TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);  //清除中断标志
}

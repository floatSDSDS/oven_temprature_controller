/******************************************************************************
  * 文件： main.c
  * 作者：
  * 日期： 2015—07-02
  * 版本： 1.0
  * 说明： 实验二：矩阵按键操作实验
  *
  ******************************************************************************/

#include "system.h"  //库头文件
#include "device.h"  //外设头文件



int main(void)
{
	/*1.System Init*/
	SysClock_Init();    //10MHZ
	/*2.Device Init*/
	//一大坨初始化
	LED_Init();			//LED初始化
	TIMER_Init();		//定时器初始化
	Button_Init();		//按键gpio口初始化
	ADC_Init();			//AD590初始化
	init_12864IO();
	init_12864();		//LCD屏幕初始化
	PID_Init() ;		//为PID结构体赋初值
	UART_Init();		//串口初始化

	//保证电烤箱是一个关着的电烤箱
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);


	//点亮一盏状态灯
	LED_On();

	//为LCD屏幕初始状态赋值
	WriteStr(0,0,"给定温度");
	WriteNum(4,0,T_set);
	WriteStr(0,1,"当前温度");
	WriteStr(0,2,"P:");
	//在屏幕上转换输出浮点数
	WriteFloat(1,2,pid.Kp);
	WriteStr(4,2,"I:");
	WriteFloat(5,2,pid.Ti);
	WriteStr(0,3,"D:");
	WriteFloat(1,3,pid.Td);

	//串口打印输出开始
	UARTprintf("--------炉温PID测试开始-------\n");
//	UARTprintf("P：%d.%02d    \n",(int)pid.Kp,(int)((pid.Kp-(int)pid.Kp)*100));
//	UARTprintf("I：%d.%02d    \n",(int)pid.Ti,(int)((pid.Ti-(int)pid.Ti)*100));
//	UARTprintf("D：%d.%02d    \n",(int)pid.Td,(int)((pid.Td-(int)pid.Td)*100));
//	UARTprintf("当前给定值：%d    \n",T_set);
	while(1){
	}

}

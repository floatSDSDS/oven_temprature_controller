/*
 * Button.c
 *
 *  Created on: 2016年7月5日
 *      Author: floatSD
 */
#ifndef BUTTON_C_
#define BUTTON_C_

#include "Button.h"
#include "Sys.h"
#include "led.h"
#include "Timer.h"
#include "UART.h"


/******************************************************************************
  * 函数：  Button_Init()
  * 描述：  按键初始化
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void Button_Init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);//使能GPIOP
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);//使能GPION
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//使能GPIOD
	GPIOPinTypeGPIOInput(GPIOP, GPIO_PIN_2);//配置PP2为行输入
	GPIOPinTypeGPIOInput(GPION, GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinTypeGPIOInput(GPIOD, GPIO_PIN_0);
}



/******************************************************************************
  * 函数：  Button_Scan()
  * 描述：  按键扫描程序，按键有优先级
  * 输入值：无
  *	返回值：返回被按下的按键编号
  ******************************************************************************/
uint8_t Button_Scan()
{
	if(GPIOPinRead(GPIO_PORTP_BASE, GPIO_PIN_2)!=0){
		return J1;
	}
	if(GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_3)!=0){
		return J2;
	}
	if(GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_2)!=0){
		return J3;
	}
	if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0)!=0){
		return J4;
	}
	else
		return NJ;
}



/******************************************************************************
  * 函数： Button_J1()
  * 描述：  加按键程序，根据Label增加选取参数的临时值
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void Button_J1(){
	switch(Label){

	case 0:	T_temp=T_temp+5;				//增加给定温度
			Flag=0;							//置Flag=0，为调整模式，电烤箱不加热
			WriteNum(4,0,T_temp);			//更新屏幕上的值
			if(T_temp<100){
				WriteChar(5,0,32);			//防止越界时显示出错，32为0的ASCII码
			}break;

	case 1:P_temp=P_temp+0.05;Flag=0;WriteFloat(1,2,P_temp);break;
	case 2:I_temp=I_temp+0.05;Flag=0;WriteFloat(5,2,I_temp);break;
	case 3:D_temp=D_temp+0.05;Flag=0;WriteFloat(1,3,D_temp);break;
	default:break;
	}
}



/******************************************************************************
  * 函数： Button_J2()
  * 描述：   加按键程序，根据Label减少选取参数
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void Button_J2(){
	switch(Label){
	case 0:T_temp=T_temp-5;Flag=0;WriteNum(4,0,T_temp);if(T_temp<100){WriteChar(5,0,32);}break;
	case 1:P_temp=P_temp-0.05;Flag=0;WriteFloat(1,2,P_temp);break;
	case 2:I_temp=I_temp-0.05;Flag=0;WriteFloat(5,2,I_temp);break;
	case 3:D_temp=D_temp-0.05;Flag=0;WriteFloat(1,3,D_temp);break;
	default:break;
	}
}




/******************************************************************************
  * 函数：  Button_J3()
  * 描述：  确定按键函数，将之前更改的临时值赋给PID结构体，置模式为控制模式
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void Button_J3(){
	Flag=1;
	T_set=T_temp;WriteNum(4,0,T_set);
	pid.Kp=P_temp;WriteFloat(1,2,pid.Kp);
	pid.Ti=I_temp;WriteFloat(5,2,pid.Ti);
	pid.Td=D_temp;WriteFloat(1,3,pid.Td);
	//串口输出
	UARTprintf("--------更改参数为-------\n");
	UARTprintf("P：%d.%02d    \n",(int)pid.Kp,(int)((pid.Kp-(int)pid.Kp)*100));
	UARTprintf("I：%d.%02d    \n",(int)pid.Ti,(int)((pid.Ti-(int)pid.Ti)*100));
	UARTprintf("D：%d.%02d    \n",(int)pid.Td,(int)((pid.Td-(int)pid.Td)*100));
	UARTprintf("当前给定值：%d    \n",T_set);
}



/******************************************************************************
  * 函数： Button_J4()
  * 描述：  切换按键函数，更改Label值在0-4循环
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void Button_J4(){
	Flag=0;
	Label++;
	if(Label>3){
		Label=0;
	}

}


/******************************************************************************
  * 函数：  Button_run()
  * 描述：  根据扫描结果执行按键函数
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void Button_run(){
	uint8_t Key = Button_Scan();
			switch(Key)
			{
				case J1: Button_J1();break;
				case J2: Button_J2();break;
				case J3: Button_J3();break;
				case J4: Button_J4();break;
				default:		break;
			}
			DelayMs(5);
}

#endif /* BUTTON_C_ */

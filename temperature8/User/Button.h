/*
 * Button.h
 *
 *  Created on: 2016年7月5日
 *      Author: floatSD
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "system.h"

/* Private define-------------------------------------------------------------*/

//低电平表示0，按下键也是低电平所以也是0
#define LOW       0x00
#define KEYPRESS  0X00

/*按键值-与开发板上的对应*/
#define NJ   0   //没有按下键码
#define J1   1   //按下J1
#define J2   2
#define J3   3
#define J4   4

//按键用到的三个端口
#define GPIOP         GPIO_PORTP_BASE
#define GPION         GPIO_PORTN_BASE
#define GPIOD         GPIO_PORTD_BASE

/*输入输出模式配置*/
#define ROW_GPIOP_IN()	 GPIOPinTypeGPIOInput(GPIOP, GPIO_PIN_2)//配置PP2为行输入
#define ROW_GPION_IN()   GPIOPinTypeGPIOInput(GPION, GPIO_PIN_2|GPIO_PIN_3)
#define ROW_GPIOD_IN()   GPIOPinTypeGPIOInput(GPIOD, GPIO_PIN_0)

void    Button_Init(void);		//按键初始化
void Button_run();				//选择按键并运行相应按键程序
uint8_t Button_Scan(void);		//按键扫描程序
void Button_J1();				//加按键的程序
void Button_J2();				//减按键程序
void Button_J3();				//确定按键程序
void Button_J4();				//切换按键程序


#endif /* BUTTON_H_ */

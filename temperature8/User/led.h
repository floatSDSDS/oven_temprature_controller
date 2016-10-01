/*
 * led.h
 *
 *  Created on: 2016年7月4日
 *      Author: floatSD
 */

#ifndef LED_H_
#define LED_H_

#include "system.h"


/* Private define-------------------------------------------------------------*/
#define PinLow        0x00

#define GPIOF         GPIO_PORTF_BASE


#define LED_GPIOF_OUT()     GPIOPinTypeGPIOOutput(GPIOF, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)//配置PF1、PF2、PF3为输出
//#define LED_GPIOL_OUT()     GPIOPinTypeGPIOOutput(GPIOL, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4)//配置PL0、PL1、PL2、PL3、PL4为输出

#define LED0_ON()     GPIOPinWrite(GPIOF,GPIO_PIN_1,GPIO_PIN_1);
#define LED0_OFF()	  GPIOPinWrite(GPIOF,GPIO_PIN_1,PinLow);

/*
#define LED1_ON()     GPIOPinWrite(GPIOF,GPIO_PIN_2,GPIO_PIN_2);
#define LED1_OFF()	  GPIOPinWrite(GPIOF,GPIO_PIN_2,PinLow);

#define LED2_ON()     GPIOPinWrite(GPIOF,GPIO_PIN_3,GPIO_PIN_3);
#define LED2_OFF()	  GPIOPinWrite(GPIOF,GPIO_PIN_3,PinLow);

#define LED3_ON()     GPIOPinWrite(GPIOL,GPIO_PIN_0,GPIO_PIN_0);
#define LED3_OFF()	  GPIOPinWrite(GPIOL,GPIO_PIN_0,PinLow);

#define LED4_ON()     GPIOPinWrite(GPIOL,GPIO_PIN_1,GPIO_PIN_1);
#define LED4_OFF()	  GPIOPinWrite(GPIOL,GPIO_PIN_1,PinLow);

#define LED5_ON()     GPIOPinWrite(GPIOL,GPIO_PIN_2,GPIO_PIN_2);
#define LED5_OFF()	  GPIOPinWrite(GPIOL,GPIO_PIN_2,PinLow);

#define LED6_ON()     GPIOPinWrite(GPIOL,GPIO_PIN_3,GPIO_PIN_3);
#define LED6_OFF()	  GPIOPinWrite(GPIOL,GPIO_PIN_3,PinLow);

#define LED7_ON()     GPIOPinWrite(GPIOL,GPIO_PIN_4,GPIO_PIN_4);
#define LED7_OFF()	  GPIOPinWrite(GPIOL,GPIO_PIN_4,PinLow);

*/

void LED_Init(void);
void LED_On();
void LED_Off();//需要调用Sys.h



#endif /* LED_H_ */

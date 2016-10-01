/*
 * led.c
 *
 *  Created on: 2016��7��4��
 *      Author: floatSD
 */
#include "led.h"
#include "Sys.h"

/******************************************************************************
  * ������  LED_Init()
  * ������  LED��ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void LED_Init()
{

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//ʹ��GPIOF
	LED_GPIOF_OUT();
}

/******************************************************************************
  * ������  LED_On()
  * ������  ����
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void LED_On()
{
	LED0_ON();
	DelayMs(125);
}


/******************************************************************************
  * ������  LED_Off()
  * ������  ����
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void LED_Off()
{
	LED0_OFF();
	DelayMs(125);
}


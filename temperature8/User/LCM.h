/*
 * LCM.h
 *
 *  Created on: 2016��7��5��
 *      Author: floatSD
 */

#ifndef LCM_H_
#define LCM_H_

#include "system.h"

#define uchar unsigned char
#define uint unsigned int
#define SID_HIGH GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5) //���������߸ߵ�ƽ
#define SID_LOW GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0) //���������ߵ͵�ƽ
#define CLK_HIGH GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6) //����ʱ���߸ߵ�ƽ
#define CLK_LOW GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0) //����ʱ���ߵ͵�ƽ
volatile uint32_t ui32SysClock;



void delay_Nms(uint8_t n);
void init_12864IO();
void Write1byte(uint8_t Byte);
void W_RS(uint8_t RS,uint8_t Data);
void WriteStr(uint8_t x,uint8_t y,char *Str);
void WriteChar(uint8_t x,uint8_t y,uint8_t Chr) ;
void init_12864();
void WriteNum(uint8_t x,uint8_t y,int l);
void WriteFloat(uint8_t x,uint8_t y,float l);

#endif /* LCM_H_ */

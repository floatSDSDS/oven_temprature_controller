/*
 * LCM.c
 *
 *  Created on: 2016年7月5日
 *      Author: floatSD
 */

#include "LCM.h"
#include "Timer.h"



/******************************************************************************
  * 函数：delay_Nms(uint8_t n)
  * 描述： 延时函数
  * 输入值：uint8_t n
  *	返回值：无
  ******************************************************************************/
void delay_Nms(uint8_t n) //延时函数
{
	uint i = 0;
	for(i=n;i>0;i--)
		SysCtlDelay(SysCtlClockGet() / 3000);
}



/******************************************************************************
  * 函数：init_12864IO()
  * 描述：12864驱动初始化
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void init_12864IO() //初始化12864
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, ~GPIO_PIN_4);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
	SID_LOW;
	CLK_LOW;
}



/******************************************************************************
  * 函数：void Write1byte(uint8_t Byte)
  * 描述：写入一个字节信息
  * 输入值：被写入字节信息uint8_t Byte
  *	返回值：无
  ******************************************************************************/
void Write1byte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
	if(Byte & 0x80)
	SID_HIGH;
	else
	SID_LOW;
	CLK_HIGH;
	CLK_LOW;
	Byte <<= 1;
	SysCtlDelay(533);
	}
}


/******************************************************************************
  * 函数：W_RS(uint8_t RS,uint8_t Data)
  * 描述：依次写入三个字节控制字
  * 输入值：第一个字节控制命令uint8_t RS,第二，三个字节控制数据uint8_t Data
  *	返回值：无
  ******************************************************************************/
void W_RS(uint8_t RS,uint8_t Data)
{
	uint8_t Head,HighData,LowData;
	//第一个字节读和写的两种功能
	if(RS)
		Head = 0XFA;
	else
		Head = 0XF8;
	//把控制数据分成高四位和第四位，分别送入第二字节和第三字节
	HighData = Data & 0XF0;
	LowData = Data<<4;
	//写入字节
	Write1byte(Head);
	Write1byte(HighData);
	Write1byte(LowData);
}



/******************************************************************************
  * 函数： WriteStr(uint8_t x,uint8_t y,char *Str)
  * 描述：在屏幕上写字符串
  * 输入值：uint8_t x,uint8_t y,待写入字符串char *Str
  *	返回值：无
  ******************************************************************************/
void WriteStr(uint8_t x,uint8_t y,char *Str)
{
	//根据不同行y，在对应x处写入字符串
	if(y==0)
		W_RS(0,0x80+x);
	if(y==1)
		W_RS(0,0x90+x);
	if(y==2)
		W_RS(0,0x88+x);
	if(y==3)
		W_RS(0,0x98+x);
	//当字符串遍历到结束符号则停止
	while(*Str != '\0')
	{
		W_RS(1,*Str++);
	}
}


/******************************************************************************
  * 函数：WriteChar(uint8_t x,uint8_t y,uint8_t Chr)
  * 描述：写字符串
  * 输入值：uint8_t x,uint8_t y,uint8_t Chr
  *	返回值：无
  ******************************************************************************/
void WriteChar(uint8_t x,uint8_t y,uint8_t Chr) //写字符
{
	if(y==0)
		W_RS(0,0x80+x);
	if(y==1)
		W_RS(0,0x90+x);
	if(y==2)
		W_RS(0,0x88+x);
	if(y==3)
		W_RS(0,0x98+x);
	W_RS(1,Chr);
}



/******************************************************************************
  * 函数：init_12864()
  * 描述：12864初始化
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void init_12864() // 初始化12864
{
	W_RS(0,0x30); //功能设定，基本指令集
	delay_Nms(5);
	W_RS(0,0x0c); //显示状态
	delay_Nms(5);
	W_RS(0,0x06); //移位控制
	delay_Nms(5);
	W_RS(0,0x01); //清除显示，地址归零
	delay_Nms(5);
}



/******************************************************************************
  * 函数：WriteNum(uint8_t x,uint8_t y,int l)
  * 描述：把整数转换成字符串在屏幕上显示
  * 输入值：uint8_t x,uint8_t y,int l
  *	返回值：无
  ******************************************************************************/
void WriteNum(uint8_t x,uint8_t y,int l){
	int m,n,i;
	uint8_t dingding;
	for(dingding=0;dingding<20;dingding++){
		tempc[dingding]=0;
	}
	if(l<100){
		m = l/10;
		n = l-m*10;
		m=m+48;
		n=n+48;
		tempc[0] = (char)m;
		tempc[1] = (char)n;
		WriteStr(x,y,tempc);
	}else if((l>=100)&&(l<110))
	{
		m = l/100;
		n = l-m*100;
		m=m+48;
		n=n+48;
		tempc[0] = (char)m;
		tempc[1] = '0';
		tempc[2] = (char)n;
		WriteStr(x,y,tempc);
	}
	else if(l>=110)
	{
		m = l/100;
		n = (l-m*100)/10;
		i = l-m*100-n*10;
		m=m+48;
		n=n+48;
		i = i+48;
		tempc[0] = (char)m;
		tempc[1] = (char)n;
		tempc[2] = (char)i;
		WriteStr(x,y,tempc);
	}
}



/******************************************************************************
  * 函数：WriteFloat(uint8_t x,uint8_t y,float l)
  * 描述：把浮点数转换为字符串在屏幕上显示
  * 输入值：uint8_t x,uint8_t y,float l
  *	返回值：无
  ******************************************************************************/
void WriteFloat(uint8_t x,uint8_t y,float l){
	int m,n,i,a,b;
	int mid1,mid2;
	uint8_t dingding;
	for(dingding=0;dingding<20;dingding++){
		tempc[dingding]=0;
	}
	mid1 = (int)l;
	if(mid1<100){
		m = mid1/10;
		n = mid1-m*10;
		m=m+48;
		n=n+48;
		tempc[0] = (char)m;
		tempc[1] = (char)n;
		tempc[2] = '.';
		mid2 = (int)((l-mid1)*100);
		a = mid2/10;
		b = mid2-a*10;
		a=a+48;
		b=b+48;
		tempc[3] = (char)a;
		tempc[4] = (char)b;
		tempc[5] = ' ';
		WriteStr(x,y,tempc);}
	//防止越界，强行在第三位写入零
		else if((mid1>=100)&&(mid1<110))
			{
				m = 1;
				n = mid1%10;
				m=m+48;
				n=n+48;
				tempc[0] = (char)m;
				tempc[1] = '0';
				tempc[2] = (char)n;
				tempc[3] = '.';
				mid2 = (int)((l-mid1)*100);
				a = mid2/10;
				b = mid2%10;
				a=a+48;
				b=b+48;
				tempc[4] = (char)a;
				tempc[5] = (char)b;
				WriteStr(x,y,tempc);
			}
	//防止越界，强行在第二位写入零
			else if(mid1>=110)
			{
				m = mid1/100;
				n = (l-m*100)/10;
				i = l-m*100-n*10;
				m=m+48;
				n=n+48;
				i = i+48;
				tempc[0] = (char)m;
				tempc[1] = (char)n;
				tempc[2] = (char)i;
				tempc[3] = '.';
				mid2 = (int)((l-mid1)*100);
				a = mid2/10;
				b = mid2-a*10;
				a=a+48;
				b=b+48;
				tempc[4] = (char)a;
				tempc[5] = (char)b;
				WriteStr(x,y,tempc);
			}
}



/*
 * LCM.c
 *
 *  Created on: 2016��7��5��
 *      Author: floatSD
 */

#include "LCM.h"
#include "Timer.h"



/******************************************************************************
  * ������delay_Nms(uint8_t n)
  * ������ ��ʱ����
  * ����ֵ��uint8_t n
  *	����ֵ����
  ******************************************************************************/
void delay_Nms(uint8_t n) //��ʱ����
{
	uint i = 0;
	for(i=n;i>0;i--)
		SysCtlDelay(SysCtlClockGet() / 3000);
}



/******************************************************************************
  * ������init_12864IO()
  * ������12864������ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void init_12864IO() //��ʼ��12864
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
  * ������void Write1byte(uint8_t Byte)
  * ������д��һ���ֽ���Ϣ
  * ����ֵ����д���ֽ���Ϣuint8_t Byte
  *	����ֵ����
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
  * ������W_RS(uint8_t RS,uint8_t Data)
  * ����������д�������ֽڿ�����
  * ����ֵ����һ���ֽڿ�������uint8_t RS,�ڶ��������ֽڿ�������uint8_t Data
  *	����ֵ����
  ******************************************************************************/
void W_RS(uint8_t RS,uint8_t Data)
{
	uint8_t Head,HighData,LowData;
	//��һ���ֽڶ���д�����ֹ���
	if(RS)
		Head = 0XFA;
	else
		Head = 0XF8;
	//�ѿ������ݷֳɸ���λ�͵���λ���ֱ�����ڶ��ֽں͵����ֽ�
	HighData = Data & 0XF0;
	LowData = Data<<4;
	//д���ֽ�
	Write1byte(Head);
	Write1byte(HighData);
	Write1byte(LowData);
}



/******************************************************************************
  * ������ WriteStr(uint8_t x,uint8_t y,char *Str)
  * ����������Ļ��д�ַ���
  * ����ֵ��uint8_t x,uint8_t y,��д���ַ���char *Str
  *	����ֵ����
  ******************************************************************************/
void WriteStr(uint8_t x,uint8_t y,char *Str)
{
	//���ݲ�ͬ��y���ڶ�Ӧx��д���ַ���
	if(y==0)
		W_RS(0,0x80+x);
	if(y==1)
		W_RS(0,0x90+x);
	if(y==2)
		W_RS(0,0x88+x);
	if(y==3)
		W_RS(0,0x98+x);
	//���ַ�������������������ֹͣ
	while(*Str != '\0')
	{
		W_RS(1,*Str++);
	}
}


/******************************************************************************
  * ������WriteChar(uint8_t x,uint8_t y,uint8_t Chr)
  * ������д�ַ���
  * ����ֵ��uint8_t x,uint8_t y,uint8_t Chr
  *	����ֵ����
  ******************************************************************************/
void WriteChar(uint8_t x,uint8_t y,uint8_t Chr) //д�ַ�
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
  * ������init_12864()
  * ������12864��ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void init_12864() // ��ʼ��12864
{
	W_RS(0,0x30); //�����趨������ָ�
	delay_Nms(5);
	W_RS(0,0x0c); //��ʾ״̬
	delay_Nms(5);
	W_RS(0,0x06); //��λ����
	delay_Nms(5);
	W_RS(0,0x01); //�����ʾ����ַ����
	delay_Nms(5);
}



/******************************************************************************
  * ������WriteNum(uint8_t x,uint8_t y,int l)
  * ������������ת�����ַ�������Ļ����ʾ
  * ����ֵ��uint8_t x,uint8_t y,int l
  *	����ֵ����
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
  * ������WriteFloat(uint8_t x,uint8_t y,float l)
  * �������Ѹ�����ת��Ϊ�ַ�������Ļ����ʾ
  * ����ֵ��uint8_t x,uint8_t y,float l
  *	����ֵ����
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
	//��ֹԽ�磬ǿ���ڵ���λд����
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
	//��ֹԽ�磬ǿ���ڵڶ�λд����
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



/*
 * Button.c
 *
 *  Created on: 2016��7��5��
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
  * ������  Button_Init()
  * ������  ������ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void Button_Init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);//ʹ��GPIOP
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);//ʹ��GPION
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//ʹ��GPIOD
	GPIOPinTypeGPIOInput(GPIOP, GPIO_PIN_2);//����PP2Ϊ������
	GPIOPinTypeGPIOInput(GPION, GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinTypeGPIOInput(GPIOD, GPIO_PIN_0);
}



/******************************************************************************
  * ������  Button_Scan()
  * ������  ����ɨ����򣬰��������ȼ�
  * ����ֵ����
  *	����ֵ�����ر����µİ������
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
  * ������ Button_J1()
  * ������  �Ӱ������򣬸���Label����ѡȡ��������ʱֵ
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void Button_J1(){
	switch(Label){

	case 0:	T_temp=T_temp+5;				//���Ӹ����¶�
			Flag=0;							//��Flag=0��Ϊ����ģʽ���翾�䲻����
			WriteNum(4,0,T_temp);			//������Ļ�ϵ�ֵ
			if(T_temp<100){
				WriteChar(5,0,32);			//��ֹԽ��ʱ��ʾ����32Ϊ0��ASCII��
			}break;

	case 1:P_temp=P_temp+0.05;Flag=0;WriteFloat(1,2,P_temp);break;
	case 2:I_temp=I_temp+0.05;Flag=0;WriteFloat(5,2,I_temp);break;
	case 3:D_temp=D_temp+0.05;Flag=0;WriteFloat(1,3,D_temp);break;
	default:break;
	}
}



/******************************************************************************
  * ������ Button_J2()
  * ������   �Ӱ������򣬸���Label����ѡȡ����
  * ����ֵ����
  *	����ֵ����
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
  * ������  Button_J3()
  * ������  ȷ��������������֮ǰ���ĵ���ʱֵ����PID�ṹ�壬��ģʽΪ����ģʽ
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void Button_J3(){
	Flag=1;
	T_set=T_temp;WriteNum(4,0,T_set);
	pid.Kp=P_temp;WriteFloat(1,2,pid.Kp);
	pid.Ti=I_temp;WriteFloat(5,2,pid.Ti);
	pid.Td=D_temp;WriteFloat(1,3,pid.Td);
	//�������
	UARTprintf("--------���Ĳ���Ϊ-------\n");
	UARTprintf("P��%d.%02d    \n",(int)pid.Kp,(int)((pid.Kp-(int)pid.Kp)*100));
	UARTprintf("I��%d.%02d    \n",(int)pid.Ti,(int)((pid.Ti-(int)pid.Ti)*100));
	UARTprintf("D��%d.%02d    \n",(int)pid.Td,(int)((pid.Td-(int)pid.Td)*100));
	UARTprintf("��ǰ����ֵ��%d    \n",T_set);
}



/******************************************************************************
  * ������ Button_J4()
  * ������  �л���������������Labelֵ��0-4ѭ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void Button_J4(){
	Flag=0;
	Label++;
	if(Label>3){
		Label=0;
	}

}


/******************************************************************************
  * ������  Button_run()
  * ������  ����ɨ����ִ�а�������
  * ����ֵ����
  *	����ֵ����
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

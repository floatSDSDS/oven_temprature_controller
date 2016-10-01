/*
 * Timer.c
 *
 *  Created on: 2015��8��24��
 *      Author: Administrator
 */

#define TIMER_C_

#include "Timer.h"
#include "led.h"
#include "Button.h"
#include "ADC.h"
#include "LCM.h"

/******************************************************************************
  * ������  TIMER_Init()
  * ������  ��ʱ����ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/

void TIMER_Init()
{

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); 	//ʹ�����趨ʱ��
	 TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);//��TIMER0B����Ϊ16λ���ڶ�ʱ��
	 TimerLoadSet(TIMER0_BASE, TIMER_B,10000000/1000);            //��������
	 IntMasterEnable();
	 TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT); //ʹ��TIMER����ж�
	 IntEnable(INT_TIMER0B);  							//ʹ�ܴ�������TIMER0B�ж�
	 TimerEnable(TIMER0_BASE, TIMER_B); 				//��TIMER0B

	 Flag=0;
	 TimerCounter = 5;
	 TimerIntFlag = UnInterrupt;
}



/******************************************************************************
  * ������  TIMER0B_Handler()
  * ������  ��ʱ���жϺ���
  * ����ֵ����
  *	����ֵ����
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
					speeda=PID_realize(settemp1,temp);					//�õ�ƫ��
					ton = (int)speeda*36;
					TimerCounter = 0;
					}
				Vout=ADC_SampleValue();									//��ȡ��������
				temp=5.0/4096*Vout/8000*1000000-427;					//��ȡ��ǰ�¶�
				tempz=(int)temp;										//��ȡ��ǰ�¶���������
				settemp1=T_set;											//������ֵ
				UARTprintf("%d.%02d\n",tempz,(int)((temp-tempz)*100));	//�������
				WriteFloat(4,1,temp);									//��Ļ����
			}
		}
		//���Ƶ翾�俪��
		if(Flag==1){
			if(speeda==100){
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);
			}
			else if(speeda<=0){
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);
			}
			//PWMʵ��
			else{
				if(TimerCounter>ton){
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);
				}
				else{
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);
				}
			}
		}
		TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);  //����жϱ�־
}

/******************************************************************************
  * �ļ��� main.c
  * ���ߣ�
  * ���ڣ� 2015��07-02
  * �汾�� 1.0
  * ˵���� ʵ��������󰴼�����ʵ��
  *
  ******************************************************************************/

#include "system.h"  //��ͷ�ļ�
#include "device.h"  //����ͷ�ļ�



int main(void)
{
	/*1.System Init*/
	SysClock_Init();    //10MHZ
	/*2.Device Init*/
	//һ�����ʼ��
	LED_Init();			//LED��ʼ��
	TIMER_Init();		//��ʱ����ʼ��
	Button_Init();		//����gpio�ڳ�ʼ��
	ADC_Init();			//AD590��ʼ��
	init_12864IO();
	init_12864();		//LCD��Ļ��ʼ��
	PID_Init() ;		//ΪPID�ṹ�帳��ֵ
	UART_Init();		//���ڳ�ʼ��

	//��֤�翾����һ�����ŵĵ翾��
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);


	//����һյ״̬��
	LED_On();

	//ΪLCD��Ļ��ʼ״̬��ֵ
	WriteStr(0,0,"�����¶�");
	WriteNum(4,0,T_set);
	WriteStr(0,1,"��ǰ�¶�");
	WriteStr(0,2,"P:");
	//����Ļ��ת�����������
	WriteFloat(1,2,pid.Kp);
	WriteStr(4,2,"I:");
	WriteFloat(5,2,pid.Ti);
	WriteStr(0,3,"D:");
	WriteFloat(1,3,pid.Td);

	//���ڴ�ӡ�����ʼ
	UARTprintf("--------¯��PID���Կ�ʼ-------\n");
//	UARTprintf("P��%d.%02d    \n",(int)pid.Kp,(int)((pid.Kp-(int)pid.Kp)*100));
//	UARTprintf("I��%d.%02d    \n",(int)pid.Ti,(int)((pid.Ti-(int)pid.Ti)*100));
//	UARTprintf("D��%d.%02d    \n",(int)pid.Td,(int)((pid.Td-(int)pid.Td)*100));
//	UARTprintf("��ǰ����ֵ��%d    \n",T_set);
	while(1){
	}

}

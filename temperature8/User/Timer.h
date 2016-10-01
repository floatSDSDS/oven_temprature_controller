/*
 * Timer.h
 *
 *  Created on: 2015��8��24��
 *      Author: Administrator
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "system.h"
#include "device.h"

#ifdef TIMER_C_

	#define TIMER_C_Extern

#else

	#define TIMER_C_Extern  extern

#endif


//�жϱ�־
#define Interrupt   1
#define UnInterrupt 0


//volatile uint16_t TimerCounter;

//һ����ȫ�ֱ���
TIMER_C_Extern volatile uint32_t TimerCounter;			//��ʱ��������
TIMER_C_Extern volatile uint8_t TimerIntFlag;			//��ʱ���жϱ�־
TIMER_C_Extern volatile uint8_t Flag;					//����ģʽ/����ģʽ�л���־
TIMER_C_Extern volatile uint8_t Label;					//�������ı�ǩ
TIMER_C_Extern volatile uint32_t Vout;					//AD���������ѹ
TIMER_C_Extern volatile float temp;						//��ǰ�¶�
TIMER_C_Extern volatile uint32_t  ui32SysClock;			//ϵͳʱ��
TIMER_C_Extern int tempz;								//��ǰ�¶���������
TIMER_C_Extern int tempd;								//
TIMER_C_Extern int settemp1;							//����ֵ
TIMER_C_Extern int T_set;								//�����¶ȵ��趨ֵ
TIMER_C_Extern int T_temp;								//�����¶ȵĵ���ֵ
TIMER_C_Extern char tempc[20];							//
TIMER_C_Extern volatile float speeda;					//PID���������ֵ
TIMER_C_Extern int ton;									//ռ�ձ��п������ʱ��



TIMER_C_Extern float P_temp;							//Kp����ֵ
TIMER_C_Extern float I_temp;							//Ki����ֵ
TIMER_C_Extern float D_temp;							//Kd����ֵ


TIMER_C_Extern int pidbz;


//������ʵ��һ��ȫ��pid�ṹ��
TIMER_C_Extern struct _pid{
	float SetSpeed;
	float ActualSpeed;
	float err;
	float err_max;
	float err_next;
	float err_last;
	float integral;
	float integral_max;
	float voltage;
	float zuizhong;
	float Kp,Ti,Td;
}pid;


/* Private function prototypes -----------------------------------------------*/
void TIMER_Init(void);



#endif /* TIMER_H_ */

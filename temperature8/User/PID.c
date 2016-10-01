/*
 * PID.c
 *
 *  Created on: 2016��7��5��
 *      Author: floatSD
 */

#include "PID.h"
#include "Timer.h"


/******************************************************************************
  * ������ PID_Init()
  * ������  PID��ʼ����Ϊpid�ṹ���һЩ������������ֵ
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void PID_Init()
{
	pid.err=0.0;
	pid.err_max=10.0;
	pid.err_next=0.0;
	pid.Kp=1.4;
	pid.Ti=7;
	pid.Td=0;
	pid.integral=0;
	pid.integral_max = 150;
	pid.zuizhong=0;
	pid.voltage=0;
	pidbz=0;
	T_set=60;
	T_temp=T_set;
	P_temp=pid.Kp;
	I_temp=pid.Ti;
	D_temp=pid.Td;
}

/******************************************************************************
  * ������ PID_realize(float speed,float tempe)
  * ������ ����PIDֵ���
  * ����ֵ��float speed,float tempe
  *	����ֵ����
  ******************************************************************************/
float PID_realize(float speed,float tempe){ // PID�������������
	pid.SetSpeed=speed;
	pid.ActualSpeed=tempe;
	pid.err = pid.SetSpeed - pid.ActualSpeed;
	pid.integral+=pid.err;
	uint8_t th1=25;
	uint8_t th2=5;

	float incrementTemp;
//�޷���ֹ���ֱ���
	if(pid.integral>pid.integral_max)
	{
		pid.integral = pid.integral_max;
	}
	if(pid.integral<0)
	{
		pid.integral = 0;
	}
//����֣����������
	if((pid.err>0)&&(pid.err<th2))
	{
		incrementTemp = pid.Kp*(pid.err+1/pid.Ti*pid.integral+pid.Td*(pid.err-pid.err_next));
	}
	else if((pid.err>th2)&&(pid.err<th1)){
		incrementTemp = pid.Kp*(pid.err+pid.Td*(pid.err-pid.err_next));
	}
	else if(pid.err>th1)
	{
		incrementTemp=100;
	}
	else if(pid.err < 0)
	{
		incrementTemp = 0;
	}

//	if(incrementTemp < 0)
//	{
//		incrementTemp = 0;
//	}
	if(incrementTemp > 100)
		incrementTemp = 100;

	pid.err_next=pid.err;
	return incrementTemp;
}



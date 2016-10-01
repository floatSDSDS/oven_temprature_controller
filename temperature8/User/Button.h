/*
 * Button.h
 *
 *  Created on: 2016��7��5��
 *      Author: floatSD
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "system.h"

/* Private define-------------------------------------------------------------*/

//�͵�ƽ��ʾ0�����¼�Ҳ�ǵ͵�ƽ����Ҳ��0
#define LOW       0x00
#define KEYPRESS  0X00

/*����ֵ-�뿪�����ϵĶ�Ӧ*/
#define NJ   0   //û�а��¼���
#define J1   1   //����J1
#define J2   2
#define J3   3
#define J4   4

//�����õ��������˿�
#define GPIOP         GPIO_PORTP_BASE
#define GPION         GPIO_PORTN_BASE
#define GPIOD         GPIO_PORTD_BASE

/*�������ģʽ����*/
#define ROW_GPIOP_IN()	 GPIOPinTypeGPIOInput(GPIOP, GPIO_PIN_2)//����PP2Ϊ������
#define ROW_GPION_IN()   GPIOPinTypeGPIOInput(GPION, GPIO_PIN_2|GPIO_PIN_3)
#define ROW_GPIOD_IN()   GPIOPinTypeGPIOInput(GPIOD, GPIO_PIN_0)

void    Button_Init(void);		//������ʼ��
void Button_run();				//ѡ�񰴼���������Ӧ��������
uint8_t Button_Scan(void);		//����ɨ�����
void Button_J1();				//�Ӱ����ĳ���
void Button_J2();				//����������
void Button_J3();				//ȷ����������
void Button_J4();				//�л���������


#endif /* BUTTON_H_ */

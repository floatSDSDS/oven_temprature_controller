/*
 * UART.c
 *
 *  Created on: 2016��7��6��
 *      Author: floatSD
 */

#include "UART.h"
#include "Sys.h"

/******************************************************************************
  * ������ UART_Init()
  * ������ UART���ڳ�ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void UART_Init()
{
    // ����UART0ʹ��PA0,PA1�������ţ������Ҫʹ��GPIOAģ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // ��Ϊ�����Ÿ��ã�����Ҫ��PA0��PA1�������ŵĹ��ܽ���ѡ��
	// ���ｫ����ѡ��Ϊִ��UART0ģ��Ĺ���
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // ����PA0��PA1�������ţ��ڽ�������ΪUART����ʹ��֮ǰ����Ҫ��������һЩ�й�UART������
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, ui32SysClock);
}



/*
 * ADC.c
 *
 *  Created on: 2016��7��5��
 *      Author: floatSD
 */

#include "Sys.h"
#include "ADC.h"
#include "Timer.h"

/******************************************************************************
  * ������  ADC_Init()
  * ������ ADC��ʼ��
  * ����ֵ����
  *	����ֵ����
  ******************************************************************************/
void ADC_Init()
{
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	 GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_7);
	 ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	 ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_END | ADC_CTL_IE);
	 ADCSequenceEnable(ADC0_BASE, 3);
	 ADCIntClear(ADC0_BASE, 3);
}

/******************************************************************************
  * ������  ADC_Sample()
  * ������  ADC��������
  * ����ֵ����
  *	����ֵ��uint32_t��ADC����ֵ��raw��
  ******************************************************************************/
uint32_t ADC_SampleValue()
{
	uint32_t ulADC0_Value;
	ADCProcessorTrigger(ADC0_BASE, 3);
	while(!ADCIntStatus(ADC0_BASE, 3, false)) ;
	ADCSequenceDataGet(ADC0_BASE, 3, &ulADC0_Value);
	SysCtlDelay(50000000/3000);
	return ulADC0_Value;
}



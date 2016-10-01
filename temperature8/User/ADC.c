/*
 * ADC.c
 *
 *  Created on: 2016年7月5日
 *      Author: floatSD
 */

#include "Sys.h"
#include "ADC.h"
#include "Timer.h"

/******************************************************************************
  * 函数：  ADC_Init()
  * 描述： ADC初始化
  * 输入值：无
  *	返回值：无
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
  * 函数：  ADC_Sample()
  * 描述：  ADC采样函数
  * 输入值：无
  *	返回值：uint32_t型ADC采样值（raw）
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



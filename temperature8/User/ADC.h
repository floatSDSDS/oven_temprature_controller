/*
 * ADC.h
 *
 *  Created on: 2016��7��5��
 *      Author: floatSD
 */

#ifndef ADC_H_
#define ADC_H_

#include "system.h"

volatile  uint8_t ADC0_HandlerFlag;


//ΪADC��ʼ��
void ADC_Init(void);

//����ADC����ֵ
uint32_t ADC_SampleValue(void);


#endif /* ADC_H_ */

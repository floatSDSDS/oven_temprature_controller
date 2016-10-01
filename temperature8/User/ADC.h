/*
 * ADC.h
 *
 *  Created on: 2016年7月5日
 *      Author: floatSD
 */

#ifndef ADC_H_
#define ADC_H_

#include "system.h"

volatile  uint8_t ADC0_HandlerFlag;


//为ADC初始化
void ADC_Init(void);

//返回ADC采样值
uint32_t ADC_SampleValue(void);


#endif /* ADC_H_ */

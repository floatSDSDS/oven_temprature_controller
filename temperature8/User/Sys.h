/*
 * Sys.h
 *
 *  Created on: 2015��7��2��
 *      Author: Administrator
 */

#ifndef SYS_H_
#define SYS_H_

#include "system.h"

/* Private define-------------------------------------------------------------*/
#define OSC_10MHZ     10000000

volatile uint32_t  ui32SysClock;


/* Private function prototypes -----------------------------------------------*/
void SysClock_Init();
void DelayMs(uint32_t CountMs);





#endif /* SYS_H_ */

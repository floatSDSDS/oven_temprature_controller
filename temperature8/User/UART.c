/*
 * UART.c
 *
 *  Created on: 2016年7月6日
 *      Author: floatSD
 */

#include "UART.h"
#include "Sys.h"

/******************************************************************************
  * 函数： UART_Init()
  * 描述： UART串口初始化
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void UART_Init()
{
    // 由于UART0使用PA0,PA1两个引脚，因此需要使能GPIOA模块
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // 因为有引脚复用，所以要对PA0和PA1两个引脚的功能进行选择
	// 这里将它们选择为执行UART0模块的功能
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // 对于PA0和PA1两个引脚，在将它们作为UART功能使用之前，需要对它们做一些有关UART的配置
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, ui32SysClock);
}



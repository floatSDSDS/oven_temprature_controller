/*
 * Sys.c
 *
 *  Created on: 2015年7月2日
 *      Author: Administrator
 */

#ifndef SYS_C_
#define SYS_C_

#include "Sys.h"

/******************************************************************************
  * 函数：  SysClock_Init()
  * 描述：  系统时钟初始化
  * 输入值：无
  *	返回值：无
  ******************************************************************************/
void SysClock_Init()
{


	ui32SysClock=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |                   //外部25Mhz晶振源
		                SYSCTL_OSC_MAIN |
		                SYSCTL_USE_PLL |
		                SYSCTL_CFG_VCO_480), OSC_10MHZ);      //设置系统时间为10MHZ
}





/******************************************************************************
  * 函数：  DelayMs()
  * 描述：  系统时钟初始化
  * 输入值：CountMs -> Ms计数值
  *	返回值：无
  ******************************************************************************/
void DelayMs(uint32_t CountMs)
{
	/*说明：SysCtlDelay(SysCtlClockGet()/3000)
	 *这个函数执行的结果就是延时1ms,
	 *无论你的系统时钟是多少,
	 *当然你的系统时钟是不能低于3K的。
	 *SysCtlClockGet()函数返回的值是系统的频率，
	 *也就是1S钟的CLOCK个数，
	 *这个个数/1000就是1ms系统时钟的个数，
	 *由于SysCtlDelay函数一个循环判断执行需要3个CLOCK时钟，
	 *所以系统时钟/3000就表示系统执行1ms的时间。
	 *由此可以看出这个函数执行的结果就是延迟1ms.
	 *在不同的系统时钟下，调用该函数都是延迟1ms.*/

	SysCtlDelay(CountMs*(OSC_10MHZ/3000));


}




#endif /* SYS_C_ */

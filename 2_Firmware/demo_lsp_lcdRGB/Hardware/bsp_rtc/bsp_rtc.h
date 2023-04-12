#ifndef _BSP_RTC_H
#define _BSP_RTC_H

#include "define.h"


#define RTC_CLOCK_SOURCE_LXTAL 
//#define RTC_CLOCK_SOURCE_IRC32K 


#define BKP_VALUE    0x32F1


void bsp_rtc_config(void );
void rtc_show_time(void);
#endif



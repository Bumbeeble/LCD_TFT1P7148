#ifndef	_DEFINE_H_
#define	_DEFINE_H_

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "bsp_led.h"
#include "bsp_usart.h"


//#define _DEBUG_ALL

#ifdef _DEBUG_ALL

    #define _DEBUG_LED
    #define _DEBUG_MAIN
    #define _DEBUG_UART1
    #define _DEBUG_KEY
    #define _DEBUG_HALL
    #define _DEBUG_PMU
    #define _DEBUG_SY8815
    #define _DEBUG_ADC
    #define _DEBUG_SLEEP
    #define _DEBUG_WIRELESSCHARGE
#endif

#endif



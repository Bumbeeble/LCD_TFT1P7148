/*!
    \file    systick.c
    \brief   the systick configuration file

    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
    \version 2020-09-30, V2.1.0, firmware for GD32F4xx
    \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx.h"
#include "systick.h"

volatile static uint32_t delay;

/*!
    \brief    configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if(SysTick_Config(SystemCoreClock / 1000U)) {
        /* capture error */
        while(1) {
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/*!
    \brief    delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count)
{
    delay = count;

    while(0U != delay) {
    }
}


bool F_systick = false;

bool F_tim_1ms = false;
bool F_tim_10ms = false;
bool F_tim_100ms = false;
bool F_tim_1s = false;
bool F_tim_250ms = false;

uint8_t cnt_tim_10ms = 0;
uint8_t cnt_tim_100ms = 0;
uint8_t cnt_tim_1s = 0;

uint8_t cnt_tim_250ms = 0;

#define C_cnt_tim_10ms  10
#define C_cnt_tim_100ms  100
#define C_cnt_tim_1s  10

#define C_cnt_tim_250ms  250

void systick_handler(void )
{
    if(!F_systick)
    {
        return;
    }
    F_systick = false;


    F_tim_1ms = true;
    cnt_tim_10ms++;
    if(cnt_tim_10ms >= C_cnt_tim_10ms)
    {
        cnt_tim_10ms = 0;
        F_tim_10ms = true;
    }
    cnt_tim_250ms++;
    if(cnt_tim_250ms >= C_cnt_tim_250ms)
    {
        cnt_tim_250ms = 0;
        F_tim_250ms = true;
    }
    cnt_tim_100ms++;
    if(cnt_tim_100ms >= C_cnt_tim_100ms)
    {
        cnt_tim_100ms = 0;
        F_tim_100ms = true;
        
        cnt_tim_1s++;
        if(cnt_tim_1s >= C_cnt_tim_1s)
        {
            cnt_tim_1s = 0;
            F_tim_1s = true;
        }

    }



}

/*!
    \brief    delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    F_systick = true;
    if(0U != delay) 
    {
        delay--;
    }
}

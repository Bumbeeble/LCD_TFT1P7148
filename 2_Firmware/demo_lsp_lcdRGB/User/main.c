/*!
    \file    main.c
    \brief   led spark with systick

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


#include "main.h"
#include "bsp_key.h"
#include "bsp_rtc.h"

#include "exmc_sdram.h"
#include "lcd.h"
//#include "cat.h"

//#include "cat.h"
#include "tree1.h"
/*!
    \brief    main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    rtc_parameter_struct   rtc_initpara;
    char buf[100];
    systick_config();
    led_gpio_config();
    usart_gpio_config(115200U);
    key_config();
	bsp_rtc_config();
    
        //RGB屏需要Gram
    exmc_synchronous_dynamic_ram_init(EXMC_SDRAM_DEVICE0);
    /* RGB屏 */
    LCD_Init(); //显示屏初始化代码
    
    POINT_COLOR=YELLOW;
    BACK_COLOR=BLACK;
    LCD_Clear(1,BLACK);
    LCD_ShowString(1,300,0,200,20,24,1,"https://lckfb.com");
    LCD_ShowString(1,250,20,200,20,24,1,"https://lckfb.com");
    LCD_ShowString(1,200,40,200,20,12,1,"https://lckfb.com");
    LCD_ShowString(1,0,60,200,20,24,1,"https://lckfb.com");
    LCD_ShowString(1,0,90,560,20,24,1,"https://lckfb.com");
    LCD_ShowString(1,0,110,200,20,24,1,"https://lckfb.com");
    LCD_ShowString(1,0,450,450,20,16,1,"450x450");
    LCD_ShowString(1,0,400,400,20,24,1,"400x400");
//    LTDC_Draw_Point(1,0, 0,RED);
//    LTDC_Draw_Point(1,10, 1,RED);
//    LTDC_Draw_Point(1,1, 10,RED);
//    LTDC_Draw_Point(1,300, 450,RED);
//    LTDC_Draw_Point(1,100, 100,RED);
    //LCD_draw_colorgradation(1,0, 0);
        // LCD_ShowPicture(1,200,50,240,240,(uint16_t *)gImage_draw);
       LCD_ShowPicture(1,200,10,240,180,(uint16_t *)gImage_tree1);
//        LCD_DrawCircle(100, 200, 70, 0xC000);
//        LCD_DrawCircle(100, 200, 80, 0x0018);
//        
//        LCD_DrawCircle(350, 200, 30, 0x7000);
//        LCD_DrawCircle(350, 200, 40, 0x8000);
//        LCD_DrawCircle(350, 200, 50, 0x9000);
    while(1) 
    {
        systick_handler();
        usart_handler();
        if(F_tim_1ms)
        {
            F_tim_1ms = false;
            key_handler();
        }
        if(F_tim_10ms)
        {
            F_tim_10ms = false;
        }
        if(F_tim_100ms)
        {
            F_tim_100ms = false;
        }
        if(F_tim_1s)
        {
            F_tim_1s = false;
            //printf("Hello world\n");
            //led1_run();
//            led1_set(0);
//            led2_run();
//            led3_run();
//            led4_run();
            
            LED2_ON();
            LED3_RUN();
            LED4_OFF();
            LED1_RUN();
//            rtc_current_time_get(&rtc_initpara);  
//            sprintf(buf,"Current date: %0.2x:%0.2x:%0.2x\n\r", \
//                  rtc_initpara.year, rtc_initpara.month, rtc_initpara.date);
//    LCD_ShowString(1,0,10,300,200,24,0,(uint8_t *)buf);
//            sprintf(buf,"Current time: %0.2x:%0.2x:%0.2x\n\r", \
//                  rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
//            
//    LCD_ShowString(1,0,100,300,200,24,0,(uint8_t *)buf);
//            rtc_show_time();
            
        }
    }
}

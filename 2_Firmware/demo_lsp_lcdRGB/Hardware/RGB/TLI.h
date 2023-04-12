#ifndef _TLI_H
#define _TLI_H


#include "gd32f4xx.h"
#include "systick.h"


//#define LCD_800X4800
#ifdef LCD_800X4800
//    #define HORIZONTAL_SYNCHRONOUS_PULSE  10
//    #define HORIZONTAL_BACK_PORCH         150
//    #define ACTIVE_WIDTH                  800
//    #define HORIZONTAL_FRONT_PORCH        40

//    #define VERTICAL_SYNCHRONOUS_PULSE    10
//    #define VERTICAL_BACK_PORCH           140
//    #define ACTIVE_HEIGHT                 480
//    #define VERTICAL_FRONT_PORCH          15

    #define HORIZONTAL_SYNCHRONOUS_PULSE  10
    #define HORIZONTAL_BACK_PORCH         140
    #define ACTIVE_WIDTH                  800
    #define HORIZONTAL_FRONT_PORCH        15

    #define VERTICAL_SYNCHRONOUS_PULSE    10
    #define VERTICAL_BACK_PORCH           150
    #define ACTIVE_HEIGHT                 480
    #define VERTICAL_FRONT_PORCH          40
    
#else


    #define HORIZONTAL_SYNCHRONOUS_PULSE  10
    #define HORIZONTAL_BACK_PORCH         150
    #define ACTIVE_WIDTH                  480
    #define HORIZONTAL_FRONT_PORCH        40

    #define VERTICAL_SYNCHRONOUS_PULSE    10
    #define VERTICAL_BACK_PORCH           140
    #define ACTIVE_HEIGHT                 800
    #define VERTICAL_FRONT_PORCH          15
#endif

//#define HORIZONTAL_SYNCHRONOUS_PULSE  41
//#define HORIZONTAL_BACK_PORCH         2
//#define ACTIVE_WIDTH                  480
//#define HORIZONTAL_FRONT_PORCH        2

//#define VERTICAL_SYNCHRONOUS_PULSE    10
//#define VERTICAL_BACK_PORCH           2
//#define ACTIVE_HEIGHT                 272
//#define VERTICAL_FRONT_PORCH          2


// #define HORIZONTAL_SYNCHRONOUS_PULSE  10
// #define HORIZONTAL_BACK_PORCH         70
// #define ACTIVE_WIDTH                  480
// #define HORIZONTAL_FRONT_PORCH        40

// #define VERTICAL_SYNCHRONOUS_PULSE    10
// #define VERTICAL_BACK_PORCH           50
// #define ACTIVE_HEIGHT                 800
// #define VERTICAL_FRONT_PORCH          15


// #define HORIZONTAL_SYNCHRONOUS_PULSE  10
// #define HORIZONTAL_BACK_PORCH         20
// #define ACTIVE_WIDTH                  480
// #define HORIZONTAL_FRONT_PORCH        40

// #define VERTICAL_SYNCHRONOUS_PULSE    10
// #define VERTICAL_BACK_PORCH           10
// #define ACTIVE_HEIGHT                 800
// #define VERTICAL_FRONT_PORCH          15

// #define HORIZONTAL_SYNCHRONOUS_PULSE  10
// #define HORIZONTAL_BACK_PORCH         20
// #define ACTIVE_WIDTH                  480
// #define HORIZONTAL_FRONT_PORCH        40

// #define VERTICAL_SYNCHRONOUS_PULSE    15
// #define VERTICAL_BACK_PORCH           10
// #define ACTIVE_HEIGHT                 800
// #define VERTICAL_FRONT_PORCH          2


/* ±³¹â PD13 */

/* ´¥Ãþ 
SCL  PB6
SDA	 PB7
INT  PD11
RST  PD12
*/

//#define LED1_RCU  RCU_GPIOD
//#define LED1_PORT  GPIOD
//#define LED1_PIN    GPIO_PIN_7
//#define LED1_ON			gpio_bit_set(LED1_PORT,LED1_PIN);
//#define LED1_OFF			gpio_bit_reset(LED1_PORT,LED1_PIN);
//#define LED1_TOGGLE	gpio_bit_toggle(LED1_PORT,LED1_PIN);




void LTDC_Draw_Point(uint8_t layer, uint16_t x, uint16_t y, uint32_t color);

void TLI_config(void);
void TLI_ConfigParam( 
int b_HORIZONTAL_SYNCHRONOUS_PULSE,
int b_HORIZONTAL_BACK_PORCH       ,
int b_HORIZONTAL_FRONT_PORCH      ,
int b_VERTICAL_SYNCHRONOUS_PULSE  ,
int b_VERTICAL_BACK_PORCH         ,
int b_VERTICAL_FRONT_PORCH        );

#endif

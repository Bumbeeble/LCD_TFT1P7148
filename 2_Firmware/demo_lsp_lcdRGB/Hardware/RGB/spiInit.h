#ifndef _SPIINIT_H
#define _SPIINIT_H


#include "gd32f4xx.h"
#include "systick.h"

/* SPIÒý½Å 
SDA  PC13  
SDI  PC1
SCL	 PD5
CS   PG12
RST  PD12
*/

#define LCD_SDA_RCU  			RCU_GPIOE   // SDA
#define LCD_SDA_PORT  		    GPIOE
#define LCD_SDA_PIN    		    GPIO_PIN_6//GPIO_PIN_5  //v0.0.1新屏幕6，老屏幕5
#define LCD_SDA_WRITE(x)	    gpio_bit_write(LCD_SDA_PORT,LCD_SDA_PIN,x)

#define LCD_SCL_RCU  			RCU_GPIOE   // SCL
#define LCD_SCL_PORT  		    GPIOE
#define LCD_SCL_PIN    		    GPIO_PIN_2
#define LCD_SCL_WRITE(x)	    gpio_bit_write(LCD_SCL_PORT,LCD_SCL_PIN,x)

#define LCD_CS_RCU  			RCU_GPIOE   // CS
#define LCD_CS_PORT  		    GPIOE
#define LCD_CS_PIN    		    GPIO_PIN_4
#define LCD_CS_WRITE(x)	        gpio_bit_write(LCD_CS_PORT,LCD_CS_PIN,x)

#define LCD_RST_RCU  			RCU_GPIOD   // RST
#define LCD_RST_PORT  		    GPIOD
#define LCD_RST_PIN    		    GPIO_PIN_12
#define LCD_RST_WRITE(x)	    gpio_bit_write(LCD_RST_PORT,LCD_RST_PIN,x)

//#define LCD_BLK PBout(1)	// DS0 
#define LCD_BLK_ON              gpio_bit_set(GPIOD,GPIO_PIN_13)	// PD13
#define LCD_BLK_OFF             gpio_bit_reset(GPIOD,GPIO_PIN_13)	// PD13

#define LCD_CS_Clr()            gpio_bit_reset(GPIOE,GPIO_PIN_4)	// PD13
#define LCD_CS_Set()            gpio_bit_set(GPIOE,GPIO_PIN_4)	// PD13

#define LCD_SDI_RCU  			RCU_GPIOC   // SDI
#define LCD_SDI_PORT  		    GPIOC
#define LCD_SDI_PIN    		    GPIO_PIN_1
#define LCD_SDI_WRITE(x)	    gpio_bit_write(LCD_SDI_PORT,LCD_SDI_PIN,x)

void NT35510_Init(void);


#endif
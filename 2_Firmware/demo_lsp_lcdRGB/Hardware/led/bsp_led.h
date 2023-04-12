#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "define.h"

#ifdef _DEBUG_LED
    #define _DEBUG_LED1
    #define _DEBUG_LED2
    #define _DEBUG_LED3
    #define _DEBUG_LED4
#endif

#define RCU_led1    RCU_GPIOE
#define PORT_led1   GPIOE
#define PIN_led1    GPIO_PIN_3
#define PIN_led1    GPIO_PIN_3
#define LEVEL_led1  1
#define led1_config()   do{rcu_periph_clock_enable(RCU_led1);\
                            gpio_mode_set(PORT_led1,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,PIN_led1);\
                            gpio_output_options_set(PORT_led1,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,PIN_led1);\
                            }while(0)
#define led1_run()   do{gpio_bit_toggle(PORT_led1, PIN_led1);}while(0)
#define led1_set(x) do{x?(gpio_bit_set(PORT_led1, PIN_led1)):(gpio_bit_reset(PORT_led1, PIN_led1));}while(0)

#define RCU_led2    RCU_GPIOD
#define PORT_led2   GPIOD
#define PIN_led2    GPIO_PIN_7
#define LEVEL_led2  1
#define led2_config()   do{rcu_periph_clock_enable(RCU_led2);\
                            gpio_mode_set(PORT_led2,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,PIN_led2);\
                            gpio_output_options_set(PORT_led2,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,PIN_led2);\
                            }while(0)
#define led2_run()   do{gpio_bit_toggle(PORT_led2, PIN_led2);}while(0)
#define led2_set(x) do{x?(gpio_bit_set(PORT_led2, PIN_led2)):(gpio_bit_reset(PORT_led2, PIN_led2));}while(0)


#define RCU_led3    RCU_GPIOG
#define PORT_led3   GPIOG
#define PIN_led3    GPIO_PIN_3
#define LEVEL_led3  1
#define led3_config()   do{rcu_periph_clock_enable(RCU_led3);\
                            gpio_mode_set(PORT_led3,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,PIN_led3);\
                            gpio_output_options_set(PORT_led3,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,PIN_led3);\
                            }while(0)
#define led3_run()   do{gpio_bit_toggle(PORT_led3, PIN_led3);}while(0)
#define led3_set(x) do{x?(gpio_bit_set(PORT_led3, PIN_led3)):(gpio_bit_reset(PORT_led3, PIN_led3));}while(0)


#define RCU_led4    RCU_GPIOA
#define PORT_led4   GPIOA
#define PIN_led4    GPIO_PIN_5
#define LEVEL_led4  1
#define led4_config()   do{rcu_periph_clock_enable(RCU_led4);\
                            gpio_mode_set(PORT_led4,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,PIN_led4);\
                            gpio_output_options_set(PORT_led4,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,PIN_led4);\
                            }while(0)
#define led4_run()   do{gpio_bit_toggle(PORT_led4, PIN_led4);}while(0)
#define led4_set(x) do{x?(gpio_bit_set(PORT_led4, PIN_led4)):(gpio_bit_reset(PORT_led4, PIN_led4));}while(0)



#ifdef _DEBUG_LED1
    #define		LED1(x)	    do{}while(0)
    #define		LED1_ON()	    do{}while(0)
    #define		LED1_OFF()	    do{}while(0)
    #define		LED1_RUN()	    do{}while(0)

    #define		_LED1(x)	    do{led1_set(x);}while(0)
    #define		_LED1_RUN()	do{led1_run();}while(0)
    #define		_LED1_ON()	    do{_LED1(LEVEL_led1);}while(0)
    #define		_LED1_OFF()	do{_LED1(!LEVEL_led1);;}while(0)
#else
    #define		_LED1(x)	    do{}while(0)
    #define		_LED1_ON()	    do{}while(0)
    #define		_LED1_OFF()	    do{}while(0)
    #define		_LED1_RUN()	    do{}while(0)

    #define		LED1(x)	        do{led1_set(x);}while(0)
    #define		LED1_RUN()	    do{led1_run();}while(0)
    #define		LED1_ON()	    do{LED1(LEVEL_led1);}while(0)
    #define		LED1_OFF()	    do{LED1(!LEVEL_led1);;}while(0)
#endif

#ifdef _DEBUG_LED2
    #define		LED2(x)	        do{}while(0)
    #define		LED2_ON()	    do{}while(0)
    #define		LED2_OFF()	    do{}while(0)
    #define		LED2_RUN()	    do{}while(0)

    #define		_LED2(x)	    do{led2_set(x);}while(0)
    #define		_LED2_RUN()	    do{led2_run();}while(0)
    #define		_LED2_ON()	    do{_LED2(LEVEL_led2);}while(0)
    #define		_LED2_OFF()	    do{_LED2(!LEVEL_led2);;}while(0)
#else
    #define		_LED2(x)	    do{}while(0)
    #define		_LED2_ON()	    do{}while(0)
    #define		_LED2_OFF()	do{}while(0)
    #define		_LED2_RUN()	do{}while(0)

    #define		LED2(x)	    do{led2_set(x);}while(0)
    #define		LED2_RUN()	    do{led2_run();}while(0)
    #define		LED2_ON()	    do{LED2(LEVEL_led2);}while(0)
    #define		LED2_OFF()	    do{LED2(!LEVEL_led2);;}while(0)
#endif


#ifdef _DEBUG_LED3
    #define		LED3(x)	    do{}while(0)
    #define		LED3_ON()	    do{}while(0)
    #define		LED3_OFF()	    do{}while(0)
    #define		LED3_RUN()	    do{}while(0)

    #define		_LED3(x)	    do{led3_set(x);}while(0)
    #define		_LED3_RUN()	do{led3_run();}while(0)
    #define		_LED3_ON()	    do{_LED3(LEVEL_led3);}while(0)
    #define		_LED3_OFF()	do{_LED3(!LEVEL_led3);;}while(0)
#else
    #define		_LED3(x)	    do{}while(0)
    #define		_LED3_ON()	    do{}while(0)
    #define		_LED3_OFF()	do{}while(0)
    #define		_LED3_RUN()	do{}while(0)

    #define		LED3(x)	    do{led3_set(x);}while(0)
    #define		LED3_RUN()	    do{led3_run();}while(0)
    #define		LED3_ON()	    do{LED3(LEVEL_led3);}while(0)
    #define		LED3_OFF()	    do{LED3(!LEVEL_led3);;}while(0)
#endif


#ifdef _DEBUG_LED4
    #define		LED4(x)	    do{}while(0)
    #define		LED4_ON()	    do{}while(0)
    #define		LED4_OFF()	    do{}while(0)
    #define		LED4_RUN()	    do{}while(0)

    #define		_LED4(x)	    do{led4_set(x);}while(0)
    #define		_LED4_RUN()	do{led4_run();}while(0)
    #define		_LED4_ON()	    do{_LED4(LEVEL_led4);}while(0)
    #define		_LED4_OFF()	do{_LED4(!LEVEL_led4);;}while(0)
#else
    #define		_LED4(x)	    do{}while(0)
    #define		_LED4_ON()	    do{}while(0)
    #define		_LED4_OFF()	do{}while(0)
    #define		_LED4_RUN()	do{}while(0)

    #define		LED4(x)	    do{led4_set(x);}while(0)
    #define		LED4_RUN()	    do{led4_run();}while(0)
    #define		LED4_ON()	    do{LED4(LEVEL_led4);}while(0)
    #define		LED4_OFF()	    do{LED4(!LEVEL_led4);;}while(0)
#endif
void led_gpio_config(void);

#endif


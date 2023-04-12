#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "define.h"

#define _uartDebug_key_
//#define _KEY_MULTI_TRIG_



#define RCU_key0   RCU_GPIOA
#define PORT_key0  GPIOA
#define PIN_key0   GPIO_PIN_0
#define _io_init_key0()  do{ rcu_periph_clock_enable(RCU_key0);\
                                gpio_mode_set(PORT_key0,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,PIN_key0);\
                            }while(0)
//normal 1, valid : 0
#define _readIO_key0()	(!gpio_input_bit_get(PORT_key0,PIN_key0))


#define C_Button_Debounce_Max	50
typedef enum {OFF = 0, ON = !OFF} keystatus;
typedef enum{
    Button0 = 0,
    Button_max
}def_key_num;

typedef enum {
    key_event_Empty = 0x00,
    key_event_1click = 0x01,
    key_event_2click = 0x02,
    key_event_3click = 0x03,
    key_event_4click = 0x04,
    key_event_5click = 0x05,
    key_event_6click = 0x06,
    key_event_Press_L = 0x11,
    key_event_Press_LL = 0x12,
    key_event_Press_LLL = 0x13
    
}def_key_event;

#define C_key_cnt_muitiTrig_Max	10			//Max key trig
#define C_key_decnt_Tim_MultiTrig_Set	500		//200ms for key trig


#define C_key_cnt_Press_Valid 500		//500ms
#define C_key_cnt_Press_L 2*1000		    //2s
#define C_key_cnt_Press_LL 10*1000		//10s
#define C_key_cnt_Press_LLL 30*1000      //30s
#define C_key_cnt_Press_MAX 60*1000      //30s

typedef struct{
    //
    bool status;
    bool trig;
    def_key_event event;
    bool trigMsg;
    uint8_t cnt_multiTrig;
    uint16_t decnt_tim_multiTrig;
    uint16_t cnt_tim_keyDown;
    bool F_PressTrig;
    
    
}def_key_msg;


extern def_key_msg key_msg[Button_max];
void key_io_init(void );
void key_config(void);

void key_handler(void);
keystatus Get_Button_Trg(uint8_t );
void Clear_Button_Trg(uint8_t );
keystatus Get_Button_Status(uint8_t );
keystatus Get_Button_Continue(uint8_t pos);

#endif



#include "bsp_key.h"


def_key_msg key_msg_s __attribute__((at (0x20008000)));

uint8_t cnt_Button = 0;
uint8_t State_Button = 0;
uint8_t State_Button_Before = 0;

uint8_t Real_Button = 0;
uint8_t Trg_Button = 0;					//¦Ì£¤?¡Â¡ã¡ä?¨¹???¡é
uint8_t Cont_Button = 0;					//¦Ì£¤?¡Â¡ã¡ä?¨¹???¡é

static void check_key_readIO(void);
static void check_key_trig(void);

def_key_msg key_msg[Button_max] = {0};

keystatus Get_Button_Trg(uint8_t pos)
{
	return (keystatus)(Trg_Button&(0x01<<pos));
}

void Clear_Button_Trg(uint8_t pos)
{
	Trg_Button &= ~(0x01<<pos);
}

keystatus Get_Button_Status(uint8_t pos)
{
	return (keystatus)(Real_Button&(0x01<<pos));
}

keystatus Get_Button_Continue(uint8_t pos)
{
	return (keystatus)(Cont_Button&(0x01<<pos));
}


void key_io_init(void )
{
    _io_init_key0();
    //_io_init_key1();
}
/**
  * @brief ¡ã¡ä?¨¹3?¨º??¡¥
  * @param  None
  * @retval None
  */
void key_config(void)
{
    key_io_init();
	check_key_readIO();
	State_Button_Before = State_Button;
	Real_Button = State_Button;
	check_key_trig();
	Trg_Button = 0;
}
/**
  * @brief ?¨¢¨¨?¡ã¡ä?¨¹¡Á¡ä¨¬?
  * @param  None
  * @retval None
  */
static void check_key_readIO(void)
{
//?¨¢¨¨?¡ã¡ä?¨¹¡Á¡ä¨¬?¡ê?¡ã¡ä??¦Ì¨ª¦Ì????a1
	if(_readIO_key0())
		State_Button |= 0x01;
	else
		State_Button &= ~(0x01);
//	if(_readIO_key1())
//		State_Button &= ~(0x01<<1);
//	else
//		State_Button |= 0x01<<1;
	

}

/**
  * @brief ¡ã¡ä?¨¹¡Á¡ä¨¬?????
  * @param  None
  * @retval None
  */
static void check_key_debounce(void)
{
	//msg_ButtonClick = _readIO_key0();
	if(State_Button == State_Button_Before)
	{
		//¡Á¡ä¨¬??¡ä??¡À?
		if(cnt_Button >= C_Button_Debounce_Max)
		{
			//¨º¡À??¦Ì?
			//cnt_Button = 0;
			Real_Button = State_Button;		//¦Ì?¦Ì??¨¨?¡§?¦Ì
		}
		else
		{
			cnt_Button++;		//??¨ºy
		}
	}
	else
	{
		cnt_Button = 0;
		State_Button_Before = State_Button;			//¡ã¡ä?¨¹¡Á¡ä¨¬???¡À?¡ê?¡À¡ê¡ä?¡ã¡ä?¨¹¡Á¡ä¨¬?
//        sleep_cnt_reset();
	}
}

void check_key_msg(void )
{
    uint8_t i = 0;
    for(i=0; i<Button_max; i++)
    {
        //decnt self decrease
        if(key_msg[i].decnt_tim_multiTrig > 0)
        {
            key_msg[i].decnt_tim_multiTrig--;
        }
        key_msg[i].status = Cont_Button & (0x01<<i);
        key_msg[i].trig  = Trg_Button & (0x01<<i);
        
        //check key trig
        if(key_msg[i].trig)
        {
            key_msg[i].trigMsg = true;           //Storage key trig, need user to clear
            
            if(key_msg[i].F_PressTrig)
            {
                key_msg[i].F_PressTrig = 0;
            }
            else
            {
#ifdef _KEY_MULTI_TRIG_
                //get key press trige
                if(key_msg[i].cnt_multiTrig < C_key_cnt_muitiTrig_Max)
                {
                    key_msg[i].cnt_multiTrig++;
                }
                key_msg[i].decnt_tim_multiTrig = C_key_decnt_Tim_MultiTrig_Set;
#else                
                key_msg[i].event = key_event_1click;
                key_msg[i].cnt_multiTrig = 0;
#ifdef _uartDebug_key_
                printf("key%d trige: %dclick\n\r",(uint16_t)i,(uint16_t)key_msg[i].event);                
#endif
                
#endif
            }
        }
        else if(key_msg[i].decnt_tim_multiTrig == 0)
        {
            if((key_msg[i].cnt_multiTrig < C_key_cnt_muitiTrig_Max) && (key_msg[i].cnt_multiTrig > 0))
            {
                //get multiTrig msg
                key_msg[i].event = (def_key_event)key_msg[i].cnt_multiTrig;
                key_msg[i].cnt_multiTrig = 0;
#ifdef _uartDebug_key_
                printf("key%d trige: %dclick\n\r",(uint16_t)i,(uint16_t)key_msg[i].event);                
#endif
            }
            
        }
        
        //check key long press
        if(!(key_msg[i].status))
        {
            //key up
            if(key_msg[i].cnt_tim_keyDown < C_key_cnt_Press_MAX)
            {
                key_msg[i].cnt_tim_keyDown++;
            }
            
            
            if(key_msg[i].cnt_tim_keyDown == C_key_cnt_Press_Valid)
            {
                key_msg[i].F_PressTrig = true;
#ifdef _uartDebug_key_
                printf("key%d trige: valid press--\n\r",(uint16_t)i);                
#endif
            }
            if(key_msg[i].cnt_tim_keyDown == C_key_cnt_Press_L)
            {
                key_msg[i].event = key_event_Press_L;
#ifdef _uartDebug_key_
                printf("key%d trige: L press--\n\r",(uint16_t)i);                
#endif
            }
            if(key_msg[i].cnt_tim_keyDown == C_key_cnt_Press_LL)
            {
                key_msg[i].event = key_event_Press_LL;
#ifdef _uartDebug_key_
                printf("key%d trige: LL press--\n\r",(uint16_t)i);                
#endif
            }
            if(key_msg[i].cnt_tim_keyDown == C_key_cnt_Press_LLL)
            {
                key_msg[i].event = key_event_Press_LLL;
#ifdef _uartDebug_key_
                printf("key%d trige: LLL press--\n\r",(uint16_t)i);                
#endif
            }
        }
        else
        {
            //key down
            key_msg[i].cnt_tim_keyDown = 0;
            key_msg[i].F_PressTrig = 0;
        }
//        if(key_msg[i].event != key_event_Empty)
//        {
//            printf("key%d event: 0x%02X\r\n", (uint16_t)i,(uint16_t)key_msg[i].event);
//            key_msg[i].event = key_event_Empty;
//        }
    }
}


/**
  * @brief ¦Ì?¦Ì?¡ã¡ä?¨¹???¡é
  * @param  None
  * @retval None
  */
static void check_key_trig(void)
{
	Trg_Button = Real_Button&(Real_Button^Cont_Button);			//
	Cont_Button = Real_Button;												//
}

void key_handler(void)
{
	check_key_readIO();
	check_key_debounce();
	check_key_trig();            //Read key status and get key trig
    check_key_msg();
}

#include "bsp_usart.h"





/* 串口发送字符串 */
void usart_send_string(uint8_t *ucstr)
{
	while(ucstr && *ucstr)
	{
	  usart_send_data(*ucstr++);
	}
}

int fputc(int ch, FILE *f)
{
     usart_send_data(ch);
     // 等待发送数据缓冲区标志置位
     return ch;
}



#define Length_TXBuf	200
typedef struct {
    uint8_t buf_TX[Length_TXBuf];
    uint8_t pos_TX_OUT;
    uint8_t pos_TX_IN;	

    uint8_t cnt_TX;
    bool	Flag_TX_Full;
    bool    Flag_TX_Empty;
} def_usart_tx;

def_usart_tx usart_tx = {0};
#if 0
/* 发送函数 */
void usart_send_data(uint8_t ucch)
{
	usart_data_transmit(BSP_USART,(uint8_t)ucch);
	while(RESET == usart_flag_get(BSP_USART,USART_FLAG_TBE));
}
#else

/* 发送函数 */
void usart_send_data(uint8_t ucch)
{
	// usart_data_transmit(BSP_USART,(uint8_t)ucch);
	// while(RESET == usart_flag_get(BSP_USART,USART_FLAG_TBE));
    //while(usart_tx.Flag_TX_Full);
    if(usart_tx.Flag_TX_Full)
        return;
	usart_tx.buf_TX[usart_tx.pos_TX_IN] = ucch;
	usart_tx.pos_TX_IN++;					//??????
	if(usart_tx.pos_TX_IN >= Length_TXBuf)
		usart_tx.pos_TX_IN = 0; 

	usart_tx.cnt_TX++;	 					//????
	if(usart_tx.cnt_TX>=Length_TXBuf)
	 	usart_tx.Flag_TX_Full = 1;			//????	  

	if(usart_tx.Flag_TX_Empty)
	{
		//SBUF_1 = (unsigned char)usart_tx.buf_TX[usart_tx.pos_TX_OUT];
        usart_data_transmit(BSP_USART,(uint8_t)usart_tx.buf_TX[usart_tx.pos_TX_OUT]);
		usart_tx.pos_TX_OUT++;
		if(usart_tx.pos_TX_OUT >= Length_TXBuf)
			usart_tx.pos_TX_OUT = 0;

		usart_tx.Flag_TX_Empty = 0;
	}	
}
#endif
void usart_handler(void )
{
    if(RESET == usart_flag_get(BSP_USART,USART_FLAG_TBE))
        return;
    if(usart_tx.cnt_TX > 1)
    {
        //SBUF_1 = (unsigned char)usart_tx.buf_TX[usart_tx.pos_TX_OUT];
        usart_data_transmit(BSP_USART,(uint8_t)usart_tx.buf_TX[usart_tx.pos_TX_OUT]);
        usart_tx.pos_TX_OUT++;
        if(usart_tx.pos_TX_OUT >= Length_TXBuf)
            usart_tx.pos_TX_OUT = 0;
        usart_tx.Flag_TX_Full = 0;
        usart_tx.cnt_TX--;
    
    }	
    else
    {
        usart_tx.cnt_TX = 0;
        usart_tx.Flag_TX_Empty = 1;
    }
}


void usart_gpio_config(uint32_t band_rate)
{
  /* 开启时钟 */
	rcu_periph_clock_enable(BSP_USART_TX_RCU); 
	rcu_periph_clock_enable(BSP_USART_RX_RCU); 
	rcu_periph_clock_enable(BSP_USART_RCU); 
	
	/* 配置GPIO复用功能 */
    gpio_af_set(BSP_USART_TX_PORT,BSP_USART_AF,BSP_USART_TX_PIN);	
	gpio_af_set(BSP_USART_RX_PORT,BSP_USART_AF,BSP_USART_RX_PIN);	
	
	/* 配置GPIO的模式 */
	/* 配置TX为复用模式 上拉模式 */
	gpio_mode_set(BSP_USART_TX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_TX_PIN);
	/* 配置RX为复用模式 上拉模式 */
	gpio_mode_set(BSP_USART_RX_PORT, GPIO_MODE_AF,GPIO_PUPD_PULLUP,BSP_USART_RX_PIN);
	
	/* 配置TX为推挽输出 50MHZ */
	gpio_output_options_set(BSP_USART_TX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_USART_TX_PIN);
	/* 配置RX为推挽输出 50MHZ */
	gpio_output_options_set(BSP_USART_RX_PORT,GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_RX_PIN);

	/* 配置串口的参数 */
	usart_deinit(BSP_USART);
	usart_baudrate_set(BSP_USART,band_rate);
	usart_parity_config(BSP_USART,USART_PM_NONE);
	usart_word_length_set(BSP_USART,USART_WL_8BIT);
	usart_stop_bit_set(BSP_USART,USART_STB_1BIT);

  /* 使能串口 */
	usart_enable(BSP_USART);
	usart_transmit_config(BSP_USART,USART_TRANSMIT_ENABLE);
	usart_tx.Flag_TX_Empty = true;
}


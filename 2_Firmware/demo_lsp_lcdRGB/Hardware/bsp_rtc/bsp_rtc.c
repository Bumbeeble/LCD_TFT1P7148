#include "bsp_rtc.h"

uint32_t RTCSRC_FLAG = 0;

__IO uint32_t prescaler_a = 0, prescaler_s = 0;
/*!
    \brief      display the current time
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_show_time(void)
{
    rtc_parameter_struct   rtc_initpara;
    rtc_current_time_get(&rtc_initpara);  
    printf("Current date: %0.2x:%0.2x:%0.2x\n\r", \
          rtc_initpara.year, rtc_initpara.month, rtc_initpara.date);
    printf("Current time: %0.2x:%0.2x:%0.2x\n\r", \
          rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
}


/*!
    \brief      use hyperterminal to setup RTC time and alarm
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_setup(void)
{
    /* setup RTC time value */
    uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    rtc_parameter_struct   rtc_initpara;
    rtc_initpara.factor_asyn = prescaler_a;
    rtc_initpara.factor_syn = prescaler_s;
    rtc_initpara.year = 0x22;
    //rtc_initpara.day_of_week = RTC_SATURDAY;
    rtc_initpara.month = RTC_MAR;
    rtc_initpara.date = 0x18;
    rtc_initpara.display_format = RTC_24HOUR;
    rtc_initpara.am_pm = RTC_AM;
    rtc_initpara.hour = 0x17;
    rtc_initpara.minute = 0x38;
    rtc_initpara.second = 0x43;
//    /* current time input */
//    printf("=======Configure RTC Time========\n\r");
//    printf("  please input hour:\n\r");
//    while (0xFF == tmp_hh){    
//        tmp_hh = usart_input_threshold(23);
//        rtc_initpara.hour = tmp_hh;
//    }
//    printf("  %0.2x\n\r", tmp_hh);
//    
//    printf("  please input minute:\n\r");
//    while (0xFF == tmp_mm){    
//        tmp_mm = usart_input_threshold(59);
//        rtc_initpara.minute = tmp_mm;
//    }
//    printf("  %0.2x\n\r", tmp_mm);

//    printf("  please input second:\n\r");
//    while (0xFF == tmp_ss){
//        tmp_ss = usart_input_threshold(59);
//        rtc_initpara.second = tmp_ss;
//    }
//    printf("  %0.2x\n\r", tmp_ss);

    /* RTC current time configuration */
    if(ERROR == rtc_init(&rtc_initpara)){    
        printf("\n\r** RTC time configuration failed! **\n\r");
    }else{
        printf("\n\r** RTC time configuration success! **\n\r");
        rtc_show_time();
        RTC_BKP0 = BKP_VALUE;
    }     
}


void bsp_rtc_config(void )
{
//----------config------------------
    /* enable PMU clock */
    rcu_periph_clock_enable(RCU_PMU);
    /* enable the access of the RTC registers */
    pmu_backup_write_enable();
    

    #if defined (RTC_CLOCK_SOURCE_IRC32K) 
          rcu_osci_on(RCU_IRC32K);
          rcu_osci_stab_wait(RCU_IRC32K);
          rcu_rtc_clock_config(RCU_RTCSRC_IRC32K);
  
          prescaler_s = 0x13F;
          prescaler_a = 0x63;
    #elif defined (RTC_CLOCK_SOURCE_LXTAL)
          rcu_osci_on(RCU_LXTAL);
          rcu_osci_stab_wait(RCU_LXTAL);
          rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);           //select rtc clock source
    
          prescaler_s = 0xFF;
          prescaler_a = 0x7F;
    #else
    #error RTC clock source should be defined.
    #endif /* RTC_CLOCK_SOURCE_IRC32K */

    rcu_periph_clock_enable(RCU_RTC);
    rtc_register_sync_wait();
    
	
    /* get RTC clock entry selection */
    RTCSRC_FLAG = GET_BITS(RCU_BDCTL, 8, 9);


//----------set up------------------
    if((BKP_VALUE != RTC_BKP0) || (0x00 == RTCSRC_FLAG))    //data is different or rtc clock not set
    {
      //backup data register value is not correct or not yet programed
        rtc_setup();
        
    }
    else
    {
        /* detect the reset source */
        if (RESET != rcu_flag_get(RCU_FLAG_PORRST)){
            printf("power on reset occurred....\n\r");
        }else if (RESET != rcu_flag_get(RCU_FLAG_EPRST)){
            printf("external reset occurred....\n\r");
        }
        printf("no need to configure RTC....\n\r");
        rtc_show_time();
    }
}

#include "spiInit.h"
#include "spi.h"
#define mDelaymS delay_1ms
#define mDelayuS delay_1us
//#define _HW_SPI_
static void spiInit_gpio_Init(void)
{
#ifndef _HW_SPI_
	/* enable the led clock */
	rcu_periph_clock_enable(LCD_SDA_RCU); // SDA
	gpio_mode_set(LCD_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_SDA_PIN);
	gpio_output_options_set(LCD_SDA_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_SDA_PIN);

	/* enable the led clock */
	rcu_periph_clock_enable(LCD_SCL_RCU); // SCL
	gpio_mode_set(LCD_SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_SCL_PIN);
	gpio_output_options_set(LCD_SCL_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_SCL_PIN);


	/* enable the led clock */
	rcu_periph_clock_enable(LCD_CS_RCU); // CS
	gpio_mode_set(LCD_CS_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_CS_PIN);
	gpio_output_options_set(LCD_CS_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_CS_PIN);

	/* enable the led clock */
	rcu_periph_clock_enable(LCD_RST_RCU); // RST
	gpio_mode_set(LCD_RST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_RST_PIN);
	gpio_output_options_set(LCD_RST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_RST_PIN);

	/* 背光 PD13 */
	rcu_periph_clock_enable(RCU_GPIOD);
	gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_13);
	gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);

#else
	spi_config();
#endif
}

#ifndef _HW_SPI_
void Write_3Spi_Byte(uint8_t CMD)
{
	uint8_t i;
	LCD_SCL_WRITE(0);
	// mDelayuS(10);
	for (i = 0; i < 8; i++)
	{
		LCD_SCL_WRITE(0);

		if ((CMD & 0x80) != 0)
			LCD_SDA_WRITE(1);
		else
			LCD_SDA_WRITE(0);

		LCD_SCL_WRITE(0);
		mDelayuS(1);
		LCD_SCL_WRITE(1);
		mDelayuS(1);
		CMD <<= 1;
	}
	// LCD_SCL_WRITE(0);
	// mDelayuS(10);
}

void Write_3Spi_cmd(uint16_t addr)
{
	LCD_CS_WRITE(0);
	mDelayuS(5);
	Write_3Spi_Byte(0x20);
	Write_3Spi_Byte(addr >> 8);

	Write_3Spi_Byte(0x00);
	Write_3Spi_Byte(addr);
	mDelayuS(5);
	LCD_CS_WRITE(1);
}

void Write_3Spi_data(uint8_t value)

{
	LCD_CS_WRITE(0);
	mDelayuS(5);
	Write_3Spi_Byte(0x40);
	Write_3Spi_Byte(value);
	mDelayuS(5);
	LCD_CS_WRITE(1);
}
#else

/******************************************************************************
	  函数说明：LCD串行数据写入函数
	  入口数据：dat  要写入的串行数据
	  返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat)
{
	LCD_CS_Clr();
	spi_ReadWriteByte(dat);
	// delay_1ms(1);
	delay_1ms(4);
	LCD_CS_Set();
}
/******************************************************************************
	  函数说明：LCD写入数据
	  入口数据：dat 写入的数据
	  返回值：  无
******************************************************************************/
void Write_3Spi_data(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}

/******************************************************************************
	  函数说明：LCD写入数据
	  入口数据：dat 写入的数据
	  返回值：  无
******************************************************************************/
void Write_3Spi_cmd(uint16_t dat)
{
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}

/******************************************************************************
	  函数说明：LCD写入命令
	  入口数据：dat 写入的命令
	  返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	//LCD_DC_Clr(); //写命令
	LCD_Writ_Bus(dat);
	//LCD_DC_Set(); //写数据
}

#endif

void NT35510_Init(void)
{

	spiInit_gpio_Init();
	LCD_SCL_WRITE(1);
	LCD_CS_WRITE(1);
	LCD_SDA_WRITE(1);
	mDelaymS(200);
	LCD_BLK_ON;
	LCD_RST_WRITE(1);
	mDelaymS(10);
	LCD_RST_WRITE(0);
	mDelaymS(50);
	LCD_RST_WRITE(1);
	mDelaymS(150);
	
	#if 0
	Write_3Spi_cmd(0xF000);	Write_3Spi_data(0x55);
	Write_3Spi_cmd(0xF001);	Write_3Spi_data(0xAA);
	Write_3Spi_cmd(0xF002);	Write_3Spi_data(0x52);
	Write_3Spi_cmd(0xF003);	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xF004);	Write_3Spi_data(0x01);//Page 1

	//*************AVDD Set AVDD 5.2V*************//
	Write_3Spi_cmd(0xB000);	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB001);	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB002);	Write_3Spi_data(0x0D);

	//************AVDD ratio****************//
	Write_3Spi_cmd(0xB600);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB601);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB602);	Write_3Spi_data(0x34);
	 
	//************AVEE  -5.2V****************//
	Write_3Spi_cmd(0xB100);	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB101);	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB102);	Write_3Spi_data(0x0D);

	//***********AVEE ratio*************//
	Write_3Spi_cmd(0xB700);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB701);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB702);	Write_3Spi_data(0x34);

	//***********VCL  -2.5V*************//
	Write_3Spi_cmd(0xB200);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xB201);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xB202);	Write_3Spi_data(0x00);

	//**************VCL ratio*****************//
	Write_3Spi_cmd(0xB800);	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xB801);	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xB802);	Write_3Spi_data(0x24);


	//*************VGH 15V  (Free pump)*********//
	Write_3Spi_cmd(0xBF00);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xB300);	Write_3Spi_data(0x0F);
	Write_3Spi_cmd(0xB301);	Write_3Spi_data(0x0F);
	Write_3Spi_cmd(0xB302);	Write_3Spi_data(0x0F);

	//*************VGH ratio*****************//
	Write_3Spi_cmd(0xB900);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB901);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB902);	Write_3Spi_data(0x34);

	//***************VGL_REG -10V**************//
	Write_3Spi_cmd(0xB500);	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xB501);	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xB502);	Write_3Spi_data(0x08);

	Write_3Spi_cmd(0xC200);	Write_3Spi_data(0x03);
		 
	//*****************VGLX ratio***************//
	Write_3Spi_cmd(0xBA00);	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xBA01);	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xBA02);	Write_3Spi_data(0x24);

	//*************VGMP/VGSP 4.5V/0V*************//
	Write_3Spi_cmd(0xBC00);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBC01);	Write_3Spi_data(0x78);
	Write_3Spi_cmd(0xBC02);	Write_3Spi_data(0x00);

	//************VGMN/VGSN -4.5V/0V****************//
	Write_3Spi_cmd(0xBD00);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBD01);	Write_3Spi_data(0x78);
	Write_3Spi_cmd(0xBD02);	Write_3Spi_data(0x00);

	//************VCOM  -1.25V****************//
	Write_3Spi_cmd(0xBE00);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBE01);	Write_3Spi_data(0x64);    //67--------------

	//************Gamma Setting******************//
	Write_3Spi_cmd(0xD100);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD101);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD102);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD103);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD104);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD105);	Write_3Spi_data(0x3a);
	Write_3Spi_cmd(0xD106);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD107);	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD108);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD109);	Write_3Spi_data(0x5c);
	Write_3Spi_cmd(0xD10A);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD10B);	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD10C);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD10D);	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD10E);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD10F);	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD110);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD111);	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD112);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD113);	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD114);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD115);	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD116);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD117);	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD118);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD119);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD11A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD11B);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD11C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD11D);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD11E);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD11F);	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD120);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD121);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD122);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD123);	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD124);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD125);	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD126);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD127);	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD128);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD129);	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD12A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD12B);	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD12C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD12D);	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD12E);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD12F);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD130);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD131);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD132);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD133);	Write_3Spi_data(0x6D);
					 
	Write_3Spi_cmd(0xD200);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD201);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD202);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD203);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD204);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD205);	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD206);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD207);	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD208);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD209);	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD20A);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD20B);	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD20C);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD20D);	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD20E);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD20F);	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD210);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD211);	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD212);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD213);	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD214);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD215);	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD216);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD217);	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD218);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD219);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD21A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD21B);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD21C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD21D);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD21E);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD21F);	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD220);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD221);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD222);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD223);	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD224);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD225);	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD226);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD227);	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD228);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD229);	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD22A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD22B);	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD22C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD22D);	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD22E);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD22F);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD230);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD231);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD232);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD233);	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD300);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD301);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD302);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD303);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD304);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD305);	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD306);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD307);	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD308);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD309);	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD30A);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD30B);	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD30C);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD30D);	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD30E);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD30F);	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD310);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD311);	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD312);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD313);	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD314);	Write_3Spi_data(0x01); 
	Write_3Spi_cmd(0xD315);	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD316);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD317);	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD318);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD319);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD31A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD31B);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD31C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD31D);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD31E);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD31F);	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD320);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD321);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD322);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD323);	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD324);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD325);	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD326);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD327);	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD328);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD329);	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD32A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD32B);	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD32C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD32D);	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD32E);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD32F);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD330);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD331);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD332);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD333);	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD400);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD401);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD402);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD403);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD404);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD405);	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD406);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD407);	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD408);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD409);	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD40A);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD40B);	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD40C);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD40D);	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD40E);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD40F);	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD410);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD411);	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD412);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD413);	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD414);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD415);	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD416);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD417);	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD418);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD419);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD41A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD41B);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD41C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD41D);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD41E);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD41F);	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD420);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD421);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD422);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD423);	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD424);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD425);	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD426);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD427);	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD428);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD429);	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD42A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD42B);	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD42C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD42D);	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD42E);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD42F);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD430);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD431);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD432);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD433);	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD500);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD501);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD502);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD503);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD504);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD505);	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD506);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD507);	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD508);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD509);	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD50A);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD50B);	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD50C);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD50D);	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD50E);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD50F);	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD510);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD511);	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD512);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD513);	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD514);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD515);	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD516);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD517);	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD518);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD519);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD51A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD51B);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD51C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD51D);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD51E);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD51F);	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD520);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD521);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD522);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD523);	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD524);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD525);	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD526);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD527);	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD528);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD529);	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD52A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD52B);	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD52C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD52D);	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD52E);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD52F);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD530);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD531);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD532);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD533);	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD600);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD601);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD602);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD603);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD604);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD605);	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD606);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD607);	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD608);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD609);	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD60A);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD60B);	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD60C);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD60D);	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD60E);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD60F);	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD610);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD611);	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD612);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD613);	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD614);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD615);	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD616);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD617);	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD618);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD619);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD61A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD61B);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD61C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD61D);	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD61E);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD61F);	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD620);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD621);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD622);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD623);	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD624);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD625);	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD626);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD627);	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD628);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD629);	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD62A);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD62B);	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD62C);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD62D);	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD62E);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD62F);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD630);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD631);	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD632);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD633);	Write_3Spi_data(0x6D);


	//**************LV2 Page 0 enable*************//
	Write_3Spi_cmd(0xF000);	Write_3Spi_data(0x55);
	Write_3Spi_cmd(0xF001);	Write_3Spi_data(0xAA);
	Write_3Spi_cmd(0xF002);	Write_3Spi_data(0x52);
	Write_3Spi_cmd(0xF003);	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xF004);	Write_3Spi_data(0x00);//Page 0

	//Write_3Spi_cmd(0xB000);	Write_3Spi_data(0x00);//add RGB mode2
	//Write_3Spi_cmd(0xB001);	Write_3Spi_data(0x10);
	//Write_3Spi_cmd(0xB002);	Write_3Spi_data(0x10);
	//Write_3Spi_cmd(0xB003);	Write_3Spi_data(0x10);
	//Write_3Spi_cmd(0xB004);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xB300);	Write_3Spi_data(0x00);

	//*************480x800*********************//
	Write_3Spi_cmd(0xB500);	Write_3Spi_data(0x50);

	//***************Display control**************//
	Write_3Spi_cmd(0xB100);	Write_3Spi_data(0xCC);
	Write_3Spi_cmd(0xB101);	Write_3Spi_data(0x00);

	//***************Source hold time*************//
	Write_3Spi_cmd(0xB600);	Write_3Spi_data(0x05);

	//**************Gate EQ control***************//
	Write_3Spi_cmd(0xB700);	Write_3Spi_data(0x70);
	Write_3Spi_cmd(0xB701);	Write_3Spi_data(0x70);

	//*************Source EQ control (Mode 2)******//
	Write_3Spi_cmd(0xB800);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xB801);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xB802);	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xB803);	Write_3Spi_data(0x03);
					
	//************Inversion mode  (2-dot)***********//
	Write_3Spi_cmd(0xBC00);	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xBC01);	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBC02);	Write_3Spi_data(0x00);
					 
	//***************Frame rate***************//      
	/*
	Write_3Spi_cmd(0xBD00);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xBD01);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xBD02);	Write_3Spi_data(0x1C);  //0X1C
	Write_3Spi_cmd(0xBD03);	Write_3Spi_data(0x1C);
	Write_3Spi_cmd(0xBD04);	Write_3Spi_data(0x00);*/

	//********Timing control 4H w/ 4-Delayms *******//
	Write_3Spi_cmd(0xC900);	Write_3Spi_data(0xD0);
	Write_3Spi_cmd(0xC901);	Write_3Spi_data(0x02); 
	Write_3Spi_cmd(0xC902);	Write_3Spi_data(0x50);
	Write_3Spi_cmd(0xC903);	Write_3Spi_data(0x50);
	Write_3Spi_cmd(0xC904);	Write_3Spi_data(0x50);

	Write_3Spi_cmd(0x3600);	Write_3Spi_data(0x00);//00
	Write_3Spi_cmd(0x3500);	Write_3Spi_data(0x00);
	
	Write_3Spi_cmd(0x3A00); Write_3Spi_data(0x55);
	Write_3Spi_cmd(0x1100);
	mDelaymS(120);
	Write_3Spi_cmd(0x2900);
	mDelaymS(10);
	Write_3Spi_cmd(0x2C00);
#else
	Write_3Spi_cmd(0xF000);
	Write_3Spi_data(0x55);
	Write_3Spi_cmd(0xF001);
	Write_3Spi_data(0xAA);
	Write_3Spi_cmd(0xF002);
	Write_3Spi_data(0x52);
	Write_3Spi_cmd(0xF003);
	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xF004);
	Write_3Spi_data(0x01); // Page 1

	//*************AVDD Set AVDD 5.2V*************//
	Write_3Spi_cmd(0xB000);
	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB001);
	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB002);
	Write_3Spi_data(0x0D);

	//************AVDD ratio****************//
	Write_3Spi_cmd(0xB600);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB601);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB602);
	Write_3Spi_data(0x34);

	//************AVEE  -5.2V****************//
	Write_3Spi_cmd(0xB100);
	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB101);
	Write_3Spi_data(0x0D);
	Write_3Spi_cmd(0xB102);
	Write_3Spi_data(0x0D);

	//***********AVEE ratio*************//
	Write_3Spi_cmd(0xB700);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB701);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB702);
	Write_3Spi_data(0x34);

	//***********VCL  -2.5V*************//
	Write_3Spi_cmd(0xB200);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xB201);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xB202);
	Write_3Spi_data(0x00);

	//**************VCL ratio*****************//
	Write_3Spi_cmd(0xB800);
	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xB801);
	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xB802);
	Write_3Spi_data(0x24);

	//*************VGH 15V  (Free pump)*********//
	Write_3Spi_cmd(0xBF00);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xB300);
	Write_3Spi_data(0x0F);
	Write_3Spi_cmd(0xB301);
	Write_3Spi_data(0x0F);
	Write_3Spi_cmd(0xB302);
	Write_3Spi_data(0x0F);

	//*************VGH ratio*****************//
	Write_3Spi_cmd(0xB900);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB901);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xB902);
	Write_3Spi_data(0x34);

	//***************VGL_REG -10V**************//
	Write_3Spi_cmd(0xB500);
	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xB501);
	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xB502);
	Write_3Spi_data(0x08);

	Write_3Spi_cmd(0xC200);
	Write_3Spi_data(0x03);

	//*****************VGLX ratio***************//
	Write_3Spi_cmd(0xBA00);
	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xBA01);
	Write_3Spi_data(0x24);
	Write_3Spi_cmd(0xBA02);
	Write_3Spi_data(0x24);

	//*************VGMP/VGSP 4.5V/0V*************//
	Write_3Spi_cmd(0xBC00);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBC01);
	Write_3Spi_data(0x78);
	Write_3Spi_cmd(0xBC02);
	Write_3Spi_data(0x00);

	//************VGMN/VGSN -4.5V/0V****************//
	Write_3Spi_cmd(0xBD00);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBD01);
	Write_3Spi_data(0x78);
	Write_3Spi_cmd(0xBD02);
	Write_3Spi_data(0x00);

	//************VCOM  -1.25V****************//
	Write_3Spi_cmd(0xBE00);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBE01);
	Write_3Spi_data(0x64); // 67--------------

	//************Gamma Setting******************//
	Write_3Spi_cmd(0xD100);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD101);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD102);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD103);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD104);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD105);
	Write_3Spi_data(0x3a);
	Write_3Spi_cmd(0xD106);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD107);
	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD108);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD109);
	Write_3Spi_data(0x5c);
	Write_3Spi_cmd(0xD10A);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD10B);
	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD10C);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD10D);
	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD10E);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD10F);
	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD110);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD111);
	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD112);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD113);
	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD114);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD115);
	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD116);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD117);
	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD118);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD119);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD11A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD11B);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD11C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD11D);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD11E);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD11F);
	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD120);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD121);
	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD122);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD123);
	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD124);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD125);
	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD126);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD127);
	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD128);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD129);
	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD12A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD12B);
	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD12C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD12D);
	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD12E);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD12F);
	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD130);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD131);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD132);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD133);
	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD200);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD201);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD202);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD203);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD204);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD205);
	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD206);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD207);
	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD208);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD209);
	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD20A);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD20B);
	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD20C);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD20D);
	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD20E);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD20F);
	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD210);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD211);
	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD212);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD213);
	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD214);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD215);
	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD216);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD217);
	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD218);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD219);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD21A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD21B);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD21C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD21D);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD21E);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD21F);
	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD220);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD221);
	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD222);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD223);
	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD224);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD225);
	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD226);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD227);
	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD228);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD229);
	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD22A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD22B);
	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD22C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD22D);
	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD22E);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD22F);
	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD230);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD231);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD232);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD233);
	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD300);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD301);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD302);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD303);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD304);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD305);
	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD306);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD307);
	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD308);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD309);
	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD30A);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD30B);
	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD30C);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD30D);
	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD30E);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD30F);
	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD310);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD311);
	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD312);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD313);
	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD314);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD315);
	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD316);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD317);
	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD318);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD319);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD31A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD31B);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD31C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD31D);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD31E);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD31F);
	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD320);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD321);
	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD322);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD323);
	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD324);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD325);
	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD326);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD327);
	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD328);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD329);
	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD32A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD32B);
	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD32C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD32D);
	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD32E);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD32F);
	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD330);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD331);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD332);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD333);
	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD400);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD401);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD402);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD403);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD404);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD405);
	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD406);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD407);
	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD408);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD409);
	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD40A);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD40B);
	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD40C);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD40D);
	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD40E);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD40F);
	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD410);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD411);
	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD412);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD413);
	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD414);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD415);
	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD416);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD417);
	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD418);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD419);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD41A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD41B);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD41C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD41D);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD41E);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD41F);
	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD420);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD421);
	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD422);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD423);
	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD424);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD425);
	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD426);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD427);
	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD428);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD429);
	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD42A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD42B);
	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD42C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD42D);
	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD42E);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD42F);
	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD430);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD431);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD432);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD433);
	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD500);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD501);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD502);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD503);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD504);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD505);
	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD506);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD507);
	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD508);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD509);
	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD50A);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD50B);
	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD50C);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD50D);
	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD50E);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD50F);
	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD510);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD511);
	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD512);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD513);
	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD514);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD515);
	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD516);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD517);
	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD518);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD519);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD51A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD51B);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD51C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD51D);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD51E);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD51F);
	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD520);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD521);
	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD522);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD523);
	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD524);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD525);
	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD526);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD527);
	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD528);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD529);
	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD52A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD52B);
	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD52C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD52D);
	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD52E);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD52F);
	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD530);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD531);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD532);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD533);
	Write_3Spi_data(0x6D);

	Write_3Spi_cmd(0xD600);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD601);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD602);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD603);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD604);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD605);
	Write_3Spi_data(0x3A);
	Write_3Spi_cmd(0xD606);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD607);
	Write_3Spi_data(0x4A);
	Write_3Spi_cmd(0xD608);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD609);
	Write_3Spi_data(0x5C);
	Write_3Spi_cmd(0xD60A);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD60B);
	Write_3Spi_data(0x81);
	Write_3Spi_cmd(0xD60C);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD60D);
	Write_3Spi_data(0xA6);
	Write_3Spi_cmd(0xD60E);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD60F);
	Write_3Spi_data(0xE5);
	Write_3Spi_cmd(0xD610);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD611);
	Write_3Spi_data(0x13);
	Write_3Spi_cmd(0xD612);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD613);
	Write_3Spi_data(0x54);
	Write_3Spi_cmd(0xD614);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD615);
	Write_3Spi_data(0x82);
	Write_3Spi_cmd(0xD616);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD617);
	Write_3Spi_data(0xCA);
	Write_3Spi_cmd(0xD618);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD619);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xD61A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD61B);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xD61C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD61D);
	Write_3Spi_data(0x34);
	Write_3Spi_cmd(0xD61E);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD61F);
	Write_3Spi_data(0x67);
	Write_3Spi_cmd(0xD620);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD621);
	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xD622);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD623);
	Write_3Spi_data(0xA4);
	Write_3Spi_cmd(0xD624);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD625);
	Write_3Spi_data(0xB7);
	Write_3Spi_cmd(0xD626);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD627);
	Write_3Spi_data(0xCF);
	Write_3Spi_cmd(0xD628);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD629);
	Write_3Spi_data(0xDE);
	Write_3Spi_cmd(0xD62A);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD62B);
	Write_3Spi_data(0xF2);
	Write_3Spi_cmd(0xD62C);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xD62D);
	Write_3Spi_data(0xFE);
	Write_3Spi_cmd(0xD62E);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD62F);
	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xD630);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD631);
	Write_3Spi_data(0x33);
	Write_3Spi_cmd(0xD632);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xD633);
	Write_3Spi_data(0x6D);

	//**************LV2 Page 0 enable*************//
	Write_3Spi_cmd(0xF000);
	Write_3Spi_data(0x55);
	Write_3Spi_cmd(0xF001);
	Write_3Spi_data(0xAA);
	Write_3Spi_cmd(0xF002);
	Write_3Spi_data(0x52);
	Write_3Spi_cmd(0xF003);
	Write_3Spi_data(0x08);
	Write_3Spi_cmd(0xF004);
	Write_3Spi_data(0x00); // Page 0

	// Write_3Spi_cmd(0xB000);	Write_3Spi_data(0x00);//add RGB mode2
	// Write_3Spi_cmd(0xB001);	Write_3Spi_data(0x10);
	// Write_3Spi_cmd(0xB002);	Write_3Spi_data(0x10);
	// Write_3Spi_cmd(0xB003);	Write_3Spi_data(0x10);
	// Write_3Spi_cmd(0xB004);	Write_3Spi_data(0x10);
	Write_3Spi_cmd(0xB300);
	Write_3Spi_data(0x00);

	//*************480x800*********************//
	Write_3Spi_cmd(0xB500);
	Write_3Spi_data(0x50);

	//***************Display control**************//
	Write_3Spi_cmd(0xB100);
	Write_3Spi_data(0xCC);
	Write_3Spi_cmd(0xB101);
	Write_3Spi_data(0x00);

	//***************Source hold time*************//
	Write_3Spi_cmd(0xB600);
	Write_3Spi_data(0x05);

	//**************Gate EQ control***************//
	Write_3Spi_cmd(0xB700);
	Write_3Spi_data(0x70);
	Write_3Spi_cmd(0xB701);
	Write_3Spi_data(0x70);

	//*************Source EQ control (Mode 2)******//
	Write_3Spi_cmd(0xB800);
	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xB801);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xB802);
	Write_3Spi_data(0x03);
	Write_3Spi_cmd(0xB803);
	Write_3Spi_data(0x03);

	//************Inversion mode  (2-dot)***********//
	Write_3Spi_cmd(0xBC00);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xBC01);
	Write_3Spi_data(0x00);
	Write_3Spi_cmd(0xBC02);
	Write_3Spi_data(0x00);

	//***************Frame rate***************//
	/*
	Write_3Spi_cmd(0xBD00);	Write_3Spi_data(0x01);
	Write_3Spi_cmd(0xBD01);	Write_3Spi_data(0x84);
	Write_3Spi_cmd(0xBD02);	Write_3Spi_data(0x1C);  //0X1C
	Write_3Spi_cmd(0xBD03);	Write_3Spi_data(0x1C);
	Write_3Spi_cmd(0xBD04);	Write_3Spi_data(0x00);*/

	//********Timing control 4H w/ 4-Delayms *******//
	Write_3Spi_cmd(0xC900);
	Write_3Spi_data(0xD0);
	Write_3Spi_cmd(0xC901);
	Write_3Spi_data(0x02);
	Write_3Spi_cmd(0xC902);
	Write_3Spi_data(0x50);
	Write_3Spi_cmd(0xC903);
	Write_3Spi_data(0x50);
	Write_3Spi_cmd(0xC904);
	Write_3Spi_data(0x50);

	Write_3Spi_cmd(0x3600);
	Write_3Spi_data(0x00); // 00
	Write_3Spi_cmd(0x3500);
	Write_3Spi_data(0x00);

	Write_3Spi_cmd(0x3A00);
	Write_3Spi_data(0x55);
	Write_3Spi_cmd(0x1100);
	mDelaymS(120);
	Write_3Spi_cmd(0x2900);
	mDelaymS(10);
	Write_3Spi_cmd(0x2C00);
#endif
}

#include "TLI.h"

#ifdef LCD_800X4800
#include "image_RGB565_800X480.h"
#else
#include "image_RGB565_480X800.h"
#endif
//
#include "font.h"
#include "image1.h"
#include "shell.h"
#include "w25qxx.h"

#define __GWDBG__
#ifdef __GWDBG__
#define GWDBG(format, ...) printf("GWDBG[%s,%d] " format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define GWDBG(format, ...)
#endif

static void TLI_gpio_config(void)
{
  /* enable the periphral clock */
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOB);
  rcu_periph_clock_enable(RCU_GPIOC);
  rcu_periph_clock_enable(RCU_GPIOD);
  rcu_periph_clock_enable(RCU_GPIOF);
  rcu_periph_clock_enable(RCU_GPIOG);

  /* configure HSYNC(PC6), VSYNC(PA4), PCLK(PG7), DE(PF10) */
  /* configure LCD_R7(PG6), LCD_R6(PA8), LCD_R5(PA12), LCD_R4(PA11), LCD_R3(PB0),
               LCD_G7(PD3), LCD_G6(PC7), LCD_G5(PB11), LCD_G4(PB10), LCD_G3(PG10), LCD_G2(PA6),
               LCD_B7(PB9), LCD_B6(PB8), LCD_B5(PA3), LCD_B4(PG12), LCD_B3(PG11) */
  /* TLI pins AF configure */
  gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12);

  gpio_af_set(GPIOB, GPIO_AF_9, GPIO_PIN_0); // PB0
  gpio_af_set(GPIOB, GPIO_AF_14, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);

  gpio_af_set(GPIOC, GPIO_AF_14, GPIO_PIN_6 | GPIO_PIN_7);

  gpio_af_set(GPIOD, GPIO_AF_14, GPIO_PIN_3);

  gpio_af_set(GPIOF, GPIO_AF_14, GPIO_PIN_10);

  gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_11);
  gpio_af_set(GPIOG, GPIO_AF_9, GPIO_PIN_10 | GPIO_PIN_12);

  /* configure TLI GPIO */

  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12);
  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12);

  gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
  gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);

  gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7);
  gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_6 | GPIO_PIN_7);

  gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
  gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_3);

  gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
  gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_10);

  gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
  gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
}
typedef struct
{
  uint32_t n;
  uint32_t p;
  uint32_t r;
  uint32_t v;
} TLI_CLK_t;

TLI_CLK_t tli_clk;

// LCD???????,?????SDRAM??.
#define LCD_FRAME_BUF_ADDR 0XC0000000

uint32_t *ltdc_framebuf[2];                                                                    // LTDC LCD???????,?????????????
uint16_t ltdc_lcd_framebuf0[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR)));                 //?????????,LCD??????????
uint16_t ltdc_lcd_framebuf1[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR + 800 * 480 * 2))); //?????????,LCD??????????

void TLI_ConfigParam(
    int b_HORIZONTAL_SYNCHRONOUS_PULSE,
    int b_HORIZONTAL_BACK_PORCH,
    int b_HORIZONTAL_FRONT_PORCH,
    int b_VERTICAL_SYNCHRONOUS_PULSE,
    int b_VERTICAL_BACK_PORCH,
    int b_VERTICAL_FRONT_PORCH)
{

  tli_parameter_struct tli_init_struct;
  tli_layer_parameter_struct tli_layer_init_struct;

  /* initialize the parameters of structure */
    tli_struct_para_init(&tli_init_struct);
    tli_layer_struct_para_init(&tli_layer_init_struct);
	
		rcu_periph_clock_enable(RCU_TLI);
	  TLI_gpio_config();
	
  W25QXX_Read((u8*)&tli_clk,0,sizeof(tli_clk));
  if (0 == b_HORIZONTAL_SYNCHRONOUS_PULSE
      && 0 == b_HORIZONTAL_BACK_PORCH
      && 0 == b_HORIZONTAL_FRONT_PORCH
      && 0 == b_VERTICAL_SYNCHRONOUS_PULSE
      && 0 == b_VERTICAL_BACK_PORCH
      && 0 == b_VERTICAL_FRONT_PORCH)
  {
    b_HORIZONTAL_SYNCHRONOUS_PULSE = HORIZONTAL_SYNCHRONOUS_PULSE;
    b_HORIZONTAL_BACK_PORCH        = HORIZONTAL_BACK_PORCH       ;
    b_HORIZONTAL_FRONT_PORCH       = HORIZONTAL_FRONT_PORCH      ;
    b_VERTICAL_SYNCHRONOUS_PULSE   = VERTICAL_SYNCHRONOUS_PULSE  ;
    b_VERTICAL_BACK_PORCH          = VERTICAL_BACK_PORCH         ;
    b_VERTICAL_FRONT_PORCH         = VERTICAL_FRONT_PORCH        ;
  }


  if (tli_clk.v == 2 || tli_clk.v == 4 || tli_clk.v == 8 || tli_clk.v == 16)
  {
    /* configure the PLLSAI clock to generate lcd clock */
    if (ERROR == rcu_pllsai_config(tli_clk.n, tli_clk.p, tli_clk.r))
    {
      while (1)
        ;
    }

    switch (tli_clk.v)
    {
    case 2:
      rcu_tli_clock_div_config(RCU_PLLSAIR_DIV2);
      break;
    case 4:
      rcu_tli_clock_div_config(RCU_PLLSAIR_DIV4);
      break;
    case 8:
      rcu_tli_clock_div_config(RCU_PLLSAIR_DIV8);
      break;
    case 16:
      rcu_tli_clock_div_config(RCU_PLLSAIR_DIV16);
      break;
    default:
      rcu_tli_clock_div_config(RCU_PLLSAIR_DIV4);
      break;
    }
  }
  else
  {
    /* configure the PLLSAI clock to generate lcd clock */
    if (ERROR == rcu_pllsai_config(192, 2, 3))
    {
      while (1)
        ;
    }
    rcu_tli_clock_div_config(RCU_PLLSAIR_DIV2);
  }
  GWDBG("lcd_clk %d %d %d %d ",
        tli_clk.n,
        tli_clk.p,
        tli_clk.r,
        tli_clk.v);

  GWDBG("TLI_ConfigParam %d %d %d %d %d %d \r\n",
        b_HORIZONTAL_SYNCHRONOUS_PULSE,
        b_HORIZONTAL_BACK_PORCH,
        b_HORIZONTAL_FRONT_PORCH,
        b_VERTICAL_SYNCHRONOUS_PULSE,
        b_VERTICAL_BACK_PORCH,
        b_VERTICAL_FRONT_PORCH);

  rcu_osci_on(RCU_PLLSAI_CK);
  if (ERROR == rcu_osci_stab_wait(RCU_PLLSAI_CK))
  {
    while (1)
      ;
  }

  /* configure TLI parameter struct */
  tli_init_struct.signalpolarity_hs = TLI_HSYN_ACTLIVE_LOW;
  tli_init_struct.signalpolarity_vs = TLI_VSYN_ACTLIVE_LOW;
  tli_init_struct.signalpolarity_de = TLI_DE_ACTLIVE_LOW;
#ifdef LCD_800X4800
  tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;
#else
  tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_INVERTEDTLI;
#endif

  /* LCD display timing configuration */
  tli_init_struct.synpsz_hpsz = b_HORIZONTAL_SYNCHRONOUS_PULSE - 1;
  tli_init_struct.synpsz_vpsz = b_VERTICAL_SYNCHRONOUS_PULSE - 1;
  tli_init_struct.backpsz_hbpsz = b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH - 1;
  tli_init_struct.backpsz_vbpsz = b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH - 1;
  tli_init_struct.activesz_hasz = b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH - 1;
  tli_init_struct.activesz_vasz = b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH + ACTIVE_HEIGHT - 1;
  tli_init_struct.totalsz_htsz = b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH + b_HORIZONTAL_FRONT_PORCH - 1;
  tli_init_struct.totalsz_vtsz = b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH + ACTIVE_HEIGHT + b_VERTICAL_FRONT_PORCH - 1;

  tli_init_struct.backcolor_red = 0xff;
  tli_init_struct.backcolor_green = 0xff;
  tli_init_struct.backcolor_blue = 0xff;

  tli_init(&tli_init_struct);

  tli_layer_init_struct.layer_window_leftpos = b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH;
  tli_layer_init_struct.layer_window_rightpos = (ACTIVE_WIDTH + b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH - 1);
  tli_layer_init_struct.layer_window_toppos = b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH;
  tli_layer_init_struct.layer_window_bottompos = (ACTIVE_HEIGHT + b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH - 1);

  /* TLI window pixel format configuration */
  tli_layer_init_struct.layer_ppf = LAYER_PPF_RGB565;
  /* TLI window specified alpha configuration */
  tli_layer_init_struct.layer_sa = 255; //
  /* TLI layer default alpha R,G,B value configuration */
  tli_layer_init_struct.layer_default_blue = 0xFF;
  tli_layer_init_struct.layer_default_green = 0xFF;
  tli_layer_init_struct.layer_default_red = 0xFF;
  tli_layer_init_struct.layer_default_alpha = 0X00; // ???
  /* TLI window blend configuration */
  tli_layer_init_struct.layer_acf1 = LAYER_ACF1_SA;
  tli_layer_init_struct.layer_acf2 = LAYER_ACF2_SA;
  /* TLI layer frame buffer base address configuration */
  ltdc_framebuf[0] = (uint32_t *)&ltdc_lcd_framebuf0;
  tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)ltdc_framebuf[0];

  //  tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)&gImage_Image_RGB565;

  tli_layer_init_struct.layer_frame_line_length = ((ACTIVE_WIDTH * 2) + 3);
  tli_layer_init_struct.layer_frame_buf_stride_offset = (ACTIVE_WIDTH * 2);
  tli_layer_init_struct.layer_frame_total_line_number = ACTIVE_HEIGHT; // ACTIVE_HEIGHT;
  tli_layer_init(LAYER0, &tli_layer_init_struct);

  tli_layer_init_struct.layer_window_leftpos = b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH;
  tli_layer_init_struct.layer_window_rightpos = (ACTIVE_WIDTH + b_HORIZONTAL_SYNCHRONOUS_PULSE + b_HORIZONTAL_BACK_PORCH - 1);
  tli_layer_init_struct.layer_window_toppos = b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH;
  tli_layer_init_struct.layer_window_bottompos = (ACTIVE_HEIGHT + b_VERTICAL_SYNCHRONOUS_PULSE + b_VERTICAL_BACK_PORCH - 1);

  /* TLI window pixel format configuration */
  tli_layer_init_struct.layer_ppf = LAYER_PPF_RGB565;
  /* TLI window specified alpha configuration */
  tli_layer_init_struct.layer_sa = 255; //
  /* TLI layer default alpha R,G,B value configuration */
  tli_layer_init_struct.layer_default_blue = 0xFF;
  tli_layer_init_struct.layer_default_green = 0xFF;
  tli_layer_init_struct.layer_default_red = 0xFF;
  tli_layer_init_struct.layer_default_alpha = 0X00; // ???
  /* TLI window blend configuration */
  tli_layer_init_struct.layer_acf1 = LAYER_ACF1_SA;
  tli_layer_init_struct.layer_acf2 = LAYER_ACF2_SA;
  /* TLI layer frame buffer base address configuration */
  ltdc_framebuf[1] = (uint32_t *)&ltdc_lcd_framebuf1;

  memcpy(ltdc_lcd_framebuf1, gImage_Image_RGB565, sizeof(gImage_Image_RGB565));
  tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)ltdc_framebuf[1];

  //  tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)&gImage_Image_RGB565;
  tli_layer_init_struct.layer_frame_line_length = ((ACTIVE_WIDTH * 2) + 3);
  tli_layer_init_struct.layer_frame_buf_stride_offset = (ACTIVE_WIDTH * 2);
  tli_layer_init_struct.layer_frame_total_line_number = ACTIVE_HEIGHT; // ACTIVE_HEIGHT;
  tli_layer_init(LAYER1, &tli_layer_init_struct);

  tli_dither_config(TLI_DITHER_ENABLE);

    tli_layer_disable(LAYER0);
    tli_layer_enable(LAYER1);
    /* reload layer0 and layer1 configuration */
    tli_reload_config(TLI_REQUEST_RELOAD_EN);
    tli_enable();

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), TLI_ConfigParam, TLI_ConfigParam, TLI_ConfigParam 10 150 40 10 10 15);

void lcd_clk(uint32_t n, uint32_t p, uint32_t r, uint32_t v)
{

  tli_clk.n = n;
  tli_clk.p = p;
  tli_clk.r = r;
  tli_clk.v = v;

  GWDBG("lcd_clk %d %d %d %d ",
        tli_clk.n,
        tli_clk.p,
        tli_clk.r,
        tli_clk.v);
  W25QXX_Write((u8 *)&tli_clk, 0, sizeof(tli_clk));
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), lcd_clk, lcd_clk, lcd_clk);

/* ?????? */
void LTDC_transparency_set(uint8_t layer, uint8_t trans)
{
  switch (layer)
  {
  case 0:
    TLI_LxSA(LAYER0) = trans; // ?????
    break;
  case 1:
    TLI_LxSA(LAYER1) = trans; // ?????
    break;
  }

  tli_reload_config(TLI_REQUEST_RELOAD_EN); // ??
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LTDC_transparency_set, LTDC_transparency_set, void LTDC_transparency_set(uint8_t layer, uint8_t trans));

//????
// x,y:????
// color:???
void LTDC_Draw_Point(uint8_t layer, uint16_t x, uint16_t y, uint32_t color)
{
#if screen_direct
  *(uint16_t *)((uint32_t)ltdc_framebuf[layer] + 2 * (ACTIVE_WIDTH * y + x)) = color;
#else
  *(uint16_t *)((uint32_t)ltdc_framebuf[layer] + 2 * (ACTIVE_WIDTH * (ACTIVE_HEIGHT - x - 1) + y)) = color;
#endif
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LTDC_Draw_Point, LTDC_Draw_Point, (uint8_t layer, uint16_t x, uint16_t y, uint32_t color));
/* ???? */
void LTDC_Set_Area(uint8_t layer, uint16_t sx, uint16_t sy, uint16_t w, uint16_t h)
{

  tli_layer_parameter_struct tli_layer_init_struct;

  /* ????? */
  tli_layer_init_struct.layer_window_leftpos = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + sx;
  tli_layer_init_struct.layer_window_rightpos = (w + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1);
  tli_layer_init_struct.layer_window_toppos = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + sy;
  tli_layer_init_struct.layer_window_bottompos = (h + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1);

  tli_layer_init_struct.layer_frame_line_length = ((w * 2) + 3);
  tli_layer_init_struct.layer_frame_buf_stride_offset = (w * 2);
  tli_layer_init_struct.layer_frame_total_line_number = h; // ACTIVE_HEIGHT;

  switch (layer)
  {
  case 0:
    ltdc_framebuf[0] = (uint32_t *)&ltdc_lcd_framebuf0;
    tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)ltdc_framebuf[0];
    tli_layer_init(LAYER0, &tli_layer_init_struct);
    break;
  case 1:
    ltdc_framebuf[1] = (uint32_t *)&ltdc_lcd_framebuf1;
    tli_layer_init_struct.layer_frame_bufaddr = (uint32_t)ltdc_framebuf[1];
    tli_layer_init(LAYER1, &tli_layer_init_struct);
    break;
  }
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LTDC_Set_Area, LTDC_Set_Area, (uint8_t layer, uint16_t sx, uint16_t sy, uint16_t w, uint16_t h));

/* ???? */
void LTDC_Fill(uint8_t layer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color)
{
  uint16_t y0, x0;

  /* ??????? */
  // LTDC_Set_Area(layer,x,y,w,h); //
  for (y0 = y; y0 < y + h; y0++)
  {
    for (x0 = x; x0 < x + w; x0++)
    {
      LTDC_Draw_Point(layer, x0, y0, color);
    }
  }
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LTDC_Fill, LTDC_Fill, (uint8_t layer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color));
// LCD??
// color:???
void LTDC_Clear(uint8_t layer, uint32_t color)
{
#if screen_direct
  LTDC_Fill(layer, 0, 0, ACTIVE_WIDTH - 1, ACTIVE_HEIGHT - 1, color);
#else
  LTDC_Fill(layer, 0, 0, ACTIVE_HEIGHT - 1, ACTIVE_WIDTH - 1, color);
#endif
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LTDC_Clear, LTDC_Clear, (uint8_t layer, uint32_t color));
/*******************************************************************************
//??????????????  YZ
//(x,y):???
//r    :??
*******************************************************************************/
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
  int a, b;
  int di;
  a = 0;
  b = r;
  di = 3 - (r << 1); //??????????
  while (a <= b)
  {
    LTDC_Draw_Point(1, x0 + a, y0 - b, color); // 5
    LTDC_Draw_Point(1, x0 + b, y0 - a, color); // 0
    LTDC_Draw_Point(1, x0 + b, y0 + a, color); // 4
    LTDC_Draw_Point(1, x0 + a, y0 + b, color); // 6
    LTDC_Draw_Point(1, x0 - a, y0 + b, color); // 1
    LTDC_Draw_Point(1, x0 - b, y0 + a, color);
    LTDC_Draw_Point(1, x0 - a, y0 - b, color); // 2
    LTDC_Draw_Point(1, x0 - b, y0 - a, color); // 7
    a++;
    //??Bresenham????
    if (di < 0)
      di += 4 * a + 6;
    else
    {
      di += 10 + 4 * (a - b);
      b--;
    }
  }
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LCD_Draw_Circle, LCD_Draw_Circle, (uint16_t x0, uint16_t y0, uint8_t r, uint16_t color));
/*******************************************************************************
//???????????   YZ
//x,y:????
//num:??????:" "--->"~"
//size:???? 12/16/24
//mode:????(1)???????(0)
//???
//1?????(size/2)???(size)???
//2???????????????????????????????????
//3???????????????????
//csize=(size/8+((size%8)?1:0))*(size/2)
//??*??????????????*????????????
*******************************************************************************/
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t color, uint8_t mode)
{
  uint8_t temp, t1, t;
  uint16_t y0 = y;
  uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); //???????????????????
  num = num - ' ';                                                //????????ASCII?????????????-' '??????????
  for (t = 0; t < csize; t++)
  {
    if (size == 12)
      temp = asc2_1206[num][t]; //??1206??
    else if (size == 16)
      temp = asc2_1608[num][t]; //??1608??
    else if (size == 24)
      temp = asc2_2412[num][t]; //??2412??
    else
      return; //?????
    for (t1 = 0; t1 < 8; t1++)
    {
      if (temp & 0x80)
        LTDC_Draw_Point(1, x, y, color);
      else if (mode == 0)
        LTDC_Draw_Point(1, x, y, 0xffff);
      temp <<= 1;
      y++;
#if screen_direct
      if (y >= ACTIVE_HEIGHT)
        return; //????
#else
      if (y >= ACTIVE_WIDTH)
        return; //????
#endif
      if ((y - y0) == size)
      {
        y = y0;
        x++;
#if screen_direct
        if (x >= ACTIVE_WIDTH)
          return; //????
#else
        if (x >= ACTIVE_HEIGHT)
          return; //????
#endif
        break;
      }
    }
  }
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LCD_ShowChar, LCD_ShowChar, (uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t color, uint8_t mode));
/*******************************************************************************
//m^n??  YZ
//???:m^n??.
*******************************************************************************/
uint32_t LCD_Pow(uint8_t m, uint8_t n)
{
  uint32_t result = 1;
  while (n--)
    result *= m;
  return result;
}


void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color)
{
  uint8_t t, temp;
  uint8_t enshow = 0;
  for (t = 0; t < len; t++)
  {
    temp = (num / LCD_Pow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1))
    {
      if (temp == 0)
      {
        LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0, color);
        continue;
      }
      else
        enshow = 1;
    }
    LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0, color);
  }
}

/*******************************************************************************
//?????
//x,y:????
//width,height:????
//size:????
// *p:???????
//???????????????????????????LCD_DrawPoint();????
*******************************************************************************/
void LCD_ShowString(uint16_t x, uint16_t y, uint8_t size, uint16_t color, uint8_t *p)
{
  //	uint8_t  x0=x;
  //	width+=x;
  //	height+=y;
  while ((*p <= '~') && (*p >= ' ')) //?????????!
  {
    //			if(x>=width){x=x0;y+=size;}
    //			if(y>=height)break;//??
    LCD_ShowChar(x, y, *p, size, color, 0);
    x += size / 2;
    p++;
  }
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), LCD_ShowString, LCD_ShowString, (uint16_t x, uint16_t y, uint8_t size, uint16_t color, uint8_t *p));

/* ?? ? */
int Num_count(int num)
{
  int wei = 0;
  if (num == 0)
    num = 1;
  while (num > 0)
  {
    wei++;
    int n = num % 10;
    num /= 10;
  }
  return wei;
}

int Set_Image()
{
  memcpy(ltdc_lcd_framebuf1, gImage_Image_RGB565, sizeof(gImage_Image_RGB565));
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), Set_Image, Set_Image, Set_Image);

void Set_Color(uint16_t layer,uint16_t color)
{
  if(layer == 1)
    memset(ltdc_lcd_framebuf1, color, sizeof(ltdc_lcd_framebuf1));
  else
    memset(ltdc_lcd_framebuf0, color, sizeof(ltdc_lcd_framebuf0));
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), Set_Color, Set_Color, 1 0xff00);
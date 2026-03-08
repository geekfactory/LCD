# 1 "../../../src/gf_flexlcd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/Applications/microchip/xc8/v3.10/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "../../../src/gf_flexlcd.c" 2
# 20 "../../../src/gf_flexlcd.c"
# 1 "../../../src/gf_flexlcd.h" 1
# 26 "../../../src/gf_flexlcd.h"
# 1 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdint.h" 1 3



# 1 "/Applications/microchip/xc8/v3.10/pic/include/c99/musl_xc8.h" 1 3
# 5 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdint.h" 2 3
# 26 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdint.h" 3
# 1 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 1 3
# 133 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef unsigned short uintptr_t;
# 148 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef short intptr_t;
# 164 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;
# 192 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef int32_t intmax_t;







typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;
# 233 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef uint32_t uintmax_t;
# 27 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdint.h" 2 3

typedef int8_t int_fast8_t;




typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;




typedef uint8_t uint_fast8_t;




typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;
# 148 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdint.h" 3
# 1 "/Applications/microchip/xc8/v3.10/pic/include/c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdint.h" 2 3
# 27 "../../../src/gf_flexlcd.h" 2
# 1 "/Applications/microchip/xc8/v3.10/pic/include/c99/stdbool.h" 1 3
# 28 "../../../src/gf_flexlcd.h" 2
# 1 "../../../src/gf_flexlcd_hal.h" 1
# 34 "../../../src/gf_flexlcd_hal.h"
enum enLCDControlPins
{
 E_EN_PIN,
 E_RS_PIN,
 E_RW_PIN,
};
# 49 "../../../src/gf_flexlcd_hal.h"
typedef struct
{

 void (*io_init)(void *iodata);


 void (*set_control_line)(void *iodata, enum enLCDControlPins line, _Bool value);


 void (*write_bus)(void *iodata, uint8_t data);


 void (*delay_us)(uint32_t us);


 uint8_t bus_mode;


 void * context;
} gf_flexlcd_hal_t;
# 29 "../../../src/gf_flexlcd.h" 2
# 65 "../../../src/gf_flexlcd.h"
enum enLcdCommands
{
 E_CLEAR_DISPLAY = 0x01,
 E_RETURN_HOME = 0x02,
 E_ENTRY_MODE_SET = 0x04,
 E_DISPLAY_ON_OFF_CTRL = 0x08,
 E_CURSOR_DISPLAY_SHIFT = 0x10,
 E_FUNCTION_SET = 0x20,
 E_SET_CGRAM_ADDR = 0x40,
 E_SET_DDRAM_ADDR = 0x80,
};




enum enLCDCursorModes
{
 E_LCD_CURSOR_OFF = 0x00,
 E_LCD_CURSOR_ON = 0x02,
 E_LCD_CURSOR_ON_BLINK = 0x03,
};
# 95 "../../../src/gf_flexlcd.h"
typedef struct
{
 gf_flexlcd_hal_t *hal;
 uint8_t rows;
 uint8_t cols;
 uint8_t dispctrl;
} gf_flexlcd_t;
# 129 "../../../src/gf_flexlcd.h"
 _Bool gf_flexlcd_init(gf_flexlcd_t *lcd, gf_flexlcd_hal_t *hal, uint8_t cols, uint8_t rows);
# 140 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_clear(gf_flexlcd_t *lcd);
# 151 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_home(gf_flexlcd_t *lcd);
# 164 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_on(gf_flexlcd_t *lcd);
# 175 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_off(gf_flexlcd_t *lcd);
# 193 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_cursor(gf_flexlcd_t *lcd, enum enLCDCursorModes emode);
# 203 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_cursor_left(gf_flexlcd_t *lcd);
# 213 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_cursor_right(gf_flexlcd_t *lcd);
# 224 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_scroll_left(gf_flexlcd_t *lcd);
# 235 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_scroll_right(gf_flexlcd_t *lcd);
# 247 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_autoscroll_on(gf_flexlcd_t *lcd);
# 259 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_autoscroll_off(gf_flexlcd_t *lcd);
# 273 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_goto(gf_flexlcd_t *lcd, uint8_t col, uint8_t row);
# 290 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_send(gf_flexlcd_t *lcd, uint8_t data, _Bool rs);
# 302 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_command(gf_flexlcd_t *lcd, uint8_t command);
# 315 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_putc(gf_flexlcd_t *lcd, char character);
# 327 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_puts(gf_flexlcd_t *lcd, const char *string);
# 345 "../../../src/gf_flexlcd.h"
 void gf_flexlcd_create_char(gf_flexlcd_t *lcd, uint8_t charnum, const uint8_t *chardata);
# 21 "../../../src/gf_flexlcd.c" 2

const uint8_t rowaddr[4] = {0x00, 0x40, 0x14, 0x54};

_Bool gf_flexlcd_init(gf_flexlcd_t *lcd, gf_flexlcd_hal_t *hal, uint8_t cols, uint8_t rows)
{

 lcd->hal = hal;
 lcd->cols = cols;
 lcd->rows = rows;
 lcd->dispctrl = 0;

 hal->io_init(hal->context);

 hal->delay_us(50000);


 if (hal->bus_mode == 4)
 {




  hal->set_control_line(hal->context, E_RS_PIN, 0);
  hal->set_control_line(hal->context, E_RW_PIN, 0);

  hal->write_bus(hal->context, 0x03);
  hal->delay_us(50000);
  hal->write_bus(hal->context, 0x03);
  hal->delay_us(120);
  hal->write_bus(hal->context, 0x03);
  hal->delay_us(120);

  hal->write_bus(hal->context, 0x02);
  hal->delay_us(120);

  gf_flexlcd_command(lcd, E_FUNCTION_SET | 0 | (1 << 3) | (1 << 2));
  hal->delay_us(50);
 }
 else if (hal->bus_mode == 8)
 {

  gf_flexlcd_command(lcd, E_FUNCTION_SET);
  hal->delay_us(50000);
  gf_flexlcd_command(lcd, E_FUNCTION_SET);
  hal->delay_us(120);
  gf_flexlcd_command(lcd, E_FUNCTION_SET);
  hal->delay_us(120);
  gf_flexlcd_command(lcd, E_FUNCTION_SET | (1 << 4) | (1 << 3) | (1 << 2));
  hal->delay_us(50);
 }
 else
 {
  return 0;
 }

 gf_flexlcd_command(lcd, E_DISPLAY_ON_OFF_CTRL | 0);
 hal->delay_us(50);
 gf_flexlcd_command(lcd, E_CLEAR_DISPLAY);
 hal->delay_us(2000);
 gf_flexlcd_command(lcd, E_ENTRY_MODE_SET | 0 | (1 << 1));
 hal->delay_us(50);

 return 1;
}

void gf_flexlcd_send(gf_flexlcd_t *lcd, uint8_t data, _Bool rs)
{
 gf_flexlcd_hal_t *hal = lcd->hal;


 hal->set_control_line(hal->context, E_RW_PIN, 0);

 hal->set_control_line(hal->context, E_RS_PIN, rs);

 if (hal->bus_mode == 4)
 {
  hal->write_bus(hal->context, data >> 4);
  hal->write_bus(hal->context, data);
 }
 else
 {
  hal->write_bus(hal->context, data);
 }
}

void gf_flexlcd_putc(gf_flexlcd_t *lcd, char character)
{
 gf_flexlcd_send(lcd, (uint8_t)character, 1);
}

void gf_flexlcd_command(gf_flexlcd_t *lcd, uint8_t command)
{
 gf_flexlcd_send(lcd, command, 0);
}

void gf_flexlcd_clear(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_CLEAR_DISPLAY);
 lcd->hal->delay_us(2000);
}

void gf_flexlcd_home(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_RETURN_HOME);
 lcd->hal->delay_us(2000);
}

void gf_flexlcd_on(gf_flexlcd_t *lcd)
{
 lcd->dispctrl |= (1 << 2);
 gf_flexlcd_command(lcd, E_DISPLAY_ON_OFF_CTRL | lcd->dispctrl);
 lcd->hal->delay_us(50);
}

void gf_flexlcd_off(gf_flexlcd_t *lcd)
{
 lcd->dispctrl &= ~(1 << 2);
 gf_flexlcd_command(lcd, E_DISPLAY_ON_OFF_CTRL | lcd->dispctrl);
 lcd->hal->delay_us(50);
}

void gf_flexlcd_cursor(gf_flexlcd_t *lcd, enum enLCDCursorModes mode)
{
 lcd->dispctrl &= 0xFC;
 lcd->dispctrl |= mode;
 gf_flexlcd_command(lcd, E_DISPLAY_ON_OFF_CTRL | lcd->dispctrl);
 lcd->hal->delay_us(50);
}

void gf_flexlcd_cursor_left(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | 0 | 0);
 lcd->hal->delay_us(50);
}

void gf_flexlcd_cursor_right(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | 0 | (1 << 2));
 lcd->hal->delay_us(50);
}

void gf_flexlcd_scroll_left(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | (1 << 3) | 0);
 lcd->hal->delay_us(50);
}

void gf_flexlcd_scroll_right(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | (1 << 3) | (1 << 2));
 lcd->hal->delay_us(50);
}

void gf_flexlcd_autoscroll_on(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_ENTRY_MODE_SET | (1 << 0) | (1 << 1));
 lcd->hal->delay_us(50);
}

void gf_flexlcd_autoscroll_off(gf_flexlcd_t *lcd)
{
 gf_flexlcd_command(lcd, E_ENTRY_MODE_SET | 0 | (1 << 1));
 lcd->hal->delay_us(50);
}

void gf_flexlcd_goto(gf_flexlcd_t *lcd, uint8_t col, uint8_t row)
{

 if (row >= lcd->rows)
  row = lcd->rows - 1;
 if (col >= lcd->cols)
  col = lcd->cols - 1;

 gf_flexlcd_command(lcd, E_SET_DDRAM_ADDR | (col + rowaddr[row]));
}

void gf_flexlcd_puts(gf_flexlcd_t *lcd, const char *string)
{
 while (*string != '\0')
  gf_flexlcd_putc(lcd, *string++);
}

void gf_flexlcd_create_char(gf_flexlcd_t *lcd, uint8_t charnum, const uint8_t *chardata)
{
 uint8_t i;
 charnum &= 0x07;
 gf_flexlcd_command(lcd, E_SET_CGRAM_ADDR | (uint8_t)(charnum << 3));
 for (i = 0; i < 8; i++)
  gf_flexlcd_send(lcd, chardata[i], 1);
}

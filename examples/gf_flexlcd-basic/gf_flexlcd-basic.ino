#include <Arduino.h>
#include "gf_flexlcd.h"
#include "arduino_hal.h"

gf_flexlcd_arduino_context_t lcd_context;
gf_flexlcd_hal_t lcd_hal;
gf_flexlcd_t lcd;

void setup()
{
	gf_flexlcd_arduino_init(&lcd_hal, &lcd_context, 7, 6, GF_FLEXLCD_ARDUINO_INVALID_PIN, 5, 4, 3, 2);
	gf_flexlcd_init(&lcd, &lcd_hal, 16, 2);

	gf_flexlcd_on(&lcd);
	gf_flexlcd_puts(&lcd, "FlexLCD Demo");
	gf_flexlcd_goto(&lcd, 0, 1);
	gf_flexlcd_puts(&lcd, "Geek Factory");
}

void loop()
{
	for (int i = 0; i < 3; i++)
	{
		gf_flexlcd_scroll_right(&lcd);
		delay(1000);
	}
	for (int i = 0; i < 3; i++)
	{
		gf_flexlcd_scroll_left(&lcd);
		delay(1000);
	}
}
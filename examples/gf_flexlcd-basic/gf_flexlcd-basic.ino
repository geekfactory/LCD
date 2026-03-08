/*	Geek Factory FlexLCD - Driver for HD44780 Compatible LCD Modules
	Copyright (C) 2026 Jesus Ruben Santa Anna Zamudio.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published
	by the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser 
	General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Author website: https://www.geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */
#include <Arduino.h>
#include "gf_flexlcd.h"
#include "arduino_hal.h"
// The context structure for the Arduino HAL implementation, this will hold the pin mapping for the LCD control and data lines
gf_flexlcd_arduino_context_t lcd_context;
// The HAL structure which holds function pointers for the LCD driver to call platform specific operations such as setting control lines, writing to the bus and delaying
gf_flexlcd_hal_t lcd_hal;
// The main LCD structure which holds the state of the LCD and allows us to control it through the provided API functions
gf_flexlcd_t lcd;

void setup()
{
	// Initialize the LCD context and HAL structures
	gf_flexlcd_arduino_init(&lcd_hal, &lcd_context, 7, 6, GF_FLEXLCD_INVALID_PIN, 5, 4, 3, 2);

	// Initialize IO pins and the LCD controller itself
	gf_flexlcd_init(&lcd, &lcd_hal, 16, 2);

	// Turn on the display (it is turned off by default after initialization)
	gf_flexlcd_on(&lcd);

	// print some text to the display
	gf_flexlcd_puts(&lcd, "FlexLCD Demo");
	gf_flexlcd_goto(&lcd, 0, 1);
	gf_flexlcd_puts(&lcd, "Geek Factory");
}

void loop()
{
	// scroll the display right 4 times
	for (int i = 0; i < 4; i++)
	{
		gf_flexlcd_scroll_right(&lcd);
		delay(1000);
	}
	// scroll the display left 4 times
	for (int i = 0; i < 4; i++)
	{
		gf_flexlcd_scroll_left(&lcd);
		delay(1000);
	}
}
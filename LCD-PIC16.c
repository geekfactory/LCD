/*	Driver for HD44780 Compatible LCD Modules
	Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Author website: http://www.geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */

/**
 * This file implements the functions that handle the IO port access for the
 * LCD display driver. The functions on this file can be implemented on a more
 * optimized way to save some program memory and execution time, but this is a
 * generic implementation.
 *
 * With this code, you can select any pin for any function at compile time:
 * For example, you can place LCD data bus lines on pins of different IO ports
 * at arbitrary positions.
 */

#include "LCD.h"
#include "LCD-PIC16.h"

/**
 * CHECK IF LOW BITS ON DATA BUS ARE DEFINED IN LCD-PIC16.H ARE DEFINED, IF NOT
 * WE´RE DRIVING THE LCD USING 4 BIT BUS
 */
#if defined( LCD_PIN_D0 ) && defined( LCD_PIN_D1 ) && defined( LCD_PIN_D2 ) && defined( LCD_PIN_D3 )
#define LCD_IO8
#else
#define LCD_IO4
#endif

uint8_t lcd_ioinit(void * iodata)
{
	uint8_t i = 0;

	// Configure control lines as outputs
	LCD_TRIS_E = 0;
	LCD_TRIS_RS = 0;
#if defined(LCD_PIN_RW)
	LCD_TRIS_WR = 0;
#endif
	// Configure bus data lines as outputs
#if defined(LCD_IO4)
	LCD_TRIS_D4 = 0;
	LCD_TRIS_D5 = 0;
	LCD_TRIS_D6 = 0;
	LCD_TRIS_D7 = 0;
#elif defined(LCD_IO8)
	LCD_TRIS_D0 = 0;
	LCD_TRIS_D1 = 0;
	LCD_TRIS_D2 = 0;
	LCD_TRIS_D3 = 0;
	LCD_TRIS_D4 = 0;
	LCD_TRIS_D5 = 0;
	LCD_TRIS_D6 = 0;
	LCD_TRIS_D7 = 0;
#endif
	// Set all the pins to "low" state
	for (i = 0; i < 11; i++)
		lcd_ioset(i, FALSE);

	// Return bus lenght
#if defined(LCD_IO4)
	return 4;
#else
	return 8;
#endif
}

void lcd_ioset(enum enLCDControlPins pin, uint8_t out)
{
	switch (pin) {
#if defined( LCD_IO8 )
	case E_D0_PIN:
		LCD_PIN_D0 = out;
		break;
	case E_D1_PIN:
		LCD_PIN_D1 = out;
		break;
	case E_D2_PIN:
		LCD_PIN_D2 = out;
		break;
	case E_D3_PIN:
		LCD_PIN_D3 = out;
		break;
#endif
	case E_D4_PIN:
		LCD_PIN_D4 = out;
		break;
	case E_D5_PIN:
		LCD_PIN_D5 = out;
		break;
	case E_D6_PIN:
		LCD_PIN_D6 = out;
		break;
	case E_D7_PIN:
		LCD_PIN_D7 = out;
		break;
	case E_RS_PIN:
		LCD_PIN_RS = out;
		break;
	case E_EN_PIN:
		LCD_PIN_E = out;
		break;
	case E_RW_PIN:
#if defined(LCD_PIN_RW)
		LCD_PIN_WR = 0;
#endif
		break;
	}
}

void lcd_iowrite4(uint8_t data)
{
#if defined(LCD_IO4)
	uint8_t i;

	for (i = 4; i < 8; i++)
		lcd_ioset(i, (data & (1 << i - 4)) ? TRUE : FALSE);

	lcd_iohigh(E_EN_PIN);
	delay_us(10);
	lcd_iolow(E_EN_PIN);
#endif
}

void lcd_iowrite8(uint8_t data)
{
#if defined(LCD_IO8)
	uint8_t i;

	for (i = 0; i < 8; i++)
		lcd_ioset(i, (data & (1 << i)) ? TRUE : FALSE);

	lcd_iohigh(E_EN_PIN);
	delay_us(10);
	lcd_iolow(E_EN_PIN);
#endif
}
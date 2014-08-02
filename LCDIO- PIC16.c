/*	Driver for HD44780 Compatible LCD Display Modules
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
 */

#include "LCD.h"

/**
 * This file implements the functions that handle the IO port access for the
 * LCD display driver. The functions on this file can be implemented on a more
 * optimized way to save some program memory and execution time, but this is a
 * generic implementation.
 *
 * With this code, you can select any pin for any function at compile time:
 * For example, you can place LCD data bus lines on pins of different IO ports
 */

/**
 * Definitions for common control lines
 */

#define LCD_PIN_RS	PORTBbits.RB1
#define LCD_TRIS_RS	TRISBbits.TRISB1
#define LCD_PIN_E	PORTBbits.RB0
#define LCD_TRIS_E	TRISBbits.TRISB0

/**
 * Configuration example for 4 bit mode
 */
#define LCD_PIN_D4	PORTAbits.RA0
#define LCD_PIN_D5	PORTAbits.RA1
#define LCD_PIN_D6	PORTAbits.RA2
#define LCD_PIN_D7	PORTAbits.RA3


/**
 * Configuration example for 8 bit mode
 */

//#define LCD_PIN_D0	PORTAbits.RA0
//#define LCD_PIN_D1	PORTAbits.RA1
//#define LCD_PIN_D2	PORTAbits.RA2
//#define LCD_PIN_D3	PORTAbits.RA3
//#define LCD_PIN_D4	PORTAbits.RA4
//#define LCD_PIN_D5	PORTAbits.RA5
//#define LCD_PIN_D6	PORTAbits.RA6
//#define LCD_PIN_D7	PORTAbits.RA7


BYTE lcd_ioinit(void * iodata)
{
	BYTE i = 0;
	TRISA &= 0x11110000;

	LCD_TRIS_E = 0;
	LCD_TRIS_RS = 0;

	// Set all the pins to "low" state
	for (i = 0; i < 8; i++)
		lcd_ioset(i, FALSE);

#if defined( LCD_PIN_D0 ) && defined( LCD_PIN_D1 ) && defined( LCD_PIN_D2 ) && defined( LCD_PIN_D3 )
	return 8;
#else
	return 4;
#endif
}

void lcd_ioset(enum enLCDControlPins pin, BOOL level)
{
	switch (pin) {
	case E_D0_PIN:
#if defined( LCD_PIN_D0 )
		LCD_PIN_D0 = level;
#endif
		break;
	case E_D1_PIN:
#if defined( LCD_PIN_D1 )
		LCD_PIN_D1 = level;
#endif
		break;
	case E_D2_PIN:
#if defined( LCD_PIN_D2 )
		LCD_PIN_D0 = level;
#endif
		break;
	case E_D3_PIN:
#if defined( LCD_PIN_D3 )
		LCD_PIN_D0 = level;
#endif
		break;
	case E_D4_PIN:
		LCD_PIN_D4 = level;
		break;
	case E_D5_PIN:
		LCD_PIN_D5 = level;
		break;
	case E_D6_PIN:
		LCD_PIN_D6 = level;
		break;
	case E_D7_PIN:
		LCD_PIN_D7 = level;
		break;

	case E_RS_PIN:
		LCD_PIN_RS = level;
		break;
	case E_EN_PIN:
		LCD_PIN_E = level;
		break;
	case E_RW_PIN:
		//PORTBbits.RB2 = 1;
		break;
	}
}

void lcd_iowrite4(BYTE data)
{
	BYTE i;
	//char xPortValue = (PORTA & 0xF0) | (data & 0x0F);
	//PORTA = xPortValue;

	lcd_ioset();

	// Enable Pin Pulse
	lcd_iohigh(E_EN_PIN);
	delay_us(10);
	lcd_iolow(E_EN_PIN);
}

void lcd_iowrite8(BYTE cData)
{
	PORTA = cData;
	lcd_iohigh(E_EN_PIN);
	delay_us(10);
	lcd_iolow(E_EN_PIN);
}
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

// Local variables
unsigned char rowaddr[4] = {0x00, 0x40, 0x14, 0x54};
unsigned char lcdrows = 2;
unsigned char lcdcolumns = 16;
// Local copy of the Display on off control register
unsigned char dispctrl = 0x00;
char iomode = 0;

BOOL lcd_init(void * iodata, BYTE cols, BYTE rows)
{
	// Initialize IO pins
	iomode = lcd_ioinit(iodata);
	lcdrows = rows;
	lcdcolumns = cols;

	// Initial delay after power-up
	delay_ms(100);

	//  Check if LCD interface is 8 or 4 bit mode
	if (iomode == 4) {
		// Begin LCD controller Initialization (HD44780 page 45-46)
		// Put a loop here to send these three?
		lcd_iowrite4(0x03);
		delay_ms(5);
		lcd_iowrite4(0x03);
		delay_us(120);
		lcd_iowrite4(0x03);
		delay_us(120);
		lcd_iowrite4(0x02);
		delay_us(120);
		lcd_command(E_FUNCTION_SET | BIT_DL_DATALENGTH_4 | BIT_N_DISP_LINES_2 | BIT_F_FONT_5_10);
		delay_us(50);
	} else if (iomode == 8) {
		// Begin LCD controller Initialization (HD44780 page 45-46)
		lcd_command(E_FUNCTION_SET);
		delay_ms(5);
		lcd_command(E_FUNCTION_SET);
		delay_us(120);
		lcd_command(E_FUNCTION_SET);
		delay_us(120);
		lcd_command(E_FUNCTION_SET | BIT_DL_DATALENGTH_8 | BIT_N_DISP_LINES_2 | BIT_F_FONT_5_10);
		delay_us(50);
	}
	// Configure display after power up
	lcd_command(E_DISPLAY_ON_OFF_CTRL | BIT_D_DISPLAY_OFF);
	delay_us(50);
	lcd_command(E_CLEAR_DISPLAY);
	delay_ms(2);
	lcd_command(E_ENTRY_MODE_SET | BIT_S_AUTOSCROLL_OFF | BIT_ID_INCREMENT_CURSOR);
	delay_us(50);

	return TRUE;
}

void lcd_clear()
{
	lcd_command(E_CLEAR_DISPLAY);
	delay_ms(2);
}

void lcd_home()
{
	lcd_command(E_RETURN_HOME);
	delay_ms(2);
}

void lcd_on()
{
	dispctrl |= BIT_D_DISPLAY_ON;
	lcd_command(E_DISPLAY_ON_OFF_CTRL | dispctrl);
	delay_us(50);
}

void lcd_off()
{
	dispctrl &= ~BIT_D_DISPLAY_ON;
	lcd_command(E_DISPLAY_ON_OFF_CTRL | dispctrl);
	delay_us(50);
}

void lcd_cursor(enum enLCDCursorModes mode)
{
	dispctrl &= 0xFC;
	dispctrl |= mode;
	lcd_command(E_DISPLAY_ON_OFF_CTRL | dispctrl);
	delay_us(50);
}

void lcd_cursor_left()
{
	lcd_command(E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_CURSOR | BIT_RL_SHIFT_LEFT);
	delay_us(50);
}

void lcd_cursor_right()
{
	lcd_command(E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_CURSOR | BIT_RL_SHIFT_RIGHT);
	delay_us(50);
}

void lcd_scroll_left()
{
	lcd_command(E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_DISPLAY | BIT_RL_SHIFT_LEFT);
	delay_us(50);
}

void lcd_scroll_right()
{
	lcd_command(E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_DISPLAY | BIT_RL_SHIFT_RIGHT);
	delay_us(50);
}

void lcd_goto(BYTE col, BYTE row)
{
	// Apply limits for Rows and Columns
	if (row >= lcdrows)
		row = lcdrows - 1;
	if (col >= lcdcolumns)
		col = lcdcolumns - 1;

	lcd_command(E_SET_DDRAM_ADDR | (col + rowaddr[ row ]));
}

void lcd_send(BYTE data, BOOL rs)
{
	// Write logic one to send characters or logic 0 to send a command
	if (rs)
		lcd_iohigh(E_RS_PIN);
	else
		lcd_iolow(E_RS_PIN);
	// Clear the RW pin if used
	lcd_iolow(E_RW_PIN);

	if (iomode == 4) {
		lcd_iowrite4(data >> 4);
		lcd_iowrite4(data);
	} else {
		lcd_iowrite8(data);
	}
}

void lcd_puts(const BYTE * string)
{
	while (*string != '\0')
		lcd_write(*string++);
}

void lcd_create_char(BYTE charnum, const BYTE * chardata)
{
	BYTE i;
	charnum &= 0x07;
	lcd_command(E_SET_CGRAM_ADDR | (charnum << 3));
	for (i = 0; i < 8; i++)
		lcd_write(chardata[i]);
}

/*	Geek Factory FlexLCD - Driver for HD44780 Compatible LCD Modules
	Copyright (C) 2026 Jesus Ruben Santa Anna Zamudio.

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
#include "gf_flexlcd.h"

const uint8_t rowaddr[4] = {0x00, 0x40, 0x14, 0x54};

bool gf_flexlcd_init(gf_flexlcd_t *lcd, gf_flexlcd_hal_t *hal, uint8_t cols, uint8_t rows)
{
	// store the HAL structure and LCD dimensions in the LCD structure
	lcd->hal = hal;
	lcd->cols = cols;
	lcd->rows = rows;
	lcd->dispctrl = 0;
	// Initialize the IO ports and any other platform specific setup using the HAL function pointer
	hal->io_init(hal->context);
	// initial delay after power-up
	hal->delay_us(50000);

	// check if the bus is 4 or 8 bits 
	if (hal->bus_mode == 4)
	{
		// Begin LCD controller initialization (HD44780 datasheet page 45-46), we use the write_bus function from
		// HAL directly to send the initialization commands in 4 bit mode, since the LCD is not fully initialized
		// yet and we can't use the higher level functions that rely on the LCD being in a known state.
		// Set RS and RW to low for the initialization sequence
		hal->set_control_line(hal->context, E_RS_PIN, false);
		hal->set_control_line(hal->context, E_RW_PIN, false);
		// begin 4 bit initialization sequence
		hal->write_bus(hal->context, 0x03);
		hal->delay_us(50000);
		hal->write_bus(hal->context, 0x03);
		hal->delay_us(120);
		hal->write_bus(hal->context, 0x03);
		hal->delay_us(120);
		// set to 4 bit mode
		hal->write_bus(hal->context, 0x02);
		hal->delay_us(120);
		// now that the LCD is in 4 bit mode, we can use the higher level functions to configure it
		gf_flexlcd_command(lcd, E_FUNCTION_SET | BIT_DL_DATALENGTH_4 | BIT_N_DISP_LINES_2 | BIT_F_FONT_5_10);
		hal->delay_us(50);
	}
	else if (hal->bus_mode == 8)
	{
		// Begin LCD controller Initialization (HD44780 page 45-46)
		gf_flexlcd_command(lcd, E_FUNCTION_SET);
		hal->delay_us(50000);
		gf_flexlcd_command(lcd, E_FUNCTION_SET);
		hal->delay_us(120);
		gf_flexlcd_command(lcd, E_FUNCTION_SET);
		hal->delay_us(120);
		gf_flexlcd_command(lcd, E_FUNCTION_SET | BIT_DL_DATALENGTH_8 | BIT_N_DISP_LINES_2 | BIT_F_FONT_5_10);
		hal->delay_us(50);
	}
	else
	{
		return false; // Invalid IO mode
	}
	// Configure display after power up
	gf_flexlcd_command(lcd, E_DISPLAY_ON_OFF_CTRL | BIT_D_DISPLAY_OFF);
	hal->delay_us(50);
	gf_flexlcd_command(lcd, E_CLEAR_DISPLAY);
	hal->delay_us(2000);
	gf_flexlcd_command(lcd, E_ENTRY_MODE_SET | BIT_S_AUTOSCROLL_OFF | BIT_ID_INCREMENT_CURSOR);
	hal->delay_us(50);

	return true;
}

void gf_flexlcd_send(gf_flexlcd_t *lcd, uint8_t data, bool rs)
{
	gf_flexlcd_hal_t *hal = lcd->hal;

	// Set RW to low for write operation
	hal->set_control_line(hal->context, E_RW_PIN, false);
	// write 1 to send characters  0 to send a command
	hal->set_control_line(hal->context, E_RS_PIN, rs);
	// check if the LCD is physically connected on a 4 or 8 bit bus and send the data accordingly
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
	lcd->dispctrl |= BIT_D_DISPLAY_ON;
	gf_flexlcd_command(lcd, E_DISPLAY_ON_OFF_CTRL | lcd->dispctrl);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_off(gf_flexlcd_t *lcd)
{
	lcd->dispctrl &= ~BIT_D_DISPLAY_ON;
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
	gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_CURSOR | BIT_RL_SHIFT_LEFT);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_cursor_right(gf_flexlcd_t *lcd)
{
	gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_CURSOR | BIT_RL_SHIFT_RIGHT);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_scroll_left(gf_flexlcd_t *lcd)
{
	gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_DISPLAY | BIT_RL_SHIFT_LEFT);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_scroll_right(gf_flexlcd_t *lcd)
{
	gf_flexlcd_command(lcd, E_CURSOR_DISPLAY_SHIFT | BIT_SC_SHIFT_DISPLAY | BIT_RL_SHIFT_RIGHT);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_autoscroll_on(gf_flexlcd_t *lcd)
{
	gf_flexlcd_command(lcd, E_ENTRY_MODE_SET | BIT_S_AUTOSCROLL_ON | BIT_ID_INCREMENT_CURSOR);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_autoscroll_off(gf_flexlcd_t *lcd)
{
	gf_flexlcd_command(lcd, E_ENTRY_MODE_SET | BIT_S_AUTOSCROLL_OFF | BIT_ID_INCREMENT_CURSOR);
	lcd->hal->delay_us(50);
}

void gf_flexlcd_goto(gf_flexlcd_t *lcd, uint8_t col, uint8_t row)
{
	// Apply limits for Rows and Columns
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

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
#include "pic_hal_mini.h"

inline static void pic_pulse_enable(void *context)
{
	PORTB |= 0x10;
	__delay_us(1);
	PORTB &= ~0x10;
}

static void pic_io_init(void *context)
{
	// Set data pins (RB0-RB3) and control pins (RB4-RB5) as outputs
	TRISB &= ~0x3F;
	// Initialize all control and data lines to low
	PORTB &= ~0x3F;
}

static void pic_set_control_line(void *context, enum enLCDControlPins line, bool value)
{
	switch (line)
	{
	case E_RS_PIN:
		if (value)
			PORTB |= 0x20; // Set RB5
		else
			PORTB &= ~0x20; // Clear RB5
		break;
	case E_EN_PIN:
		if (value)
			PORTB |= 0x10; // Set RB4
		else
			PORTB &= ~0x10; // Clear RB4
		break;
	default:
		break;
	}
}

static void pic_write_bus(void *context, uint8_t data)
{
	// Clear the data bits (RB0-RB3) and set them according to data
	PORTB &= ~0x0F;
	PORTB |= (data & 0x0F);
	// Pulse the enable line to latch the data
	pic_pulse_enable(context);
}

static void pic_delay_us(uint32_t us)
{
	while (us--)
		__delay_us(1);
}

void gf_flexlcd_pic_mini_init(gf_flexlcd_hal_t *hal)
{
	hal->io_init = pic_io_init;
	hal->set_control_line = pic_set_control_line;
	hal->write_bus = pic_write_bus;
	hal->delay_us = pic_delay_us;
	hal->bus_mode = 4;
	hal->context = NULL;
}

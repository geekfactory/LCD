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
#include "arduino_hal.h"

inline static void arduino_pulse_enable(void *context)
{
	gf_flexlcd_arduino_context_t *hal_context = (gf_flexlcd_arduino_context_t *)context;

	digitalWrite(hal_context->en, HIGH);
	delayMicroseconds(1);
	digitalWrite(hal_context->en, LOW);
}

static void arduino_io_init(void *context)
{
	gf_flexlcd_arduino_context_t *hal_context = (gf_flexlcd_arduino_context_t *)context;

	// Set pin modes for control and data lines
	if (hal_context->rw != GF_FLEXLCD_INVALID_PIN)
		pinMode(hal_context->rw, OUTPUT);
	pinMode(hal_context->rs, OUTPUT);
	pinMode(hal_context->en, OUTPUT);
	pinMode(hal_context->d4, OUTPUT);
	pinMode(hal_context->d5, OUTPUT);
	pinMode(hal_context->d6, OUTPUT);
	pinMode(hal_context->d7, OUTPUT);

	// initialize lines to default state
	if (hal_context->rw != GF_FLEXLCD_INVALID_PIN)
		digitalWrite(hal_context->rw, LOW);
	digitalWrite(hal_context->rs, LOW);
	digitalWrite(hal_context->en, LOW);
	digitalWrite(hal_context->d4, LOW);
	digitalWrite(hal_context->d5, LOW);
	digitalWrite(hal_context->d6, LOW);
	digitalWrite(hal_context->d7, LOW);
}

static void arduino_set_control_line(void *context, enum enLCDControlPins line, bool value)
{
	gf_flexlcd_arduino_context_t *hal_context = (gf_flexlcd_arduino_context_t *)context;

	switch (line)
	{
	case E_RS_PIN:
		digitalWrite(hal_context->rs, value ? HIGH : LOW);
		break;
	case E_EN_PIN:
		digitalWrite(hal_context->en, value ? HIGH : LOW);
		break;
	case E_RW_PIN:
		if (hal_context->rw != GF_FLEXLCD_INVALID_PIN)
			digitalWrite(hal_context->rw, value ? HIGH : LOW);
		break;
	default:
		// Invalid control line, do nothing
		break;
	}
}

static void arduino_write_bus(void *context, uint8_t nibble)
{
	gf_flexlcd_arduino_context_t *hal_context = (gf_flexlcd_arduino_context_t *)context;

	digitalWrite(hal_context->d4, (nibble >> 0) & 0x01);
	digitalWrite(hal_context->d5, (nibble >> 1) & 0x01);
	digitalWrite(hal_context->d6, (nibble >> 2) & 0x01);
	digitalWrite(hal_context->d7, (nibble >> 3) & 0x01);

	arduino_pulse_enable(context);
}

static void arduino_delay_us(uint32_t us)
{
	delayMicroseconds(us);
}

void gf_flexlcd_arduino_init(gf_flexlcd_hal_t *hal, gf_flexlcd_arduino_context_t *context, uint8_t rs, uint8_t en, uint8_t rw, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	// store pin numbers in the context structure
	context->rs = rs;
	context->en = en;
	context->rw = rw;
	context->d4 = d4;
	context->d5 = d5;
	context->d6 = d6;
	context->d7 = d7;

	// Initialize the HAL structure with function pointers and IO pin context
	hal->io_init = arduino_io_init;
	hal->set_control_line = arduino_set_control_line;
	hal->write_bus = arduino_write_bus;
	hal->delay_us = arduino_delay_us;
	hal->bus_mode = 4;
	hal->context = context;
}

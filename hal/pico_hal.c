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
#include "pico_hal.h"

static inline void pico_pulse_enable(gf_flexlcd_pico_fast_ctx_t *ctx)
{
	sio_hw->gpio_set = ctx->en_mask;
	sleep_us(1);
	sio_hw->gpio_clr = ctx->en_mask;
}

static void pico_io_init(void *context)
{
	gf_flexlcd_pico_fast_ctx_t *ctx = context;
	uint32_t pins = ctx->rs_mask | ctx->en_mask | ctx->rw_mask | ctx->data_mask;
	for (int i = 0; i < 30; i++)
	{
		if (pins & (1u << i))
		{
			gpio_init(i);
			gpio_set_dir(i, GPIO_OUT);
		}
	}
	sio_hw->gpio_clr = pins;
}

static void pico_set_control_line(void *context, enum enLCDControlPins line, bool value)
{
	gf_flexlcd_pico_fast_ctx_t *ctx = context;

	uint32_t mask = 0;

	switch (line)
	{
	case E_RS_PIN:
		mask = ctx->rs_mask;
		break;
	case E_EN_PIN:
		mask = ctx->en_mask;
		break;
	case E_RW_PIN:
		mask = ctx->rw_mask;
		break;
	default:
		return;
	}

	if (value)
		sio_hw->gpio_set = mask;
	else
		sio_hw->gpio_clr = mask;
}

static void pico_write_bus(void *context, uint8_t nibble)
{
	gf_flexlcd_pico_fast_ctx_t *ctx = context;

	uint32_t set_mask = 0;

	if (nibble & 0x01)
		set_mask |= ctx->d4_mask;
	if (nibble & 0x02)
		set_mask |= ctx->d5_mask;
	if (nibble & 0x04)
		set_mask |= ctx->d6_mask;
	if (nibble & 0x08)
		set_mask |= ctx->d7_mask;

	// clear data pins
	sio_hw->gpio_clr = ctx->data_mask;
	// set required pins
	sio_hw->gpio_set = set_mask;

	pico_pulse_enable(ctx);
}

static void pico_delay_us(uint32_t us)
{
	sleep_us(us);
}

void gf_flexlcd_pico_init(gf_flexlcd_hal_t *hal, gf_flexlcd_pico_fast_ctx_t *ctx,
			  uint8_t rs,
			  uint8_t en,
			  uint8_t rw,
			  uint8_t d4,
			  uint8_t d5,
			  uint8_t d6,
			  uint8_t d7)
{
	ctx->rs_mask = 1u << rs;
	ctx->en_mask = 1u << en;
	if (rw == GF_FLEXLCD_INVALID_PIN)
		ctx->rw_mask = 0;
	else
		ctx->rw_mask = 1u << rw;
	ctx->d4_mask = 1u << d4;
	ctx->d5_mask = 1u << d5;
	ctx->d6_mask = 1u << d6;
	ctx->d7_mask = 1u << d7;
	ctx->data_mask = ctx->d4_mask | ctx->d5_mask | ctx->d6_mask | ctx->d7_mask;

	hal->io_init = pico_io_init;
	hal->set_control_line = pico_set_control_line;
	hal->write_bus = pico_write_bus;
	hal->delay_us = pico_delay_us;
	hal->bus_mode = 4;
	hal->context = ctx;
}
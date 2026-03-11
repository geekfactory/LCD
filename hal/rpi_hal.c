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
#include <gpiod.h>
#include <unistd.h>

#include "gf_flexlcd_hal.h"
#include "rpi_hal.h"

static void rpi_io_init(void *context)
{
	gf_flexlcd_rpi_context_t *ctx = context;

	gpiod_line_request_output(ctx->rs, "flexlcd", 0);
	gpiod_line_request_output(ctx->en, "flexlcd", 0);
	if (ctx->rw)
		gpiod_line_request_output(ctx->rw, "flexlcd", 0);
	gpiod_line_request_output(ctx->d4, "flexlcd", 0);
	gpiod_line_request_output(ctx->d5, "flexlcd", 0);
	gpiod_line_request_output(ctx->d6, "flexlcd", 0);
	gpiod_line_request_output(ctx->d7, "flexlcd", 0);
}

static void rpi_set_control_line(void *context, enum enLCDControlPins line, bool value)
{
	gf_flexlcd_rpi_context_t *ctx = context;

	switch (line)
	{
	case E_RS_PIN:
		gpiod_line_set_value(ctx->rs, value);
		break;
	case E_EN_PIN:
		gpiod_line_set_value(ctx->en, value);
		break;
	case E_RW_PIN:
		if (ctx->rw)
			gpiod_line_set_value(ctx->rw, value);
		break;
	default:
		break;
	}
}

static void rpi_write_bus(void *context, uint8_t nibble)
{
	gf_flexlcd_rpi_context_t *ctx = context;

	gpiod_line_set_value(ctx->d4, (nibble >> 0) & 1);
	gpiod_line_set_value(ctx->d5, (nibble >> 1) & 1);
	gpiod_line_set_value(ctx->d6, (nibble >> 2) & 1);
	gpiod_line_set_value(ctx->d7, (nibble >> 3) & 1);

	gpiod_line_set_value(ctx->en, 1);
	usleep(1);
	gpiod_line_set_value(ctx->en, 0);
}

static void rpi_delay_us(uint32_t us)
{
	usleep(us);
}

bool gf_flexlcd_rpi_init(gf_flexlcd_hal_t *hal, gf_flexlcd_rpi_context_t *ctx, const char *chipname,
			 int rs,
			 int en,
			 int rw,
			 int d4,
			 int d5,
			 int d6,
			 int d7)
{
	ctx->chip = gpiod_chip_open_by_name(chipname);

	if (!ctx->chip)
		return false;

	ctx->rs = gpiod_chip_get_line(ctx->chip, rs);
	ctx->en = gpiod_chip_get_line(ctx->chip, en);

	ctx->d4 = gpiod_chip_get_line(ctx->chip, d4);
	ctx->d5 = gpiod_chip_get_line(ctx->chip, d5);
	ctx->d6 = gpiod_chip_get_line(ctx->chip, d6);
	ctx->d7 = gpiod_chip_get_line(ctx->chip, d7);

	if (rw == GF_FLEXLCD_INVALID_PIN)
		ctx->rw = NULL;
	else
		ctx->rw = gpiod_chip_get_line(ctx->chip, rw);

	hal->io_init = rpi_io_init;
	hal->set_control_line = rpi_set_control_line;
	hal->write_bus = rpi_write_bus;
	hal->delay_us = rpi_delay_us;
	hal->bus_mode = 4;
	hal->context = ctx;

	return true;
}
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
#ifndef RPI_HAL_H
#define RPI_HAL_H
// This library uses libgpiod to access GPIO pins on linux devices
#include <gpiod.h>
#include "gf_flexlcd_hal.h"

typedef struct
{
	struct gpiod_chip *chip;
	struct gpiod_line *rs;
	struct gpiod_line *rw;
	struct gpiod_line *en;
	struct gpiod_line *d4;
	struct gpiod_line *d5;
	struct gpiod_line *d6;
	struct gpiod_line *d7;

} gf_flexlcd_rpi_context_t;

bool gf_flexlcd_rpi_init(gf_flexlcd_hal_t *hal, gf_flexlcd_rpi_context_t *ctx, const char *chipname,
			 int rs,
			 int en,
			 int rw,
			 int d4,
			 int d5,
			 int d6,
			 int d7);

#endif
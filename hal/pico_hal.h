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
#ifndef PICO_HAL_H
#define PICO_HAL_H

#include <stdint.h>
#include <stdbool.h>

#include "hardware/gpio.h"
#include "hardware/structs/sio.h"
#include "pico/stdlib.h"

#include "gf_flexlcd_hal.h"

typedef struct
{
	uint32_t rs_mask;
	uint32_t en_mask;
	uint32_t rw_mask;
	uint32_t d4_mask;
	uint32_t d5_mask;
	uint32_t d6_mask;
	uint32_t d7_mask;
	uint32_t data_mask;
} gf_flexlcd_pico_context_t;

void gf_flexlcd_pico_init(gf_flexlcd_hal_t *hal, gf_flexlcd_pico_context_t *ctx,
			  uint8_t rs,
			  uint8_t en,
			  uint8_t rw,
			  uint8_t d4,
			  uint8_t d5,
			  uint8_t d6,
			  uint8_t d7);

#endif
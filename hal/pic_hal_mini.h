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
#ifndef PIC_HAL_MINI_H
#define PIC_HAL_MINI_H

#include <XC.h>
#include <stdint.h>
#include <stdbool.h>
#include "gf_flexlcd_hal.h"

#define _XTAL_FREQ 4000000

/**
 * @brief Initializes the HAL for a PIC microcontroller with a minimal pinout.
 * 
 * Minimal implementation for PIC microcontrollers, uses a single port for data and control lines.
 * 
 * Using this HAL doesn't allow multiple LCD instances, as the port and pins are hardcoded.
 * It's intended for simple projects where only one LCD is needed and RAM usage must be minimized.
 * 
 * @param hal Pointer to the HAL structure to initialize.
 */
void gf_flexlcd_pic_mini_init(gf_flexlcd_hal_t *hal);

#endif // PIC_HAL_MINI_H
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
#ifndef GF_FLEXLCD_HAL_H
#define GF_FLEXLCD_HAL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Value used for invalid pins
 */
#define GF_FLEXLCD_INVALID_PIN 255

/**
 * Enumeration defining the LCD control pins
 */
enum enLCDControlPins
{
	E_EN_PIN,
	E_RS_PIN,
	E_RW_PIN,
};

/**
 * @brief Structure that contains information of the HAL.
 *
 * Structure defining the Hardware Abstraction Layer (HAL) for the FlexLCD
 * driver. This structure contains function pointers for platform-specific
 * operations such as initializing IO, setting control lines, writing to the bus,
 * and generating the required delays on different platforms.
 */
typedef struct
{
	/**  Function pointer to initialize the IO ports and any other platform specific setup needed to operate the LCD */
	void (*io_init)(void *iodata);

	/** Function pointer to set the state of a control line as defined in enum enLCDControlPins */
	void (*set_control_line)(void *iodata, enum enLCDControlPins line, bool value);

	/** Function pointer to write data to the LCD bus */
	void (*write_bus)(void *iodata, uint8_t data);

	/** Function pointer to delay for a specified number of microseconds */
	void (*delay_us)(uint32_t us);

	/** Used to indicate the bus mode (4 or 8 bits) */
	uint8_t bus_mode;

	/** Context pointer for platform-specific IO control data */
	void *context;
} gf_flexlcd_hal_t;

#endif // GF_FLEXLCD_HAL_H
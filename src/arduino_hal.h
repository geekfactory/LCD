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
#include "gf_flexlcd_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * @brief Arduino-specific context structure for the LCD HAL
	 *
	 * This structure holds the pin numbers for the control and data lines of the LCD
	 * when using the Arduino platform. It is used as the context for the HAL functions
	 * to know which pins to manipulate.
	 */
	typedef struct
	{
		uint8_t rs;
		uint8_t en;
		uint8_t rw;
		uint8_t d4;
		uint8_t d5;
		uint8_t d6;
		uint8_t d7;
	} gf_flexlcd_arduino_context_t;

	/**
	 * @brief Initializes the LCD HAL structure for Arduino platform
	 *
	 * This function initializes the LCD HAL structure with the appropriate function pointers for the Arduino platform
	 * and stores the pin numbers in the context structure.
	 *
	 * @param hal A pointer to the gf_flexlcd_hal_t structure to initialize
	 * @param context A pointer to the gf_flexlcd_arduino_context_t structure to store IO information
	 * @param rs The pin number connected to the RS line of the LCD
	 * @param en The pin number connected to the EN line of the LCD
	 * @param rw The pin number connected to the RW line of the LCD (set to 0 if not used)
	 * @param d4 The pin number connected to the D4 line of the LCD (used in 4-bit mode)
	 * @param d5 The pin number connected to the D5 line of the LCD (used in 4-bit mode)
	 * @param d6 The pin number connected to the D6 line of the LCD (used in 4-bit mode)
	 * @param d7 The pin number connected to the D7 line of the LCD (used in 4-bit mode)
	 */
	void gf_flexlcd_arduino_init(gf_flexlcd_hal_t *hal, gf_flexlcd_arduino_context_t *context, uint8_t rs, uint8_t en, uint8_t rw, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

#ifdef __cplusplus
}
#endif
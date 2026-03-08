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

	Author website: https://www.geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */
#ifndef GF_FLEXLCD_H
#define GF_FLEXLCD_H

/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "gf_flexlcd_hal.h"

/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/
// Entry Mode Set Control Bits
#define BIT_S_AUTOSCROLL_ON (1 << 0)	 //!< Enable autoscroll. For use with Entry Mode Set command
#define BIT_S_AUTOSCROLL_OFF 0		 //!< Disable autoscroll. For use with Entry Mode Set command
#define BIT_ID_INCREMENT_CURSOR (1 << 1) //!< Increment cursor position after each char. For use with Entry Mode Set command
#define BIT_ID_DECREMENT_CURSOR 0	 //!< Decrement cursor position after each char. For use with Entry Mode Set command
// Display On/Off Control Bits
#define BIT_B_CURSOR_BLINK (1 << 0)
#define BIT_B_CURSOR_NO_BLINK 0
#define BIT_C_CURSOR_ON (1 << 1)
#define BIT_C_CURSOR_OFF 0
#define BIT_D_DISPLAY_ON (1 << 2)
#define BIT_D_DISPLAY_OFF 0
// Cursor / Display Shift Control Bits
#define BIT_RL_SHIFT_RIGHT (1 << 2)
#define BIT_RL_SHIFT_LEFT 0
#define BIT_SC_SHIFT_DISPLAY (1 << 3) //!< Seting this bit causes a display scroll
#define BIT_SC_SHIFT_CURSOR 0	      //!< Clearing this bits causes a cursor move
// Function set Control Bits
#define BIT_F_FONT_5_10 (1 << 2)
#define BIT_F_FONT_5_8 0
#define BIT_N_DISP_LINES_2 (1 << 3)
#define BIT_N_DISP_LINES_1 0
#define BIT_DL_DATALENGTH_8 (1 << 4)
#define BIT_DL_DATALENGTH_4 0

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/

/**
 * Enumeration defining the HD44780 commands
 */
enum enLcdCommands
{
	E_CLEAR_DISPLAY = 0x01,
	E_RETURN_HOME = 0x02,
	E_ENTRY_MODE_SET = 0x04,
	E_DISPLAY_ON_OFF_CTRL = 0x08,
	E_CURSOR_DISPLAY_SHIFT = 0x10,
	E_FUNCTION_SET = 0x20,
	E_SET_CGRAM_ADDR = 0x40,
	E_SET_DDRAM_ADDR = 0x80,
};

/**
 * This enumeration defines the available cursor modes
 */
enum enLCDCursorModes
{
	E_LCD_CURSOR_OFF = 0x00,
	E_LCD_CURSOR_ON = 0x02,
	E_LCD_CURSOR_ON_BLINK = 0x03,
};

/**
 * This structure represents the LCD display and contains the necessary
 * information to operate it.
 *
 * The structure contains a pointer to the LCD HAL structure, the number of rows
 * and columns of the display and the current display control settings (display
 * on/off, cursor on/off, blink on/off).
 */
typedef struct
{
	gf_flexlcd_hal_t *hal;
	uint8_t rows;
	uint8_t cols;
	uint8_t dispctrl;
} gf_flexlcd_t;

/*-------------------------------------------------------------*/
/*		Function prototypes				*/
/*-------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * @brief Initializes the LCD IO pins and HD44780 controller.
	 *
	 * This function prepares the resources needed to operate an HD44780 compatible
	 * display. The IO Ports initialization and the LCD controller chip preparation
	 * sequences are performed here.
	 *
	 * The Initialization routine leaves the display disabled. To see the written
	 * text you should enable it by calling gf_flexlcd_on() function.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure
	 * @param hal A pointer to a gf_flexlcd_hal_t structure
	 * @param cols The number of columns present on the display (number of
	 * horizontal characters)
	 * @param rows The number of rows that the display can show (text lines)
	 *
	 * @return Returns true if the LCD was succesfully initialized, false otherwise.
	 */
	bool gf_flexlcd_init(gf_flexlcd_t *lcd, gf_flexlcd_hal_t *hal, uint8_t cols, uint8_t rows);

	/**
	 * @brief  Clears the entire LCD display.
	 *
	 * Clears the LCD and returns the cursor to the home position. All data on the
	 * display controller's RAM memory is cleared.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_clear(gf_flexlcd_t *lcd);

	/**
	 * @brief Returns the cursor to home position.
	 *
	 * This function returns the cursor to the begining of the DDRAM memory without
	 * affecting it's contents.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_home(gf_flexlcd_t *lcd);

	/**
	 * @brief Turns on the display and shows the DDRAM contents.
	 *
	 * This function sends a command to turn the display ON and shows the contents
	 * of the DDRAM on the screen. After the Initialization of the LCD controller,
	 * the display is turned Off, so you need to call this function before you see
	 * anything on screen.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_on(gf_flexlcd_t *lcd);

	/**
	 * @brief Turns off the display.
	 *
	 * This function turns off the display and hides the content of the DDRAM,
	 * however the data on the DDRAM (display memory) is NOT cleared.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_off(gf_flexlcd_t *lcd);

	/**
	 * @brief Set the cursor display mode.
	 *
	 * Turns on the cursor and sets the cursor display mode to one of the following:
	 *
	 * - E_LCD_CURSOR_OFF - Dont display the cursor (default setting).
	 * - E_LCD_CURSOR_ON - Show cursor as a small line under the letters
	 * - E_LCD_CURSOR_ON_BLINK - Shows cursor as a blinking square
	 *
	 * As defined in enum enLCDCursorModes.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param emode The display mode of the cursor.
	 *
	 */
	void gf_flexlcd_cursor(gf_flexlcd_t *lcd, enum enLCDCursorModes emode);

	/**
	 * @brief Moves the cursor one position to the left.
	 *
	 * Sends a command to move the cursor one position to the left.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_cursor_left(gf_flexlcd_t *lcd);

	/**
	 * @brief Moves the cursor one position to the right.
	 *
	 * Sends a command to move the cursor one position to the right.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_cursor_right(gf_flexlcd_t *lcd);

	/**
	 * @brief Scrolls the display viewport to the left.
	 *
	 * Scrolls the viewport one position to the left, cursor position is also
	 * affected.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_scroll_left(gf_flexlcd_t *lcd);

	/**
	 * @brief Scrolls the display viewport to the right.
	 *
	 * Scrolls the viewport one position to the right, cursor position is also
	 * affected.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_scroll_right(gf_flexlcd_t *lcd);

	/**
	 * @brief Enables LCD autoscroll mode.
	 *
	 * Enables autoscroll function when new characters are written to the LCD module.
	 * When autoscroll is enabled, the display will automatically scroll to the left
	 * when a new character is written to the rightmost position of the display.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_autoscroll_on(gf_flexlcd_t *lcd);

	/**
	 * @brief Disables LCD autoscroll mode.
	 *
	 * Disables the autoscroll function. When autoscroll is disabled, the display
	 * will not scroll when new characters are written to the rightmost position of
	 * the display.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 */
	void gf_flexlcd_autoscroll_off(gf_flexlcd_t *lcd);

	/**
	 * @brief Moves the cursor to the given position.
	 *
	 * This functions sets the cursor position on the DDRAM. If cursor display is
	 * enabled (using gf_flexlcd_cursor()), cursor will also be shown on the display.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param col The column of the LCD to place the cursor, with 0 being the
	 * leftmost position on the display.
	 * @param row The row on the LCD to place the cursor, where the top row is 0.
	 */
	void gf_flexlcd_goto(gf_flexlcd_t *lcd, uint8_t col, uint8_t row);

	/**
	 * @brief Writes data or a command to the LCD display.
	 *
	 * This function writes a single character to the current cursor position OR
	 * sends a command to the LCD display controller.
	 * The parameter "rs", indicates if the data is command or char, and should be
	 * set to true if the data presented to this function is a character or false if
	 * the data is a command to the LCD controller.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param data The data or command byte to send to the LCD
	 * @param rs A boolean value indicating if the previous parameter was a
	 * character to display (true) or a command (false) to the LCD controller.
	 */
	void gf_flexlcd_send(gf_flexlcd_t *lcd, uint8_t data, bool rs);

	/**
	 * @brief Writes a command to the LCD controller.
	 *
	 * Helper function that calls gf_flexlcd_send() with the "rs" parameter set to
	 * false, indicating that the data being sent is a command.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param command The command byte to send to the LCD controller.
	 */
	void gf_flexlcd_command(gf_flexlcd_t *lcd, uint8_t command);

	/**
	 * @brief Writes a character to LCD controller's DDRAM.
	 *
	 * Helper function that calls gf_flexlcd_send() with the "rs" parameter set to
	 * true, indicating that the data being sent is a character to display.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param character The character to write to the LCD display at the current
	 * cursor position.
	 */
	void gf_flexlcd_putc(gf_flexlcd_t *lcd, char character);

	/**
	 * @brief Writes a string to the current LCD position.
	 *
	 * Writes a null terminated string to the current position on DDRAM.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param string Pointer to the string to write to the screen. The string must
	 * be null terminated.
	 */
	void gf_flexlcd_puts(gf_flexlcd_t *lcd, const char *string);

	/**
	 * @brief Writes a custom character to CGRAM.
	 *
	 * This function allows the user to define up to 8 personalized characters that
	 * can be displayed by sending the appropiate code using the gf_flexlcd_putc()
	 * function.
	 *
	 * The custom character number and the char bitmap are passed to this function
	 * and it writes to the proper CGRAM address.
	 *
	 * @param lcd A pointer to a gf_flexlcd_t structure that is used to aceess the
	 * display instance.
	 * @param charnum The number for the custom character to define.
	 * @param chardata The character bitmap. Each custom character is composed of
	 * 8 bytes which are read from the provided data buffer.
	 */
	void gf_flexlcd_create_char(gf_flexlcd_t *lcd, uint8_t charnum, const uint8_t *chardata);

#ifdef __cplusplus
}
#endif

#endif // GF_FLEXLCD_H
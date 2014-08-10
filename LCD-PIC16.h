/*	Driver for HD44780 Compatible LCD Modules
	Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

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

	Author website: http://www.geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */
#ifndef LCD_PIC16_H
#define	LCD_PIC16_H
/*-------------------------------------------------------------*/
/*		Configuration for Control Signals		*/
/*-------------------------------------------------------------*/
#define LCD_PIN_RS	PORTBbits.RB1
#define LCD_TRIS_RS	TRISBbits.TRISB1
#define LCD_PIN_E	PORTBbits.RB0
#define LCD_TRIS_E	TRISBbits.TRISB0
// NOT NEEDED YET, CONNECT RW TO GROUND
//#define LCD_PIN_RW	PORTBbits.RB2
//#define LCD_TRIS_RW	TRISBbits.TRISB2

/*-------------------------------------------------------------*/
/*		Configuration example: 4 bit mode		*/
/*-------------------------------------------------------------*/
#define LCD_TRIS_D4	TRISAbits.TRISA0
#define LCD_TRIS_D5	TRISAbits.TRISA1
#define LCD_TRIS_D6	TRISAbits.TRISA2
#define LCD_TRIS_D7	TRISAbits.TRISA3

#define LCD_PIN_D4	PORTAbits.RA0
#define LCD_PIN_D5	PORTAbits.RA1
#define LCD_PIN_D6	PORTAbits.RA2
#define LCD_PIN_D7	PORTAbits.RA3

/*-------------------------------------------------------------*/
/*		Configuration example: 8 bit mode		*/
/*-------------------------------------------------------------*/
//#define LCD_TRIS_D0	TRISAbits.TRISA0
//#define LCD_TRIS_D1	TRISAbits.TRISA1
//#define LCD_TRIS_D2	TRISAbits.TRISA2
//#define LCD_TRIS_D3	TRISAbits.TRISA3
//#define LCD_TRIS_D4	TRISAbits.TRISA0
//#define LCD_TRIS_D5	TRISAbits.TRISA1
//#define LCD_TRIS_D6	TRISAbits.TRISA2
//#define LCD_TRIS_D7	TRISAbits.TRISA3

//#define LCD_PIN_D0	PORTAbits.RA0
//#define LCD_PIN_D1	PORTAbits.RA1
//#define LCD_PIN_D2	PORTAbits.RA2
//#define LCD_PIN_D3	PORTAbits.RA3
//#define LCD_PIN_D4	PORTAbits.RA4
//#define LCD_PIN_D5	PORTAbits.RA5
//#define LCD_PIN_D6	PORTAbits.RA6
//#define LCD_PIN_D7	PORTAbits.RA7

#define CONFIG_TIMING_MAIN_CLOCK	1000000

#endif
// End of Header file

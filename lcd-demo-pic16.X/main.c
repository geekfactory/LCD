/************************* http://geekfactory.mx *******************************
 *
 * Demo for the "tick" library for time management, non-blocking delays and
 * event scheduling. In this program we toggle a led connected to the bit 0 on
 * A port, without the need to stop the program with a call to a delay function.
 *
 * Demostración de la librería "tick" para manejo de tiempos, retardos sin
 * bloqueo y programación de eventos. En este demo, se hace parpadear un led
 * conectado al puerto A en el bit 0, sin la necesidad de detener el programa
 * con una llamada a una función de retardo (delay).
 *
 * AUTHOR/AUTOR: Jesus Ruben Santa Anna Zamudio
 * MICROCONTROLLER/MICROCONTROLADOR: PIC16F88, PIC16F628
 * COMPILER/COMPILADOR: Microchip XC8 http://www.microchip.com/compilers
 *
 ********************************************************************************/
#define CONFIG_TIMING_MAIN_CLOCK 1000000
#include <xc.h>			// Encabezado para el compilador XC8
#include "../LCD.h"

/* Device specific configuration */
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON	// RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

// Definicion de caracteres personalizados
const char arrowr[8] = {
	0b00001000,
	0b00000100,
	0b00000010,
	0b00011111,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00000000,
};

const char arrowu[8] = {
	0b00000100,
	0b00001110,
	0b00010101,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000000,
};

const char arrowd[8] = {
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00010101,
	0b00001110,
	0b00000100,
	0b00000000,
};

const char arrowl[8] = {
	0b00000010,
	0b00000100,
	0b00001000,
	0b00011111,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000000,
};

void main( )
{
	int i;

	ANSEL = 0x00;
	TRISA = 0xFE;
	TRISB = 0x7F;

	// Initialize lcd driver
	lcd_init( 0, 16, 2 );

	// Load characters to CGRAM
	lcd_create_char( 0, arrowr );
	lcd_create_char( 1, arrowu );
	lcd_create_char( 2, arrowl );
	lcd_create_char( 3, arrowd );

	// Clear screen to end write to character generator
	lcd_clear( );
	// Turn on display
	lcd_on( );
	// Display message on the first row
	lcd_puts( "LCD Test Program" );
	// Move cursor to the fourth column on second line
	lcd_goto( 3, 1 );
	// Print a message there
	lcd_puts( "Hello World" );
	// Mover cursor to the sixteenth column on second row
	lcd_goto( 15, 1 );

	// Main loop
	for(;; ) {
		for( i = 0; i < 4; i++ ) {
			delay_ms( 250 );
			PORTBbits.RB7 = 0;
			delay_ms( 250 );
			PORTBbits.RB7 = 1;
			lcd_write( i );
			// Goto the last visible position on the screen
			lcd_goto( 50, 50 );
		}
	}
}

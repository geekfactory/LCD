#include "../LCD.h"
#include "../../UART/UART.h"

#define MATRIX_SET_CURSOR		71
#define MATRIX_CURSOR_HOME		72
#define MATRIX_CURSOR_UNDERLINE_ON	74
#define MATRIX_CURSOR_UNDERLINE_OFF	75
#define MATRIX_CURSOR_BLOCK_ON		83
#define MATRIX_CURSOR_BLOCK_OFF		84
#define MATRIX_CURSOR_LEFT		76
#define MATRIX_CURSOR_RIGHT		77
#define MATRIX_CUSTOM_CHAR		78
#define MATRIX_READ_VERSION		54
#define MATRIX_MODULE_TYPE		55

#define MATRIX_SET_CONTRAST		80
#define MATRIX_AUTOSCROLL_ON		81
#define MATRIX_AUTOSCROLL_OFF		82
#define MATRIX_GPIO_ON			86
#define MATRIX_GPIO_OFF			87
#define MATRIX_CLEAR_SCREEN		88

void main( )
{
	xUARTHandle serial1 = uart_init( E_UART_1 );
	lcd_init( 0, 20, 4 );

	// Configure UART
	if( uart_control( serial1, UART_DATABITS_8 | UART_PARITY_NONE | UART_STOPBITS_1, 9600 ) )
		for(;; ); // Error configuring UART, should not get here

	uart_open( serial1 );

	for(;; ) {
		unsigned char rxbyte = uart_read( serial1 ); // Command
		unsigned char temp; // Parameter

		if( rxbyte == 254 ) {
			switch( uart_read( serial1 ) ) {
			case MATRIX_SET_CURSOR:
				lcd_goto( uart_read( serial1 ) - 1, uart_read( serial1 ) - 1 );
				break;
			case MATRIX_CURSOR_HOME:
				lcd_home( );
				break;
			case MATRIX_CURSOR_UNDERLINE_ON:
				lcd_cursor( E_LCD_CURSOR_ON );
				break;
			case MATRIX_CURSOR_UNDERLINE_OFF:
				lcd_cursor( E_LCD_CURSOR_OFF );
				break;
			case MATRIX_CURSOR_BLOCK_ON:
				lcd_cursor( E_LCD_CURSOR_ON_BLINK );
				break;
			case MATRIX_CURSOR_BLOCK_OFF:
				lcd_cursor( E_LCD_CURSOR_OFF );
				break;
			case MATRIX_CURSOR_LEFT:
				lcd_cursor_left( );
				break;
			case MATRIX_CURSOR_RIGHT:
				lcd_cursor_right( );
				break;
			case MATRIX_CUSTOM_CHAR:
				lcd_command( 64 + ( uart_read( serial1 ) * 8 ) );
				for( temp = 7; temp != 0; temp-- ) {
					lcd_write( uart_read( serial1 ) );
				}
				break;
				//case 35: // Read serial number
				//case 36: // Read version number
			case MATRIX_READ_VERSION:
				uart_puts( serial1, "1" );
				break;
			case MATRIX_MODULE_TYPE:
				uart_puts( serial1, "9" );
				break;
			case MATRIX_SET_CONTRAST:
				uart_read( serial1 );
				//analogWrite( BR, 0xFF - serial_getch( ) );
				break;
			case MATRIX_AUTOSCROLL_ON:
				lcd_autoscroll_on( );
				break;
			case MATRIX_AUTOSCROLL_OFF:
				lcd_autoscroll_off( );
				break;
			case MATRIX_GPIO_OFF:
				break;
			case MATRIX_GPIO_ON:
				break;
			case MATRIX_CLEAR_SCREEN:
				lcd_clear( );
				break;
			case 35: // Place large number
			case 38: // Poll key presses
			case 51: // Change I2C slave address (1 parameter, address)
			case 57: // Change baud rate (1 parameter, baud rate)
			case 59: // Exit flow-control mode
			case 61: // Place vertical bar (2 parameters, column, length)
			case 64: // Change the startup screen
			case 65: // Auto transmit keypresses on
			case 67: // Auto line wrap on
			case 68: // Auto line wrap off
			case 66: // Backlight on (1 parameter, minutes)
			case 69: // Clear key buffer
			case 70: // Backlight off
			case 79: // Auto transmit keypress off
			case 85: // Set debounce time (1 paramater, time)
			case 96: // Auto repeat mode off
			case 152: // Set and save brightness (1 parameter, brightness)
			case 153: // Set backlight brightness (1 parameter, brightness)
			case 104: // Initialize horizontal bar
			case 109: // Initialize medium number
			case 110: // Initialize lange numbers
			case 111: // Place medium numbers
			case 115: // Initialize narrow vertical bar
			case 118: // Initialize wide vertical bar
			case 124: // Place horizontal bar graph (4 parameters, column, row, direction, length)
			case 126: // Set auto repeat mode (1 parameter, mode)
			case 145: // Set and save contrast (1 parameter, contrast)
			case 160: // Transmission protocol select (1 parameter, protocol)
			case 192: // Load custom characters (1 parameter, bank)
			case 164: // Setting a non-standart baudrate (1 parameter, speed)
			case 193: // Save custom character (3 parameters, bank, id, data)
			case 194: // Save startup screen custom characters (2 parameters, id, data)
			case 195: // Set startup GPO state (2 parameters, number, state)
			case 200: // Dallas 1-Wire
				switch( uart_read( serial1 ) ) {
				case 1: // Dallas 1-Wire transaction (6 parameters, flags, send, bits, receive, bits, data)
				case 2: // Search for a 1-Wire device
				default:
					break;
				}
				break;
			case 213: // Assign keypad codes
			default:
				/* All other commands are ignored
				 and parameter byte is discarded. */
				temp = uart_read( serial1 );
				break;
			}
			return; // Stop and start again.
		}

		// Otherwise its a plain char so we print it to the LCD.
		lcd_write( rxbyte );
	}
}

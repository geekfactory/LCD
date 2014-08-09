/************************* http://geekfactory.mx *******************************

********************************************************************************/

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

void main()
{
	int i;
	
	// Declare a structure and fill it with pin numbers
	struct lcd_io lcdpins;
	// Pins for control signals
	lcdpins.rs = 10;
	lcdpins.e = 11;
	// Pins for 4 bit data bus
	lcdpins.d4 = 1;
	lcdpins.d5 = 2;
	lcdpins.d6 = 3;
	lcdpins.d7 = 4;

	// Initialize lcd driver, tell the LCD library which pins to use
	lcd_init(&lcdpins, 16, 2);

	// Load characters to CGRAM
	lcd_create_char(0, arrowr);
	lcd_create_char(1, arrowu);
	lcd_create_char(2, arrowl);
	lcd_create_char(3, arrowd);

	// Clear screen to end write to character generator
	lcd_clear();
	// Turn on display
	lcd_on();
	// Display message on the first row
	lcd_puts("LCD Test Program");
	// Move cursor to the fourth column on second line
	lcd_goto(3, 1);
	// Print a message there
	lcd_puts("Hello World");
	// Mover cursor to the sixteenth column on second row
	lcd_goto(15, 1);

	// Main loop
	for (;;) {
		for (i = 0; i < 4; i++) {
			delay_ms(250);
			PORTBbits.RB7 = 0;
			delay_ms(250);
			PORTBbits.RB7 = 1;
			lcd_write(i);
			// Goto the last visible position on the screen
			lcd_goto(50, 50);
		}
	}
}
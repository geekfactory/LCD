#include "LCD.h"
#include "wiringPi.h"
#include "LCD-RBPI.h"

struct lcd_io * io;

BYTE lcd_ioinit( void * iodata )
{
	int i = 0;
	BYTE iomode = 4;
	
	io= (struct lcd_io *)iodata;
	
	// Check if control signals have their pins defined
	if( io->rspin == 0 || io->epin == 0)
		return 0;
	pinMode (io->rspin, OUTPUT);
	pinMode (io->epin, OUTPUT);
	
	if( io->d4pin != 0, io->d5pin != 0, io->d6pin != 0, io->d7pin != 0)
	{
		pinMode (io->d4pin, OUTPUT);
		pinMode (io->d5pin, OUTPUT);
		pinMode (io->d6pin, OUTPUT);
		pinMode (io->d7pin, OUTPUT);
		
		if( io->d0pin != 0, io->d1pin != 0, io->d2pin != 0, io->d3pin != 0)
		{
			pinMode (io->d0pin, OUTPUT);
			pinMode (io->d1pin, OUTPUT);
			pinMode (io->d2pin, OUTPUT);
			pinMode (io->d3pin, OUTPUT);
			iomode = 8;
		}
	}
	else
		// at least the high nibble of the data bus should be defined
		return 0;
	
	// Set all the pins to "low" state
	for( i = 0; i < 11; i++ )
		lcd_ioset( i, FALSE );
		
	return iomode;
}

void lcd_ioset( enum enLCDControlPins pin, BOOL out )
{
	switch( pin ) {
	case E_D0_PIN:
		digitalWrite(io->d0pin,out);
		break;
	case E_D1_PIN:
		digitalWrite(io->d1pin,out);
		break;
	case E_D2_PIN:
		digitalWrite(io->d2pin,out);
		break;
	case E_D3_PIN:
		digitalWrite(io->d3pin,out);
		break;
	case E_D4_PIN:
		digitalWrite(io->d4pin,out);
		break;
	case E_D5_PIN:
		digitalWrite(io->d5pin,out);
		break;
	case E_D6_PIN:
		digitalWrite(io->d6pin,out);
		break;
	case E_D7_PIN:
		digitalWrite(io->d7pin,out);
		break;
	case E_RS_PIN:
		digitalWrite(io->rspin,out);
		break;
	case E_EN_PIN:
		digitalWrite(io->epin,out);
		break;
	case E_RW_PIN:
		digitalWrite(io->wrpin,out);
		break;
	}
}

void lcd_iowrite4( BYTE data )
{
	BYTE i;

	for( i = 4; i < 8; i++ )
		lcd_ioset( i, ( data & ( 1 << i - 4 ) ) ? TRUE : FALSE );

	lcd_iohigh( E_EN_PIN );
	delay_us( 10 );
	lcd_iolow( E_EN_PIN );
}

void lcd_iowrite8( BYTE data )
{
	BYTE i;

	for( i = 0; i < 8; i++ )
		lcd_ioset( i, ( data & ( 1 << i ) ) ? TRUE : FALSE );

	lcd_iohigh( E_EN_PIN );
	delay_us( 10 );
	lcd_iolow( E_EN_PIN );
}
#ifndef LCDIO_H
#define LCDIO_H
/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/
/**
The values on this enumerarion represents the IO pins for the control signals
*/
enum enLCDControlPins
{
	E_EN_PIN,
	E_RS_PIN,
	E_RW_PIN,
};

/*-------------------------------------------------------------*/
/*				Function prototypes								*/
/*-------------------------------------------------------------*/

/**
@brief Prepares the IO pins used for LCD interface
*/
unsigned char xLCDIOInitialize( void * pxLCDIO );

/**
@brief Clears the indicated LCD control line
*/
void vLCDIOClearPin( enum enLCDControlPins eCtrlPin );

/**
@brief Sets the indicated LCD control line
*/
void vLCDIOSetPin( enum enLCDControlPins eCtrlPin );

/**
@brief Writes 4 bits of data to the parallel interface pins
*/
void vLCDIOWrite4( char cData );

/**
@brief Writes 8 bits of data to the parallel interface pins
*/
void vLCDIOWrite8( char cData );

#endif

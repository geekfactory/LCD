#ifndef LCD-RBPI
#define LCD-RBPI

/**
  * Structure used to define IO pin data to be used to interface a display
  * to the raspberry Pi computer.
  */
struct lcd_io
{
	int rs;	//!< Pin number where the RS pin is connected
	int e;	//!< Pin number where the E pin is connected
	int rw;	//!< Pin number where the RW pin is connected (optional)
	
	int d0;	//!< Data bus bit 0 (optional)
	int d1;	//!< Data bus bit 1 (optional)
	int d2;	//!< Data bus bit 2 (optional)
	int d3;	//!< Data bus bit 3 (optional)
	int d4;	//!< Data bus bit 4 (required)
	int d5;	//!< Data bus bit 5 (required)
	int d6;	//!< Data bus bit 6 (required)
	int d7;	//!< Data bus bit 7 (required)
};

#endif

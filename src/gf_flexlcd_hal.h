#ifndef GF_FLEXLCD_HAL_H
#define GF_FLEXLCD_HAL_H

#include <stdint.h>
#include <stdbool.h>

#define GF_FLEXLCD_ARDUINO_INVALID_PIN 255

enum enLCDControlPins
{
	E_EN_PIN,
	E_RS_PIN,
	E_RW_PIN,
};

typedef struct
{
	/**  Function pointer to initialize the IO ports and any other platform specific setup needed to operate the LCD */
	void (*io_init)(void *iodata);

	/** Function pointer to set the state of a control line */
	void (*set_control_line)(void *iodata, enum enLCDControlPins line, bool value);
	
	/** Function pointer to write data to the LCD bus */
	void (*write_bus)(void *iodata, uint8_t data);

	/** Function pointer to delay for a specified number of microseconds */
	void (*delay_us)(uint32_t us);

	/** Used to indicate the bus mode (4 or 8 bits) */
	uint8_t bus_mode;

	/** Context pointer for platform-specific IO control data */
	void * context;
} gf_flexlcd_hal_t;

#endif // GF_FLEXLCD_HAL_H
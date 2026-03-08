#include "pic_hal_mini.h"

inline static void pic_pulse_enable(void *context)
{
	PORTB |= 0x10;
	__delay_us(1);
	PORTB &= ~0x10;
}

static void pic_io_init(void *context)
{
	// Set data pins (RB0-RB3) and control pins (RB4-RB5) as outputs
	TRISB &= ~0x3F;
	// Initialize all control and data lines to low
	PORTB &= ~0x3F;
}

static void pic_set_control_line(void *context, enum enLCDControlPins line, bool value)
{
	switch (line)
	{
	case E_RS_PIN:
		if (value)
			PORTB |= 0x20; // Set RB5
		else
			PORTB &= ~0x20; // Clear RB5
		break;
	case E_EN_PIN:
		if (value)
			PORTB |= 0x10; // Set RB4
		else
			PORTB &= ~0x10; // Clear RB4
		break;
	default:
		break;
	}
}

static void pic_write_bus(void *context, uint8_t data)
{
	// Clear the data bits (RB0-RB3) and set them according to data
	PORTB &= ~0x0F;
	PORTB |= (data & 0x0F);
	// Pulse the enable line to latch the data
	pic_pulse_enable(context);
}

static void pic_delay_us(uint32_t us)
{
	while (us--)
		__delay_us(1);
}

void gf_flexlcd_pic_mini_init(gf_flexlcd_hal_t *hal)
{
	hal->io_init = pic_io_init;
	hal->set_control_line = pic_set_control_line;
	hal->write_bus = pic_write_bus;
	hal->delay_us = pic_delay_us;
	hal->bus_mode = 4;
	hal->context = NULL;
}

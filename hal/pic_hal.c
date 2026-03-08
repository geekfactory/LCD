#include "pic_hal.h"

static void pic_bus_write_4(void *context, uint8_t nibble)
{
	gf_flexlcd_pic_context_t *hal_context = (gf_flexlcd_pic_context_t *)context;
	char temp = *(hal_context->bus_port);
	temp &= ~(hal_context->bus_mask);
	temp |= (nibble & 0x0F) << hal_context->bus_offset;
	*(hal_context->bus_port) = temp;
}

static void pic_pulse_enable(void *context)
{
	gf_flexlcd_pic_context_t *hal_context = (gf_flexlcd_pic_context_t *)context;
	*(hal_context->bus_port) |= hal_context->en;
	__delay_us(10);
	*(hal_context->bus_port) &= ~(hal_context->en);
}

static void pic_set_rs(void *context, uint8_t rs)
{
	gf_flexlcd_pic_context_t *hal_context = (gf_flexlcd_pic_context_t *)context;
	if (rs)
		*(hal_context->bus_port) |= hal_context->rs;
	else
		*(hal_context->bus_port) &= ~(hal_context->rs);
}

static void pic_set_rw(void *context, uint8_t rw)
{
	// Not implemented since RW pin is not used in this configuration
}

static void pic_delay_us(uint32_t us)
{
	while (us--)
		__delay_us(1);
}

static void pic_delay_ms(uint32_t ms)
{
	while (ms--)
		__delay_ms(1);
}

void gf_flexlcd_pic_init(gf_flexlcd_hal_t *hal, gf_flexlcd_pic_context_t *context, volatile unsigned char *bus_port, volatile unsigned char *bus_tris, uint8_t bus_mask, uint8_t bus_offset, uint8_t rs_mask, uint8_t en_mask)
{
	context->bus_port = bus_port;
	context->bus_tris = bus_tris;
	context->bus_mask = bus_mask;
	context->rs = rs_mask;
	context->en = en_mask;

	hal->write_bus_4 = pic_bus_write_4;
	hal->write_bus_8 = NULL;
	hal->delay_ms = pic_delay_ms;
	hal->delay_us = pic_delay_us;
	hal->set_rs = pic_set_rs;
	hal->set_rw = pic_set_rw;
	hal->pulse_enable = pic_pulse_enable;
	hal->iomode = 4;
	hal->context = context;
}

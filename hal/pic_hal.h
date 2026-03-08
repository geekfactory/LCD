#ifndef PIC_HAL_H
#define PIC_HAL_H

#include <XC.h>
#include <stdint.h>
#include <stdbool.h>
#include "gf_flexlcd_hal.h"
#define _XTAL_FREQ 4000000

/**
 * @brief PIC-specific context structure for the LCD HAL
 *
 * This structure holds the port and pin information for the control and data lines of the LCD
 * when using a PIC microcontroller. It is used as the context for the HAL functions
 * to know which ports and pins to manipulate.
 */
typedef struct {
    volatile unsigned char * bus_port;
    volatile unsigned char * bus_tris;
    uint8_t bus_mask;
    uint8_t bus_offset;
    uint8_t rs;
    uint8_t en;
} gf_flexlcd_pic_context_t;

/** 
 */
void gf_flexlcd_pic_init(gf_flexlcd_hal_t *hal, gf_flexlcd_pic_context_t *context, volatile unsigned char * bus_port, volatile unsigned char * bus_tris, uint8_t bus_mask, uint8_t bus_offset, uint8_t rs_mask, uint8_t en_mask);

#endif // PIC_HAL_H
#ifndef PIC_HAL_MINI_H
#define PIC_HAL_MINI_H

#include <XC.h>
#include <stdint.h>
#include <stdbool.h>
#include "gf_flexlcd_hal.h"

#define _XTAL_FREQ 4000000

/**
 * @brief Initializes the HAL for a PIC microcontroller with a minimal pinout.
 * 
 * Minimal implementation for PIC microcontrollers, uses a single port for data and control lines.
 * 
 * Using this HAL doesn't allow multiple LCD instances, as the port and pins are hardcoded.
 * It's intended for simple projects where only one LCD is needed and RAM usage must be minimized.
 * 
 * @param hal Pointer to the HAL structure to initialize.
 */
void gf_flexlcd_pic_mini_init(gf_flexlcd_hal_t *hal);

#endif // PIC_HAL_MINI_H
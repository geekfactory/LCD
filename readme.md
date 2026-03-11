# FlexLCD

**FlexLCD** is a portable **C driver for HD44780-compatible alphanumeric LCD displays** featuring a clean **Hardware Abstraction Layer (HAL)** architecture.

The library is designed to run on a wide range of platforms including **Arduino, Raspberry Pi, Linux SBCs, and bare-metal microcontrollers**.

The driver core is written in **pure C**, allowing it to be reused across embedded and desktop environments while keeping platform-specific code isolated in HAL implementations.

## Features

- HD44780 compatible LCD driver
- 4-bit and 8-bit bus support
- Clean Hardware Abstraction Layer (HAL)
- Platform-agnostic core driver
- Works with microcontrollers and Linux systems
- Small footprint suitable for low-resource MCUs
- No dynamic memory allocation
- Reentrant driver design
- Easily portable to new platforms

## Supported Platforms

FlexLCD is designed to be portable. The core driver does not depend on any specific hardware.

Current or planned HAL implementations include:

| Platform | HAL |
|--------|--------|
| Arduino | `arduino_hal` |
| Raspberry Pi / Linux | `rpi_hal` (libgpiod) |
| AVR | `avr_hal` AVR GCC |
| PIC16 | `pic_hal_mini` `pic_hal` XC8 |
| ESP32 | ESP-IDF / Arduino |
| RP2040 | `pico_hal` |

Additional HAL implementations can easily be created for new platforms.

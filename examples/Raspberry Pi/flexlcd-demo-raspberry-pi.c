#include "gf_flexlcd.h"
#include "rpi_hal.h"
#include <unistd.h>

int main()
{
	gf_flexlcd_t lcd;

	gf_flexlcd_hal_t hal;

	gf_flexlcd_rpi_context_t ctx;

	gf_flexlcd_rpi_init(&hal, &ctx, "gpiochip0",
			    17, // RS
			    27, // EN
			    GF_FLEXLCD_INVALID_PIN,
			    22, // D4
			    23, // D5
			    24, // D6
			    25	// D7
	);
	gf_flexlcd_init(&lcd, &hal, 16, 2);

	gf_flexlcd_on(&lcd);
	// print some text to the display
	gf_flexlcd_puts(&lcd, "FlexLCD Demo");
	gf_flexlcd_goto(&lcd, 0, 1);
	gf_flexlcd_puts(&lcd, "Geek Factory");

	// scroll the display forever
	for (;;)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			gf_flexlcd_scroll_right(&lcd);
			sleep(1);
		}
		for (uint8_t i = 0; i < 4; i++)
		{
			gf_flexlcd_scroll_left(&lcd);
			sleep(1);
		}
	}
}
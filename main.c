

/*
 * main.c
 *
 *  Created on: Jun 6, 2022
 *      Author: jenkins
 */

#include <msp430.h> 
#include "clock.h"
#include "i2c.h"
#include "module.h"

/*
 * The Module List
 */
const MODULE_T MODULES[] =
{
 &run_menu,
 &run_contrast,
 &run_inverse,
 &run_all_on,
 &run_on_off,
 &run_h_scroll,
 &run_v_scroll,
 &run_vh_scroll,
 &run_fade,
 &run_blink,
 &run_zoom,
 &run_com_scan,
 &run_image
};

const uint8_t MODULE_COUNT = sizeof(MODULES) / sizeof(MODULE_T);

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

	clock_init();
    gpio_init();
    i2c_init();
    ssd1315_init();

    uint8_t moduleIndex = 0;
    MODULE_T moduleRun = MODULES[moduleIndex];

    while (1) {
        ModRet nextMod = moduleRun();

        if (nextMod == MOD_PREV) {
            if (moduleIndex > 1)
                --moduleIndex;
            else
                moduleIndex = MODULE_COUNT - 1;
        }
        else if (nextMod == MOD_NEXT) {
            ++moduleIndex;
            if (moduleIndex == MODULE_COUNT)
                moduleIndex = 0;
        }
        moduleRun = MODULES[moduleIndex];
    }

	return 0;
}

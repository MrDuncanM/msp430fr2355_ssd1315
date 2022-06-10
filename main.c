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
 &run_contrast
};

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

        /*switch(__even_in_range(gpio_get_button(), 0x7)) {
        case MOD_PREV:
            if (moduleIndex > 1)
                --moduleIndex;
            else
                moduleIndex = sizeof(MODULES);
            break;
        case MOD_NOP: break;
        case MOD_NEXT:
            ++moduleIndex;
            if (moduleIndex == sizeof(MODULES))
                moduleIndex = 0;
        }*/
    }

	return 0;
}

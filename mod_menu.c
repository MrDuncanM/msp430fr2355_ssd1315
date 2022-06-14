/*
 * mod_menu.c
 *
 *  Created on: Jun 8, 2022
 *      Author: jenkins
 */

#include "module.h"

ModRet run_menu(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(25, 1, "[Toggle LEDs]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(12, 6, "Demo Applications");

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            return MOD_PREV;
        case BTN_RIGHT:
            return MOD_NEXT;
        case BTN_A:
            break;
        default: break;
        }
    }
}

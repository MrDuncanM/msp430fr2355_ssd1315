/*
 * mod_menu.c
 *
 *  Created on: Jun 8, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

ModRet run_menu(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(34, 1, "[Send NOP]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(12, 6, "Demo Applications");

    while (1) {
        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            return MOD_PREV;
        case BTN_RIGHT:
            return MOD_NEXT;
        case BTN_A:
            ssd1315_command(SSD1315_NOP);
            break;
        default: break;
        }
    }
}

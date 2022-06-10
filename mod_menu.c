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
    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(12, 6, "Demo Applications");

    gpio_toggle_led1();

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            gpio_toggle_led1();
            //return MOD_PREV;
            break;
        case BTN_RIGHT:
            gpio_toggle_led2();
            //return MOD_NEXT;
            break;
        case BTN_A:
            gpio_toggle_led1();
            gpio_toggle_led2();
            break;
        default: break;
        }
    }
}

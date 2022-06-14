/*
 * mod_all_on.c
 *
 *  Created on: Jun 10, 2022
 *      Author: jenkins
 */


#include "module.h"

ModRet run_all_on(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(7, 1, "[Toggle All Pixels]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(9, 6, "All Pixels On Demo");

    uint8_t mode = SSD1315_ENTIRE_DISPLAY_NORM;
    ssd1315_command(mode);

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            return MOD_PREV;
        case BTN_RIGHT:
            return MOD_NEXT;
        case BTN_A:
            mode = (mode == SSD1315_ENTIRE_DISPLAY_NORM ? SSD1315_ENTIRE_DISPLAY_ON : SSD1315_ENTIRE_DISPLAY_NORM);
            ssd1315_command(mode);
            break;
        default: break;
        }
    }
}

/*
 * mod_on_off.c
 *
 *  Created on: Jun 10, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

ModRet run_on_off(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(10, 1, "[Turn Display Off]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(6, 6, "Display On/Off Demo");

    uint8_t mode = SSD1315_SET_DISPLAY_ON;
    ssd1315_command(mode);

    while (1) {
        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_SET_DISPLAY_ON);
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_SET_DISPLAY_ON);
            return MOD_NEXT;
        case BTN_A:
            mode = (mode == SSD1315_SET_DISPLAY_ON ? SSD1315_SET_DISPLAY_OFF : SSD1315_SET_DISPLAY_ON);
            ssd1315_command(mode);
            break;
        default: break;
        }
    }
}

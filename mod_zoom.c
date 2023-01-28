/*
 * mod_zoom.c
 *
 *  Created on: Jun 12, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

void zoom_print_menu(uint8_t isZoomed) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(19, 1, "[Zoom Display]");

    if (isZoomed) {
        ssd1315_print(0, 2, "MSP430 - SSD1315 OLED");
        ssd1315_print(34, 3, "Zoom Demo");
    }
    else {
        ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
        ssd1315_print(34, 6, "Zoom Demo");
    }
}

ModRet run_zoom(void) {
    uint8_t mode = SSD1315_ZOOM_DISABLE;

    while (1) {
        zoom_print_menu(mode);

        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_SET_ZOOM);
            ssd1315_command(SSD1315_ZOOM_DISABLE);
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_SET_ZOOM);
            ssd1315_command(SSD1315_ZOOM_DISABLE);
            return MOD_NEXT;
        case BTN_A:
            mode = ~mode;
            ssd1315_command(SSD1315_SET_ZOOM);
            ssd1315_command(mode);
            break;
        default: break;
        }
    }
}

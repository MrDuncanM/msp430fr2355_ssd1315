/*
 * mod_contrast.c
 *
 *  Created on: Jun 10, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

ModRet run_contrast(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(13, 1, "[Adjust Contrast]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(25, 6, "Contrast Demo");

    uint8_t contrast = 0x1;
    ssd1315_command(SSD1315_SET_CONTRAST);
    ssd1315_command(contrast);

    while (1) {
        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            return MOD_PREV;
        case BTN_RIGHT:
            return MOD_NEXT;
        case BTN_A:
            contrast += 0xF;
            if (contrast == 0)
                contrast = 0x1;
            ssd1315_command(SSD1315_SET_CONTRAST);
            ssd1315_command(contrast);
            break;
        default: break;
        }
    }
}

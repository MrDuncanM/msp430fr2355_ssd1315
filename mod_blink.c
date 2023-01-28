/*
 * mod_blink.c
 *
 *  Created on: Jun 12, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

ModRet run_blink(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(19, 1, "[Blink Display]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(34, 6, "Blink Demo");

    uint8_t mode = SSD1315_FB_DISABLE;

    while (1) {
        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_SET_FADE_BLINK);
            ssd1315_command(SSD1315_FB_DISABLE);
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_SET_FADE_BLINK);
            ssd1315_command(SSD1315_FB_DISABLE);
            return MOD_NEXT;
        case BTN_A:
            if (mode == SSD1315_FB_DISABLE) {
                mode = SSD1315_FB_BLINK;

                ssd1315_command(SSD1315_SET_FADE_BLINK);
                ssd1315_command(mode | SSD1315_112_FRAME_FB);
            }
            else {
                mode = SSD1315_FB_DISABLE;
                ssd1315_command(SSD1315_SET_FADE_BLINK);
                ssd1315_command(mode);
            }
            break;
        default: break;
        }
    }
}

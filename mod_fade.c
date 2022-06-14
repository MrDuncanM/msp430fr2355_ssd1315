/*
 * mod_fade.c
 *
 *  Created on: Jun 12, 2022
 *      Author: jenkins
 */

#include "module.h"

ModRet run_fade(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(22, 1, "[Fade Display]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(37, 6, "Fade Demo");

    uint8_t mode = SSD1315_FB_DISABLE;

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
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
                mode = SSD1315_SET_FADE_BLINK;
                ssd1315_command(mode);

                ssd1315_command(SSD1315_FB_FADE | SSD1315_112_FRAME_FB);
            }
            else {
                mode = SSD1315_FB_DISABLE;
                ssd1315_command(SSD1315_SET_FADE_BLINK);
                ssd1315_command(SSD1315_FB_DISABLE);
            }
            break;
        default: break;
        }
    }
}

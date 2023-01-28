/*
 * mod_v_scroll.c
 *
 *  Created on: Jun 12, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

ModRet run_v_scroll(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(25, 1, "[Scroll Text]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(22, 6, "V. Scroll Demo");

    uint8_t mode = SSD1315_STOP_SCROLL;

    while (1) {
        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_STOP_SCROLL);
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_STOP_SCROLL);
            return MOD_NEXT;
        case BTN_A:
            ssd1315_command(SSD1315_STOP_SCROLL);
            if (mode == SSD1315_STOP_SCROLL) {
                // TODO: This scrolls the whole screen? but in the area specified by SET_V_SCROLL
                mode = SSD1315_SET_VH_SCROLL_URIGHT;
                ssd1315_command(mode);
                ssd1315_command(SSD1315_VH_COL_SCR_NONE);
                ssd1315_command(0);                             // Start Page
                ssd1315_command(SSD1315_2_FRAME_SCROLL);
                ssd1315_command(7);                             // End Page
                ssd1315_command(1);                             // Row Offset
                ssd1315_command(0);                             // Start Column
                ssd1315_command(127);                           // End Column

                // What does this do?
                /*ssd1315_command(SSD1315_SET_V_SCROLL);
                ssd1315_command(32);                             // Start Page
                ssd1315_command(48);                             // End Page
                ssd1315_command(SSD1315_START_SCROLL);*/
            }
            else {
                mode = SSD1315_STOP_SCROLL;
            }
            break;
        default: break;
        }
    }
}

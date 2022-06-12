/*
 * mod_inverse.c
 *
 *  Created on: Jun 10, 2022
 *      Author: jenkins
 */

#include "module.h"

ModRet run_inverse(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(19, 1, "[Invert Screen]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(28, 6, "Inverse Demo");

    uint8_t mode = SD1315_SET_NORMAL_DISP;
    ssd1315_command(mode);

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            gpio_toggle_led1();
            return MOD_PREV;
        case BTN_RIGHT:
            gpio_toggle_led2();
            return MOD_NEXT;
        case BTN_A:
            mode = (mode == SD1315_SET_NORMAL_DISP ? SD1315_SET_INVERSE_DISP : SD1315_SET_NORMAL_DISP);
            ssd1315_command(mode);
            break;
        default: break;
        }
    }
}

/*
 * mod_image.c
 *
 *  Created on: Jun 14, 2022
 *      Author: jenkins
 */


#include "module.h"
#include "star.h"
#include "dog.h"

ModRet run_image(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(22, 1, "[Toggle Image]");

    uint8_t showingStar = 1;

    while (1) {
        ssd1315_img_draw(showingStar ? &STAR : &DOG, 0, 2);

        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            return MOD_PREV;
        case BTN_RIGHT:
            return MOD_NEXT;
        case BTN_A:
            showingStar = !showingStar;
            break;
        default: break;
        }
    }
}

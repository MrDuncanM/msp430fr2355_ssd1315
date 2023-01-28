/*
 * mod_com_scan.c
 *
 *  Created on: Jun 13, 2022
 *      Author: Michael Duncan
 */

#include "module.h"

void com_scan_print(uint8_t isNorm) {
    ssd1315_clear();

    if (isNorm) { // Actually reversed in this app
        ssd1315_rprint(0, 7, "> txeN     suoiverP <");
        ssd1315_rprint(13, 6, "]nacS moC elggoT[");

        ssd1315_rprint(0, 4, "DELO 5131DSS - 034PSM");
        ssd1315_rprint(25, 2, "omeD nacS moC");
    }
    else {
        ssd1315_print(0, 0, "< Previous     Next >");
        ssd1315_print(13, 1, "[Toggle Com Scan]");

        ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
        ssd1315_print(25, 6, "Com Scan Demo");
    }
}

// TODO: I would like to support leaving the display in 'normal mode' via print_?
ModRet run_com_scan(void) {
    uint8_t mode = SSD1315_SET_COM_OUTPUT_REV;
    ssd1315_command(mode);

    while (1) {
        com_scan_print(mode == SSD1315_SET_COM_OUTPUT_NORM);

        switch(__even_in_range(gpio_get_button(), BTN_MASK)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_SET_COM_OUTPUT_REV);
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_SET_COM_OUTPUT_REV);
            return MOD_NEXT;
        case BTN_A:
            mode = (mode == SSD1315_SET_COM_OUTPUT_NORM ? SSD1315_SET_COM_OUTPUT_REV : SSD1315_SET_COM_OUTPUT_NORM);
            ssd1315_command(mode);
            break;
        default: break;
        }
    }
}

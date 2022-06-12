/*
 * mod_h_scroll.c
 *
 *  Created on: Jun 10, 2022
 *      Author: jenkins
 */

#include "module.h"


typedef enum {
    HSS_OFF,
    HSS_RIGHT_2_FRAME,
    HSS_RIGHT_3_FRAME,
    HSS_RIGHT_4_FRAME,
    HSS_RIGHT_5_FRAME,
    HSS_RIGHT_6_FRAME,
    HSS_RIGHT_32_FRAME,
    HSS_RIGHT_64_FRAME,
    HSS_RIGHT_128_FRAME,
    HSS_LEFT_2_FRAME,
    HSS_LEFT_3_FRAME,
    HSS_LEFT_4_FRAME,
    HSS_LEFT_5_FRAME,
    HSS_LEFT_6_FRAME,
    HSS_LEFT_32_FRAME,
    HSS_LEFT_64_FRAME,
    HSS_LEFT_128_FRAME,
} HScroll_State;

HScroll_State change_hs_state(HScroll_State curState) {
    // Note: All of these are transitions to a new state. e.g. HSS_OFF -> HSS_RIGHT_2_FRAMES
    HScroll_State retState = HSS_OFF;
    if (curState == HSS_LEFT_128_FRAME) {
        retState = HSS_OFF;
        ssd1315_command(SSD1315_STOP_SCROLL);
    }
    else if (curState < HSS_RIGHT_128_FRAME) {
        ssd1315_command(SSD1315_SET_HORZ_SCROLL_RIGHT);
        ssd1315_command(SSD1315_DUMMY_BYTE_L);
        ssd1315_command(4);
        switch (curState) {
        case HSS_OFF:
            retState = HSS_RIGHT_2_FRAME;
            ssd1315_command(SSD1315_2_FRAME_SCROLL);
            break;
        case HSS_RIGHT_2_FRAME:
            retState = HSS_RIGHT_3_FRAME;
            ssd1315_command(SSD1315_3_FRAME_SCROLL);
            break;
        case HSS_RIGHT_3_FRAME:
            retState = HSS_RIGHT_4_FRAME;
            ssd1315_command(SSD1315_4_FRAME_SCROLL);
            break;
        case HSS_RIGHT_4_FRAME:
            retState = HSS_RIGHT_5_FRAME;
            ssd1315_command(SSD1315_5_FRAME_SCROLL);
            break;
        case HSS_RIGHT_5_FRAME:
            retState = HSS_RIGHT_6_FRAME;
            ssd1315_command(SSD1315_6_FRAME_SCROLL);
            break;
        case HSS_RIGHT_6_FRAME:
            retState = HSS_RIGHT_32_FRAME;
            ssd1315_command(SSD1315_32_FRAME_SCROLL);
            break;
        case HSS_RIGHT_32_FRAME:
            retState = HSS_RIGHT_64_FRAME;
            ssd1315_command(SSD1315_64_FRAME_SCROLL);
            break;
        case HSS_RIGHT_64_FRAME:
            retState = HSS_RIGHT_128_FRAME;
            ssd1315_command(SSD1315_128_FRAME_SCROLL);
            break;
        }
        ssd1315_command(6);
        ssd1315_command(SSD1315_DUMMY_BYTE_L);
        ssd1315_command(SSD1315_DUMMY_BYTE_H);
        ssd1315_command(SSD1315_START_SCROLL);
    }
    else {
        ssd1315_command(SSD1315_SET_HORZ_SCROLL_LEFT);
        ssd1315_command(SSD1315_DUMMY_BYTE_L);
        ssd1315_command(4);
        switch (curState) {
        case HSS_RIGHT_128_FRAME:
            retState = HSS_LEFT_2_FRAME;
            ssd1315_command(SSD1315_2_FRAME_SCROLL);
            break;
        case HSS_LEFT_2_FRAME:
            retState = HSS_LEFT_3_FRAME;
            ssd1315_command(SSD1315_3_FRAME_SCROLL);
            break;
        case HSS_LEFT_3_FRAME:
            retState = HSS_LEFT_4_FRAME;
            ssd1315_command(SSD1315_4_FRAME_SCROLL);
            break;
        case HSS_LEFT_4_FRAME:
            retState = HSS_LEFT_5_FRAME;
            ssd1315_command(SSD1315_5_FRAME_SCROLL);
            break;
        case HSS_LEFT_5_FRAME:
            retState = HSS_LEFT_6_FRAME;
            ssd1315_command(SSD1315_6_FRAME_SCROLL);
            break;
        case HSS_LEFT_6_FRAME:
            retState = HSS_LEFT_32_FRAME;
            ssd1315_command(SSD1315_32_FRAME_SCROLL);
            break;
        case HSS_LEFT_32_FRAME:
            retState = HSS_LEFT_64_FRAME;
            ssd1315_command(SSD1315_64_FRAME_SCROLL);
            break;
        case HSS_LEFT_64_FRAME:
            retState = HSS_LEFT_128_FRAME;
            ssd1315_command(SSD1315_128_FRAME_SCROLL);
            break;
        }
        ssd1315_command(6);
        ssd1315_command(SSD1315_DUMMY_BYTE_L);
        ssd1315_command(SSD1315_DUMMY_BYTE_H);
        ssd1315_command(SSD1315_START_SCROLL);
    }
    return retState;
}

ModRet run_h_scroll(void) {
    ssd1315_clear();

    module_print_menu();
    ssd1315_print(25, 1, "[Scroll Text]");

    ssd1315_print(0, 4, "MSP430 - SSD1315 OLED");
    ssd1315_print(22, 6, "H. Scroll Demo");

    HScroll_State mode = HSS_OFF;
    ssd1315_command(mode);

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_STOP_SCROLL);
            gpio_toggle_led1();
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_STOP_SCROLL);
            gpio_toggle_led2();
            return MOD_NEXT;
        case BTN_A:
            mode = change_hs_state(mode);
            break;
        default: break;
        }
    }
}

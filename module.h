/*
 * module.h
 *
 *  Created on: Jun 8, 2022
 *      Author: jenkins
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <stdint.h>
#include "gpio.h"
#include "ssd1315.h"

typedef enum {
    MOD_PREV = 0x1,
    MOD_NOP = 0x2,
    MOD_NEXT = 0x4
} ModRet;

/*
 * ModuleFunc
 * Modules conform to this entry point and get added to a global list of entry points.
 * Each Module returns -1, 0, or 1 and that will direct the flow to the next module.
 * This could be extended to a Enum definition that would allow modules to return the
 * id of a specific module to transfer to. e.g Menus.
 */
typedef ModRet (*MODULE_T)(void);

/*
 * Module Utilities
 */
void module_print_menu(void);

/*
 * Module Declarations...?
 * This is convenient for now but modules may need their own headers.
 */
ModRet run_menu(void);
ModRet run_contrast(void);
ModRet run_inverse(void);
ModRet run_all_on(void);
ModRet run_on_off(void);
ModRet run_h_scroll(void);
ModRet run_vh_scroll(void);

#endif /* MODULE_H_ */

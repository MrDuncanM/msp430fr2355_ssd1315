/*
 * gpio.c
 *
 *  Created on: Jun 7, 2022
 *      Author: jenkins
 */

#include <msp430.h>
#include "gpio.h"

Button BUTTON_FLAGS = BTN_NONE;

void gpio_init(void) {
    P1DIR = 0xFF;
    P2DIR = 0xFF;
    P3DIR = 0xFF;
    P4DIR = 0xFF ^ BUTTON1;
    P5DIR = 0xFF;
    P6DIR = 0xFF;

    // Configure Pins for I2C
    P1SEL0 |= BIT2 | BIT3;
    P1SEL1 &= ~(BIT2 | BIT3);

    // Turn off LEDs
    P1OUT &= ~LED1;
    P6OUT &= ~LED2;

    // Configure Button Left
    P4DIR &= ~BUTTON1;
    P4REN |= BUTTON1;
    P4OUT |= BUTTON1;
    P4IES |= BUTTON1;

    // Configure Button Right & A
    P2DIR &= ~(BUTTON2 | BUTTON3);
    P2REN |= BUTTON2 | BUTTON3;
    P2OUT |= BUTTON2 | BUTTON3;
    P2IES |= BUTTON2 | BUTTON3;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
}

void gpio_toggle_led1(void) {
    P1OUT ^= LED1;
}

void gpio_toggle_led2(void){
    P6OUT ^= LED2;
}

Button gpio_get_button(void) {
    BUTTON_FLAGS = BTN_NONE;
    P4IE |= BUTTON1;                 // Btn 1 interrupt enable.
    P4IFG = 0;
    P2IE |= BUTTON2 | BUTTON3;
    P2IFG = 0;

    __bis_SR_register(LPM0_bits | GIE);               // Enter LPM0 w/ interrupts

    return BUTTON_FLAGS;
}

/*
 * ISRs
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT4_VECTOR
__interrupt void PORT4_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT4_VECTOR))) PORT4_ISR (void)
#else
#error Compiler not supported!
#endif
{
    BUTTON_FLAGS |= BTN_LEFT;
    P4IFG = 0;
    __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) PORT2_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(P2IFG, BUTTON2 | BUTTON3)) {
    case BUTTON2:
        BUTTON_FLAGS |= BTN_RIGHT;
        P2IFG &= ~BUTTON2;
        break;
    case BUTTON3:
        BUTTON_FLAGS |= BTN_A;
        P2IFG &= ~BUTTON3;
        break;
    default: break;
    }
    __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}

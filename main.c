
#include "xc.h"
#include "configuration.h"

void init_PWM(void) {
    // Set RD0 as output
    TRISDbits.TRISD0 = 0;

    // Initialize Timer2
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR2 = 0x00; // Clear timer register
    PR2 = 2900; // Load the period value for 10.23Khz

    // Initialize Output Compare Module 1
    OC1CONbits.OCM = 0b000; // Disable Output Compare Module
    OC1R = 1600; // Set the initial duty cycle (50%)
    OC1RS = 1600; // Load the Compare Register Value
    OC1CONbits.OCTSEL = 0; // Select Timer2 as the OC time base
    OC1CONbits.OCM = 0b110; // Select the OC mode (PWM mode, no fault protection)

    // Start Timer2
    T2CONbits.TON = 1;
}

void delay_ms(unsigned int milliseconds) {
    while (milliseconds-- > 0) {
        __delay32(16000); // Assuming Fcy = 16 MHz, __delay32(16000) creates a 1 ms delay
    }
}

int main(void) {
    // Initialize the PWM
    init_PWM();

    while (1) {
        // Set the duty cycle to 50%
        OC1RS = 800; // Update duty cycle to 50%

        // Optional: Add a delay to observe the PWM signal
        delay_ms(1000); // Delay for 1 second
    }

    return 0;
}
#ifndef __DELAY_H__
#define __DELAY_H__
#include <LPC21xx.h>
#include <stdint.h>

// Delay for seconds
void delay(uint32_t sec){

    T0PR = 15000000 - 1;   // Prescaler for 1 Hz tick at 60 MHz PCLK

    T0TCR = 0x01;          // Enable Timer0

    while (T0TC < sec);    // Wait for desired seconds

    T0TCR = 0x03;          // Reset Timer Counter

    T0TCR = 0x00;          // Disable Timer0

}
// Delay for milliseconds

void delay_ms(uint32_t ms){

    T0PR = 150000 - 1;      // Prescaler for 1 kHz tick (1 ms) at 60 MHz PCLK

    T0TCR = 0x01;          // Enable Timer0

    while (T0TC < ms);     // Wait for desired milliseconds

    T0TCR = 0x03;          // Reset Timer Counter

    T0TCR = 0x00;          // Disable Timer0

}
// Delay for microseconds

void delay_micro(uint32_t micro){

    T0PR = 15 - 1;         // Prescaler for 1 MHz tick (1 盜) at 60 MHz PCLK

    T0TCR = 0x01;          // Enable Timer0

    while (T0TC < micro);  // Wait for desired microseconds

    T0TCR = 0x03;          // Reset Timer Counter

    T0TCR = 0x00;          // Disable Timer0

}
#endif  // __DELAY_H__


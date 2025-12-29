#include <LPC21xx.h>

#include "timer.h"


void timer0_init(void)

{

	T0TCR = 0x00;          // Disable timer

	T0PR  = 60 - 1;        // 60MHz / 60 = 1MHz ? 1盜 tick

	T0TCR = 0x02;          // Reset timer

}


void timer0_start(void)

{

	T0TCR = 0x02;          // Reset

	T0TCR = 0x01;          // Enable

}


unsigned int timer0_stop(void)

{

	T0TCR = 0x00;          // Stop

	return T0TC;           // Return time in 盜

}



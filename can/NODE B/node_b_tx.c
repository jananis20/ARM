// Node B - Ultrasonic CAN Transmitter

#include <LPC21xx.h>
#include "can2.h"
#include "delay.h"
#include "timer.h"

#define TRIG (1 << 2)
#define ECHO (1 << 3)
#define TANK_HEIGHT 10

int main(void)
{
    CAN2_MSG tx = {1, 0, 1, 0, 0};   // ID = 1 (Ultrasonic)
    unsigned int echoTime;
    float distance;
    int fuel_level;

    can2_init();
    timer0_init();

    IODIR0 |= TRIG;     // TRIG output
    IODIR0 &= ~ECHO;    // ECHO input

    while(1)
    {
        /* Trigger ultrasonic pulse */
        IOSET0 = TRIG;
        delay_us(10);
        IOCLR0 = TRIG;

        /* Wait for echo HIGH */
        while(!(IOPIN0 & ECHO));
        timer0_start();

        /* Wait for echo LOW */
        while(IOPIN0 & ECHO);
        echoTime = timer0_stop();   // microseconds

        /* Distance calculation (cm) */
        distance = (0.0343f * echoTime) / 2.0f;

        /* Fuel level calculation */
        fuel_level = TANK_HEIGHT - (int)distance;
        if(fuel_level < 0) fuel_level = 0;
        if(fuel_level > TANK_HEIGHT) fuel_level = TANK_HEIGHT;

        /* Send CAN data */
        tx.byteA = fuel_level;
        can2_tx(tx);

        delay_ms(1000);
    }
}

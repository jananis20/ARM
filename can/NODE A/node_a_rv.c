// Node A - LCD Dashboard (with L and °C)

#include <LPC21xx.h>
#include "Delay.h"
#include "can2.h"
#include "LCD8BIT.h"

int main(void)
{
    CAN2_MSG rx;

    VPBDIV = 1;

    can2_init();
    LCD_INIT();

    /* -------- STARTUP SCREEN -------- */
    LCD_COMMAND(0x01);
    delay_ms(50);

    LCD_COMMAND(0x80);           // Line 1
    LCDPrintString("   V24ce9j2    ");

    LCD_COMMAND(0xC0);           // Line 2
    LCDPrintString(" CAR DASHBOARD ");

    delay_ms(2000);

    /* -------- DASHBOARD -------- */
    LCD_COMMAND(0x01);
    delay_ms(20);

    LCD_COMMAND(0x80);           // Line 1
    LCDPrintString(" CAR DASHBOARD ");

    LCD_COMMAND(0xC0);           // Line 2
    LCDPrintString("Fuel Level : ");

    LCD_COMMAND(0x94);           // Line 3
    LCDPrintString("Temp       : ");

    LCD_COMMAND(0xD4);           // Line 4
    LCDPrintString("HeadLight  : ");

    /* -------- MAIN LOOP -------- */
    while(1)
    {
        can2_rx(&rx);   // blocking receive

        if(rx.rtr == 0)
        {
            /* Fuel Level */
            if(rx.id == 1)
            {
                LCD_COMMAND(0xC0 + 14);
                LCDPrintString("    ");
                LCD_COMMAND(0xC0 + 14);
                LCDPrintInt(rx.byteA);
                LCDPrintString(" L");   // Litres
				delay(2);
            }

            /* Temperature */
            else if(rx.id == 2)
            {
                LCD_COMMAND(0x94 + 14);
                LCDPrintString("    ");
                LCD_COMMAND(0x94 + 14);
                LCDPrintInt(rx.byteA);
                LCD_DATA(0xDF);           // ° symbol
                LCD_DATA('C');  
				delay(2);          // Celsius
            }

            /* HeadLight */
            else if(rx.id == 3)
            {
                LCD_COMMAND(0xD4 + 14);
                if(rx.byteA){
                    LCDPrintString("ON  ");
					delay(1);
					
				}

               else{
                    LCDPrintString("OFF  ");
					delay(1);
					
               }
			}
        }
    }
}

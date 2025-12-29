/* main_nodeD_TX.c LCD SENOR*/
#include <LPC21xx.H>
#include <stdio.h>
#include "uart.h"
#include "can.h"
#include "Delay.h"

#define LDR 7;

main()
{	
	CAN2_MSG m1;
	VPBDIV = 0x01;
	IODIR0 = LDR;

	uart0_init(115200);
	can2_init();

	uart0_tx_string("LIGHT NODE D\r\n");
	/*sending data frame*/
	m1.id=0x00000003;
	m1.rtr=0;//data frame
	m1.dlc=4;
	m1.byteA=0;
	m1.byteB=0;
	
	while(1)
		{ 	
			if(((IOPIN0>>2)&1)==1)
			{
				uart0_tx_string("HeadLight: ON\r\n");
				m1.byteA=1;
				can2_tx(m1);//data-frame
				IOCLR0 = LDR;
			}
			else
			{
				uart0_tx_string("HeadLight: OFF\r\n");
				m1.byteA=0;
				can2_tx(m1);//data-frame
				IOSET0 = LDR;
			}	
			delay_ms(1010); //wait 1 second for next update	
		}
}



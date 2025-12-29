#include <LPC21xx.h>

#include "can2.h"


void can2_init(void)

{

	PINSEL1 |= 0x00014000;      // P0.23=RD2, P0.24=TD2

	VPBDIV = 1;                // PCLK = 60 MHz


	C2MOD = 0x01;              // Reset mode

	AFMR  = 0x02;              // Accept all frames

	C2BTR = 0x001C001D;        // 125 kbps @ 60 MHz

	C2MOD = 0x00;              // Normal mode

}


void can2_tx(CAN2_MSG m1)

{

	C2TID1 = m1.id;

	C2TFI1 = (m1.dlc << 16);


	if(m1.rtr == 0)

	{

		C2TFI1 &= ~(1<<30);

		C2TDA1 = m1.byteA;

		C2TDB1 = m1.byteB;

	}

	else

		C2TFI1 |= (1<<30);


	C2CMR = (1<<0) | (1<<5);

	while(!(C2GSR & (1<<3)));

}


void can2_rx(CAN2_MSG *m1)

{

	while(!(C2GSR & 0x01));

	m1->id = C2RID;

	m1->dlc = (C2RFS>>16)&0xF;

	m1->rtr = (C2RFS>>30)&1;

	m1->byteA = C2RDA;

	m1->byteB = C2RDB;

	C2CMR = (1<<2);

}


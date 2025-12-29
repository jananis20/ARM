#ifndef __CAN2_H__

#define __CAN2_H__


typedef unsigned int u32;


typedef struct

{

	u32 id;

	u32 rtr;

	u32 dlc;

	u32 byteA;

	u32 byteB;

} CAN2_MSG;


void can2_init(void);

void can2_tx(CAN2_MSG m1);

void can2_rx(CAN2_MSG *m1);


#endif


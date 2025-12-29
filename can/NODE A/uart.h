#ifndef __UART_H__
#define __UART_H__
void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
void uart0_tx_string(char *ptr);
void uart0_tx_integer(int num);
void uart0_tx_hex(int num);
void uart0_tx_float(float num);
#include <LPC21xx.h>
#include <stdio.h>
#include "uart.h"

void uart0_init(unsigned int baud)
{

    PINSEL0 |= 0x5;     // Enable TXD0 & RXD0

    U0LCR = 0x83;       // 8-bit, enable DLAB


    switch(baud)

    {

        case 115200: U0DLL = 32; break; // PCLK = 60MHz

        case 921600: U0DLL = 4;  break;

        default:     U0DLL = 32;

    }


    U0LCR = 0x03;       // Disable DLAB

}

void uart0_tx(unsigned char data)

{

    U0THR = data;

    while((U0LSR & (1<<5)) == 0);

}

unsigned char uart0_rx(void)

{

    while((U0LSR & 0x1) == 0);

    return U0RBR;

}

void uart0_tx_string(char *ptr)
{
     while(*ptr)
       {
          U0THR = *ptr++;
          while((U0LSR & (1<<5)) == 0);
    }
}
void uart0_tx_integer(int num)

{

    char buf[10];

    sprintf(buf, "%d", num);

    uart0_tx_string(buf);

}


void uart0_tx_hex(int num)

{

    char buf[10];

    sprintf(buf, "%X", num);

    uart0_tx_string(buf);

}

void uart0_tx_float(float num)

{

    int i = (int)num;

    uart0_tx_integer(i);

    uart0_tx('.');

    uart0_tx_integer((num - i) * 10);

}






#endif



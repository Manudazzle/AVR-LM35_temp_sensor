/*
 * UART.c
 *
 * Created: 23-05-2026 08:32:54 PM
 *  Author: PC
 */ 

#include "UART.h"

void uart_init()
{
	/*Step 1: Load baud rate : 9600*/
	UBRR0H = 0;
	UBRR0L = 103;
	/*Step 2: Enable transmitter and Receiver*/
	UCSR0B |= ((1 <<TXEN0 ) | (1 << RXEN0));
	/*Step 3: Choosing data frame format*/
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00));
	/*Step 4: Parity select*/
	UCSR0C &= ~((1 << UPM00) | (1 << UPM01));
	/*Step 5: Stop bit select*/
	UCSR0C &= ~(1 << USBS0);
}

/*Function to transmit data*/
void uart_transmit(char data)
{
	/*Checking if buffer is ready to transmit data*/
	while (!(UCSR0A & (1 << UDRE0)));
	
	/*Feed data to the data buffer*/
	UDR0 = data;
}

void uart_TxString(const char *str)
{
	while (*str)
	{
		uart_transmit(*str++);
	}
}
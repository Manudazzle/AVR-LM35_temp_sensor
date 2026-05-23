/*
 * UART.h
 *
 * Created: 23-05-2026 08:33:10 PM
 *  Author: PC
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdlib.h>

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUDRATE)) - 1)

/*Function declarations in UART*/
void uart_init();
void uart_transmit(char data);
void uart_TxString(const char *str);

#endif /* UART_H_ */
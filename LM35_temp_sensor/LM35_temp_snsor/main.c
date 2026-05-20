/*
 * LM35_adc.c
 *
 * Created: 20-05-2026 11:04:59 AM
 * Author : MANU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"

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

int main(void)
{
	uint16_t adc_value;
	float temperature;
	
	//Setup LED on PB0
	DDRB |= (1<<DDB0); 
	
    adc_init();
	lcd_init();
	uart_init();
    while (1) 
    {
		adc_value = read_adc(0);
		temperature = adc_value * 0.488;
		
		//LCD Display
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_print("Temperature: ");
		
		lcd_set_cursor(1,0);
		lcd_print_float(temperature);
		lcd_data(0xDF); //Hex Value for degree Symbol
		lcd_print("C");
		_delay_ms(500);
		
		//UART Transmission
		uart_transmit('\n');
		_delay_ms(500);
		
		//LED Blink
		PORTB ^= (1<<PORTB0);
		_delay_ms(500);
    }
}


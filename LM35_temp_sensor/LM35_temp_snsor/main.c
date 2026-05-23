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
#include "UART.h"

void my_delay_ms(void)
{
	//Step 1 : load 0 to TCNT0
	TCNT0 = 0;
	//Step 2 : choosing Normal mode: Mode0
	TCCR0A &= ~((1<< WGM01) | (1<<WGM00));
	TCCR0B &= ~(1<< WGM02);
	//step 3 : Selecting Prescalar value: No Prescaling
	TCCR0B &= ~((1<< CS02) | (1<< CS01));
	TCCR0B |= (1<< CS00);
	/*  Overflow Calculation
	
		1fclk = 16MHZ = 16,000,000
		1 tick = 1/16,000,000 = 62.5ns (nano seconds)
		For 256 ticks = 256*62.5ns = 16micro seconds(16*10^-6) -> 1 overflow
		0.5s = 0.5/16micro seconds = 31250 = overflow required for 0.5s delay	 
	*/
	for(uint16_t i=0;i<31250;i++)
	{
		// Overflow check command
		while(!(TIFR0 & (1<<TOV0)));
		TIFR0 |= (1<<TOV0); // Clearing the bit by writing to 1
	}
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
	my_delay_ms();
	
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
		my_delay_ms();
		
		//UART Transmission
		char temp_buffer[10];
		dtostrf(temperature,4,1,temp_buffer);   // convert to string 
		uart_TxString(temp_buffer);
		uart_TxString("C\r\n");
		my_delay_ms();
		
		//LED Blink
		PORTB ^= (1<<PORTB0);
		my_delay_ms();
    }
}
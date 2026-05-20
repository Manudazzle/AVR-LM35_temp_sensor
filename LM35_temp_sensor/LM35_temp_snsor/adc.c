/*
 * adc.c
 *
 * Created: 11-05-2026 05:09:41 PM
 *  Author: MANU
 */ 

#include "adc.h"
#include <avr/io.h>

//ADC Initialization
void adc_init()
{
	//Step1: Setting reference voltage VCC
	
	ADMUX &= (1<<REFS1);
	ADMUX |= (1<<REFS0);

	//Step2: Select result adjustment is right adjusted by default

	//Step3: Enable ADC
	ADCSRA |= (1<<ADEN);

	//Step4 : Choosing prescalar value = 128 ~ 125KHZ
	ADCSRA |= ((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));
}

//Step5: To read adc value from the corresponding given channel (0 - 7)
uint16_t read_adc(uint16_t channel)
{
	// Our limit is 0-7 (0000 - 0111). So it is use to limt the choosen channel between 0 to 7
	/*
		Ex : Chosen channel: 8 (1000)
			 channel &= 0000 1000 & 0000 0111 -> 0000 0000
		EX2 : Chosen channel: 12 (1100)
			 channel &= 0000 1100 & 0000 0111 -> 0000 0100 = 4 output(channel)
	 */
	channel &= 0x07;
	
	//Step6: To clear the previous channel and update the register with the new chosen channel
	ADMUX = (ADMUX & 0xF0) | channel;
	
	//Step7: Start adc conversion
	ADCSRA |= (1<<ADSC);
	
	//Step8: Wait until the conversion is done or completed
	while (ADCSRA & (1 << ADSC));
	
	//Step9: Return adc
	return ADC;
}
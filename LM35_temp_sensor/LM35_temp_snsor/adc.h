/*
 * adc.h
 *
 * Created: 11-05-2026 05:09:56 PM
 *  Author: MANU
 */ 


#ifndef ADC_H_
#define ADC_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>

void adc_init();
uint16_t read_adc(uint16_t channel);

#endif /* ADC_H_ */
#include<avr/io.h>
#include<avr/interrupt.h>

#include"adc_lib.h"

#define set_bit(bit,reg) reg |= 1<<bit
#define clear_bit(bit,reg) reg &= ~(1<<bit)

volatile static uint8_t adc_convert_done = 1;

ISR(ADC_vect){
	adc_convert_done = 1;

}

void adc_init(void){
	//setting REFS0 to 1 and leaving REFS1 to 0 to use AVcc as voltage reference
	set_bit(REFS0, ADMUX); 
	
	//enablig ADC
	set_bit(ADEN, ADMUX); 
	
	//enabling interrupts
	set_bit(ADIE, ADMUX); 
	
	//setting prescaler
	set_bit(ADPS0, ADMUX);
	set_bit(ADPS1, ADMUX); 
	set_bit(ADPS2, ADMUX);

}

void adc_pin_select(uint8_t source){
	ADMUX &= 0xF0; 
	set_bit(source, ADMUX);
	
}

void adc_pin_enable(uint8_t pin){
	set_bit(pin, DIDR0);
}

void adc_pin_disable(uint8_t pin){
	clear_bit(pin, DIDR0);
}



uint16_t adc_read(void){
	uint8_t adcl = 0; 
	uint8_t adch = 0;

	adc_convert_done = 0;
	
	set_bit(ADSC, ADCSRA); 
	while(adc_convert_done == 0); 
	
	adcl = ADCL; 
	adch = ADCH; 
	
	return (adch << 8 | adcl);


}


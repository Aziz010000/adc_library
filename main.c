#include<avr/io.h>
#include<avr/interrupt.h>

#include"adc_lib.h"


int main(int arcv, char *argv[])
{
	adc_init();
	adc_pin_enable(ADC0_PIN);
	adc_pin_select(ADC0_PIN);
	
	uint16_t convert = 0;
	
	while(1){
		convert = adc_read();
		float volts = ADC_VOLT(convert);
	}








	return 0;
}

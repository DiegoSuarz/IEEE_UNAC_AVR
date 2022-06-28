/*
 * ADC_AVR.c
 *
 * Created: 6/06/2022 19:04:15
 *  Author: Diego
 */ 
#include "ADC_AVR.h"

void ADC_Init(void){
	ADMUX |= (1<<REFS0);  //seleccionanado el voltaje de referencia Interno 0-5v AVCC
	ADMUX &= ~(1<<REFS1);

	ADMUX &= ~(1<<ADLAR); //justificación a la derecha
   	
	//Seleccionamos el clock del ADC
	//FOSC / PREESC = 16MHz/128 = 125Khz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // preescaler 128
	
	//Desabilitamos los pines analógicos
	//DIDR0 = 0xFF; //deshabilita pines digitales ADC5-0 (todos los canales analogicos)
	
	DIDR0 = 0x00; //temporal
} 


void ADC_Enable(void){
	ADCSRA |= (1<<ADEN); //habilitamos el periferico adc
	
	
}	
void ADC_Disable(void){
	ADCSRA &= ~(1<<ADEN);  //deshabilitamos el periferico adc
	
}

uint16_t ADC_AnalogRead(Channel ANx){
	
	//Seleccionamos el canal del ADC
	ADMUX = ((ADMUX & 0xF0)|(ANx & 0x0F));
	
	//habilitamos el periferico adc
	ADCSRA |= (1<<ADEN); 
	
	//Iniciar Conversion
	ADCSRA |= (1<<ADSC);
	
	//Esperar que la conversion termine
	while(((ADCSRA &(1<<ADSC)))!=0);
	
	//deshabilitamos el ADC
	ADC_Disable();
	
	return (ADC);
}



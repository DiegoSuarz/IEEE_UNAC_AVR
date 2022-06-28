/*
 * Labview.c
 *
 * Created: 24/06/2022 12:16:19
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "USART_AVR.h"
#include "ADC_AVR.h"

float pot0,pot1,pot2,pot3,pot4,pot5;
uint16_t adc_0,adc_1,adc_2,adc_3,adc_4;

char Buffer0[4],Buffer1[4],Buffer2[4],Buffer3[4],Buffer4[4];
char buffer_usart[50]=" ";

void Ejemplo1(void);
void Ejemplo2(void);

int main(void)
{
    ADC_Init();
	USART0_Init(9600);
	sei();
    while (1) 
    {
		Ejemplo1();
		//Ejemplo2();
    }
}

void Ejemplo1(void){
	//inciamos la conversion
	adc_0 = ADC_AnalogRead(AN0);
	adc_1 = ADC_AnalogRead(AN1);
	adc_2 = ADC_AnalogRead(AN2);
	adc_3 = ADC_AnalogRead(AN3);
	adc_4 = ADC_AnalogRead(AN4);
	
	
	//
	//convertimos uint a string (ascii)
	sprintf((char*)Buffer0,"%u;",adc_0);
	sprintf((char*)Buffer1,"%u;",adc_1);
	sprintf((char*)Buffer2,"%u;",adc_2);
	sprintf((char*)Buffer3,"%u;",adc_3);
	sprintf((char*)Buffer4,"%u;",adc_4);
	
	strcat(buffer_usart,Buffer0);
	strcat(buffer_usart,Buffer1);
	strcat(buffer_usart,Buffer2);
	strcat(buffer_usart,Buffer3);
	strcat(buffer_usart,Buffer4);
		
	USART0_PrintString(buffer_usart);
	memset(buffer_usart,'\0',sizeof(buffer_usart));
	
	_delay_ms(500);
	

}

void Ejemplo2(void){
	adc_0 = ADC_AnalogRead(AN0);
	adc_1 = ADC_AnalogRead(AN1);
	adc_2 = ADC_AnalogRead(AN2);
	adc_3 = ADC_AnalogRead(AN3);
	adc_4 = ADC_AnalogRead(AN4);
	sprintf((char*)buffer_usart,"%u;%u;%u;",adc_0,adc_1,adc_2);
	USART0_PrintString(buffer_usart);
}
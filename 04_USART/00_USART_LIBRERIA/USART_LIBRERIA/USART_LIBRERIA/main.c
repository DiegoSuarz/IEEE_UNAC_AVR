/*
 * USART_LIBRERIA.c
 *
 * Created: 7/06/2022 12:45:31
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "USART_AVR.h"

void ejemplo1(void);
void ejemplo2(void);
void ejemplo3(void);

int main(void)
{
	DDRD |= (1<<7)|(1<<6);
	PORTD &= ~(1<<7) & ~(1<<6);
    USART0_Init(9600);
	sei(); //habilitamos la rx
    while (1) 
    {
		
		//ejemplo1();	
		//ejemplo2();
		ejemplo3();	
    }
}

void ejemplo1(void){
	USART0_PrintChar('H');
	_delay_ms(300);
	USART0_PrintChar('o');
	_delay_ms(300);
	USART0_PrintChar('l');
	_delay_ms(300);
	USART0_PrintChar('a');
	_delay_ms(300);
}

void ejemplo2(void){
	USART0_PrintString("Clase 5\n\r");
	_delay_ms(300);
	USART0_PrintString("EMBS UNAC\n\r");
	_delay_ms(300);
	USART0_PrintString("HOLA \n\r");
	_delay_ms(300);
}

void ejemplo3(void){
	USART0_PrintString("50\n\r");
	_delay_ms(5);
}

ISR(USART_RX_vect){  //servicio de rutina de interrupción, se activa cada vez que se recepciona un dato
	char dato = UDR0;		
	switch(dato){
		case 'a':
		PORTD |= (1<<7);
		break;
		
		case 'b':
		PORTD &= ~(1<<7);
		break;
		
		case 'c':
		PORTD |= (1<<6);
		break;
		
		case 'd':
		PORTD &= ~(1<<6);
		break;
		
	}
}


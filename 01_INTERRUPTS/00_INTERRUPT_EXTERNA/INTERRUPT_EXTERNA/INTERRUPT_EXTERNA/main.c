/*
 * INTERRUPT_EXTERNA.c
 *
 * Created: 29/05/2022 20:21:42
 * Author : Diego
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h> //libreria necesaria para trabajar con interrupciones
#include <util/delay.h>
#include "Interrupts.h"


int main(void)
{
	INTx_Init();
	DDRB |= (1<<5) | (1<<0);
	PORTB &= ~(1<<5) & ~(1<<0);
	sei(); //set interrupt, habilita las interrupciones globales
    //cli(); //clear interrupt, deshabilita las interrupciones globales
	while (1) 
    {
		
    }
}


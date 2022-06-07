/*
 * TIMER_TEMPORIZADOR.c
 *
 * Created: 31/05/2022 20:49:06
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Timers_AVR.h"


int main(void)
{
	 cli();
	 Timer1_Init();
	 Timer2_Init();
	 DDRC |= (1<<0)|(1<<1);
	 PORTC &= ~(1<<0) & ~(1<<1);
	 sei();
	while (1) 
    {
		
    }
}

ISR(TIMER1_OVF_vect){ //rutina de servicio de interrupción
	
	PORTC ^= (1<<PINC0);
	TCNT1 = Valor_100ms; //recargar valor del TIMER1
	
	TIFR1 |= (1<<TOV1); //Limpiamos la bandera de interrupción del TIMER1
}

ISR(TIMER2_OVF_vect){ //rutina de servicio de interrupción
	
	PORTC ^= (1<<PINC1);
	TCNT2 = 178; //recargar valor del TIMER1
	
	TIFR2 |= (1<<TOV2); //Limpiamos la bandera de interrupción del TIMER1
}
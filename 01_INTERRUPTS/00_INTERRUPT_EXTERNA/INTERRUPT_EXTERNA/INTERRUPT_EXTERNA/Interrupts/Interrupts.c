/*
 * Interrupts.c
 *
 * Created: 29/05/2022 20:34:17
 *  Author: Diego
 */ 


#include <avr/io.h> //necesario para acceder a los registros
#include <avr/interrupt.h> //libreria necesaria para trabajar con interrupciones
#include "Interrupts.h"

void INTx_Init(void){
	/************************************************************************/
	/* INT0 flanco de subida                                                                */
	/************************************************************************/
	EICRA |= (1<<ISC01)|(1<<ISC00); //INT0 se activa por es flanco de subida
	
	EIMSK |= (1<<INT0); //habilitamos la interrupcion externa 0 (INT0)
	
	
	/************************************************************************/
	/* INT1 flanco de bajada                                                                     */
	/************************************************************************/
	EICRA |= (1<<ISC11); 
	EICRA &= ~(1<<ISC10); //INT1 se activa por flanco de bajada
	
	EIMSK |= (1<<INT1); //habilitamos la interrupcion externa 1 (INT1)
}

ISR(INT0_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT0
	
	PORTB ^= (1<<0);
	EIFR |= (1<<INTF0); //limpiamos la bandera de interrupcion INT0
}

ISR(INT1_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT1
	
	PORTB ^= (1<<5);
	EIFR |= (1<<INTF1); //limpiamos la bandera de interrupcion INT1
}
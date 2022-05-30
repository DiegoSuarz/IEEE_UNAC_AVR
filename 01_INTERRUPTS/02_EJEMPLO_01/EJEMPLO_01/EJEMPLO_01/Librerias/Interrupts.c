/*
 * Interrupts.c
 *
 * Created: 29/05/2022 21:17:47
 *  Author: Diego
 *
*
* Interrupts.c
*
* Created: 29/05/2022 20:34:17
*  Author: Diego
*/


#include <avr/io.h> //necesario para acceder a los registros
#include <avr/interrupt.h> //libreria necesaria para trabajar con interrupciones
#include "Interrupts.h"

/************************************************************************/
/* Interrupcion Externa                                                                     */
/************************************************************************/

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

//ISR(INT0_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT0
//
//
//EIFR |= (1<<INTF0); //limpiamos la bandera de interrupcion INT0
//}
//
//ISR(INT1_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT1
//
//
//EIFR |= (1<<INTF1); //limpiamos la bandera de interrupcion INT1
//}
//

/************************************************************************/
/* Interrupcion por cambio de estado PCINT                                                                     */
/************************************************************************/

void PCINTx_Init(void){
	PCICR |= (1<<PCIE0); //habilitamos interrupcion PCINT0-PCINT7
	
	PCMSK0 |= (1<<PCINT7); //seleccionamos la mascara para PCINT7 (solo se activa esa interrupcion)
}

//ISR(PCINT0_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion PCINT0( pcint0-pcint7)
//
	//
	//PCIFR |= (1<<PCIF0); //limpiamos la bandera de interrupcion INT1
//}
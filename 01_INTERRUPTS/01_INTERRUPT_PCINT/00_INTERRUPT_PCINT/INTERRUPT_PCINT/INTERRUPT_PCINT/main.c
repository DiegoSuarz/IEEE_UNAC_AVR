/*
 * INTERRUPT_PCINT.c
 *
 * Created: 29/05/2022 21:17:17
 * Author : Diego
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Interrupts.h"
#include <stdint.h>
#include <stdbool.h>

volatile bool Flag_PCINT7 = false;

int main(void)
{
	cli(); //deshabilita todas las interrupciones globales
    PCINTx_Init();
	sei(); //habilita todas las interrupciones globales
    while (1) 
    {
		if(Flag_PCINT7){
			for(uint8_t i=0;i<9;i++){
				PORTB ^= (1<<5);
				_delay_ms(300);
			}
			Flag_PCINT7=false;
		}
		
    }
}


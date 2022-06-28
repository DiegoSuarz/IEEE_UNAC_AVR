/*
 * Timers_AVR.c
 *
 * Created: 31/05/2022 20:50:38
 *  Author: Diego
 */ 
#include <avr/io.h>
#include "Timers_AVR.h"

void Timer1_Init(void){
	//TMR1 en modo normal se usa WGM10=0,WGM11=0,WGM12=0,WGM13=0
	TCCR1A &= ~(1<<WGM11) &~(1<<WGM10); 
	TCCR1B &= ~(1<<WGM13) &~(1<<WGM12);
			
	/*
	El timer 1 es de 16bits
	
	t = 500ms
	FOSC = 16Mhz
	Prescaler = 256
	
	
	ValorTimer = 65536 - ((t x FOSC)/(Prescaler) 
	ValorTimer = 65536 - ((500x10^-3 x 16x10^6)/256) 
	ValorTimer = 65536 - 31250
	ValorTimer = 34286
	
	Valor_100ms = 34286
	*/
	//configuracion del preescaler 256: CS10=1, CS11=1 ,CS12=0
	TCCR1B &= ~((1<<CS11)|(1<<CS10));
	TCCR1B |= (1<<CS12);
	
	//cargar el valor al temporizador:
	TCNT1 = Valor_500ms;
	
	//Configurar la interrupción por desbordamiento
	TIMSK1 |= (1<<TOIE1); //habilita interrupción por desobordamiento de TMR1
	
}

void Timer2_Init(void){
	
	//timer2 en modo contador
	TCCR2A &= ~(1<<WGM20) & ~(1<<WGM21); //modo temporizador
	TCCR2B &= ~(1<<WGM22);
	/*
	El timer 2 es de 8bits
	
	t = 5ms
	FOSC = 16Mhz
	Prescaler = 64
	
	
	ValorTimer = 256 - ((t x FOSC)/(Prescaler) 
	ValorTimer = 256 - ((5x10^-3 x 16x10^6)/1024) 
	ValorTimer = 256 - 78
	ValorTimer = 178
	

	*/
	//cargar el prescaler 1024
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
	
	//cargar el valor:
	TCNT2 = 178;
	
	//habilitar la interrupción de desbordamiento tmr2
	TIMSK2 |= (1<< TOV2);
			
}


/*
 * TMR1_CTC.c
 *
 * Created: 3/07/2022 19:02:23
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

void Config_TMR1_CTC(void);

int main(void)
{
    Config_TMR1_CTC();
    while (1) 
    {
		
    }
}

void Config_TMR1_CTC(void){
	//configurar salida digital el pin 
	DDRB |= (1<<PINB1); //OC1A (Timer/Counter1 output compare match A output) 
	
	//configurar TMR1 modo CTC
	/*
	WGM13 WGM12 WGM11 WGM10 = 0100
		*/
	TCCR1A &= ~(1<<WGM11)&~(1<<WGM10);
	
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//fuente de reloj interno y preescaler 256
	//CS12 CS11 CS10 = 100
	TCCR1B &= ~(1<<CS11)& ~(1<<CS10);
	TCCR1B |= (1<<CS12);
	
	//se puede usar de 4 modos el CTC
	/* TCCR1A (COM1A1 COM1A0),(COM1B1 COM1B0) (dos pines vinculados al CTC)
		-normal pin OC1A/OC1B desconectados 00
		-toggle pin OC1A/OC1B				01
		-Clear pin OC1A/OC1B (low level)	10
		-set pin OC1A/OC1B (hihg level)		11
	*/
	//modo toggle en cuando TCNT1 = OCR1A
	TCCR1A |= (1<<COM1A0);
	TCCR1A &= ~(1<<COM1A1);
	
	//formula de frecuencia de oscilacion para el modo CTC
	/*
	OCR1A = ((FOSC)/2*PREESCALER*FREC_D)-1
	FREC_D: FRECUENCIA A LA CUAL QUEREMOS QUE OSCILE EL PIN OC1A EXTERNO
	EJM:
	FOSC=16MHZ, PREE = 256, FREC_D = 3hz  t=1/3 = 333.3 ms
	
	OCR1A = ((16000000)/2*256*3)-1
	OCR1A = 10415.66
	OCR1A = 10416
	*/
	
	OCR1A = 10416;
	return;
}


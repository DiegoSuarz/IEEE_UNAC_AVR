/*
 * TMR1_CTC_PWM.c
 *
 * Created: 3/07/2022 20:30:41
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

void Config_TMR1_CTC_PWM(void);

int main(void)
{
	DDRB |= (1<<PINB5);
    Config_TMR1_CTC_PWM();
	sei();
    while (1) 
    {
		
    }
}

void Config_TMR1_CTC_PWM(void){
	//configurar salida digital el pin 
		
	//configurar TMR1 modo CTC PWM(simulado)
	/*
	Para simular el modo PWM del TMR1 en modo CTC debemos 
	utilizar los 2 registros de comparacion OCR1A y OCR1B
	y cargar los valores a cada registro, al utiliar este
	modo la cpu controla el pwm, asi que no es recomendable
	usarlo si nuestro codigo es muy extenso
	
	
	configurar TMR1 modo CTC
	WGM13 WGM12 WGM11 WGM10 = 0100
		*/
	TCCR1A &= ~(1<<WGM11)&~(1<<WGM10);
	
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//fuente de reloj interno y preescaler 1 (sin preescaler)
	//CS12 CS11 CS10 = 001
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS12)& ~(1<<CS11);
	
	//habilitar las interrupciones por comparacion (los 2 registros OCIE1B,OCIE1A)
	TIMSK1 |= (1<<OCIE1A)|(1<<OCIE1B);
	
	//se puede usar de 4 modos el CTC (para simular el PWM se deja los pines desconectados
	/* TCCR1A (COM1A1 COM1A0),(COM1B1 COM1B0) (dos pines vinculados al CTC)
		-normal pin OC1A/OC1B desconectados 00
		-toggle pin OC1A/OC1B				01
		-Clear pin OC1A/OC1B (low level)	10
		-set pin OC1A/OC1B (hihg level)		11
	*/
	//modo toggle en cuando TCNT1 = OCR1A
	TCCR1A &= ~(1<<COM1A1)&~(1<<COM1A0);
	
	//formula de frecuencia de oscilacion para el modo CTC
	/*
	PARA LA FRECUENCIA PWM:
	OCR1A = ((FOSC)/(2*PREESCALER*FREC_D)/2)-1   //se divide entre 2 el calculo ya que la frecuencia se va a duplicar al usar los 2 comparadores
	FREC_D: FRECUENCIA A LA CUAL QUEREMOS QUE OSCILE EL PIN OC1A EXTERNO
	EJM:
	FOSC=16MHZ, PREE = 1, FREC_D = 5khz  T_PWM =1/5Khz = 200us
	
	OCR1A = ((16000000)/(2*1*5000)/2)-1
	OCR1A = 3199
	
	*/
	
	OCR1A = 3199; //controla el periodo del PWM
	
	//PARA LA FRECUENCIA duty cycle:
	/*
		este valor no debe sobrepasar el valor del regitro OCR1A
		ejm, para un duty cycle del 50% -> OCR1A/2 ->3199/2 = 1599
		10%-> 0.1*3199 = 319.9 = 320
		90%-> 0.9*3199 = 2879.1 = 2879
	*/
	//OCR1B = 1599;  //50% duty cycle
	//OCR1B = 320;  //10% duty cycle
	OCR1B =2879; //90% duty cycle
	return;
}

ISR(TIMER1_COMPA_vect){
	PORTB |= (1<<PORTB5); //al iniciar el T PWM on
}

ISR(TIMER1_COMPB_vect){
	PORTB &= ~(1<<PORTB5); //al terminar el T Duty cycle off
}
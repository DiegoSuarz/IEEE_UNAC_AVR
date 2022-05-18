/*
 * GPIO_HOLA_MUNDO.c
 *
 * Created: 17/05/2022 22:14:53
 * Author : Diego Suárez
 */ 
#define F_CPU	16000000UL

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>



uint8_t Dato1;
uint16_t Dato2;
uint32_t Dato3;

int dato;
float adc;
char texto;
char dato_sms[50];

typedef struct{
	float Conversion;
	uint32_t Alarma_sensor;
	char flag;
}lectura;

typedef enum{
	stop=60,
	Start,
	run
}Estados;


int main(void)
{
    //
	/*
	Registros relacionado DDRx
    AVR tiene 3 registros principales
	DDRX -> definir pines como entrada o salida digital.(1 = salida, 0 = entrada)
	PORTx -> Escribir en el puerto o pines 1 o 0.
	PINx -> Lectura del Puerto o pines
	
	operadores al bit:
	| = or
	& = and
	~ = not
	^ = xor
	<< corrimiento a la derecha
	>> corrimiento a la izquierda
	*/
	
	
	DDRB |= (1<<5); // definiendo como salida el pin PB5
	DDRB &= ~(1<<7); // definiendo como entrada al pin PB7
	
	for(;;)
	{
		PORTB |= (1<<5); //poner el pin PB5 en alto (1 logico)
		_delay_ms(500);
		PORTB &= ~(1<<5);
		_delay_ms(500);
		
		//PORTB ^= (1<<5);
		//_delay_ms(200);
	}
}


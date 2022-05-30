/*
 * EJEMPLO_01.c
 *
 * Created: 29/05/2022 21:53:19
 * Author : Diego
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Interrupts.h"
#include "LCD_Libreria.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint16_t algodon=0,cemento=0;
char strAlgodon[20],strCemento[20];
bool Algodon_F = false, Cemento_F= false;

int main(void)
{
    cli();
	LCD_AVR_Init();
	sprintf(strAlgodon,"%04u",algodon); //convertir de entero a cadena
	sprintf(strCemento,"%04u",cemento); //convertir de entero a cadena
	INTx_Init();
	sei();
	
	LCD_AVR_Set_Cursor(0,Fila1);
	LCD_AVR_Print_String("Algodon: ");
	LCD_AVR_Set_Cursor(0,Fila2);
	LCD_AVR_Print_String("Cemento: ");
    while (1) 
    {
		if(Algodon_F || Cemento_F){
			
			sprintf(strAlgodon,"%04u",algodon); //convertir de entero a cadena
			sprintf(strCemento,"%04u",cemento); //convertir de entero a cadena
			
			LCD_AVR_Set_Cursor(10,Fila1);
			LCD_AVR_Print_String(strAlgodon);
			LCD_AVR_Set_Cursor(10,Fila2);
			LCD_AVR_Print_String(strCemento);
			
			//borramos las banderas
			Algodon_F = false;
			Cemento_F = false;
		}
    }
}

ISR(INT0_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT0
	algodon++;
	Algodon_F = true;
	EIFR |= (1<<INTF0); //limpiamos la bandera de interrupcion INT0
}

ISR(INT1_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT1
	cemento++;
	Cemento_F = true;
	EIFR |= (1<<INTF1); //limpiamos la bandera de interrupcion INT1
}

/*
 * TIMER_CONTADOR.c
 *
 * Created: 4/06/2022 12:36:09
 * Author : Diego
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Timers_AVR.h"
#include "LCD_Libreria.h"
#include <stdio.h>
#include <stdint.h>

uint8_t Productos;
char buffer[20]=" ";
int main(void)
{
	LCD_AVR_Init();
	LCD_AVR_Set_Cursor(0,Fila1);
	LCD_AVR_Print_String("Clase Timers");
   
	Timer1_ModoContador();
	LCD_AVR_Set_Cursor(0,Fila2);
	LCD_AVR_Print_String("Productos: ");
	while (1) 
    {
		Productos = TCNT1;
		sprintf(buffer,"Productos: %04u",Productos);
		LCD_AVR_Set_Cursor(0,Fila2);
		LCD_AVR_Print_String((char*)buffer);
    }
}


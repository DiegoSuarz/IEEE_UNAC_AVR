/*
 * spi_thermocuple.c
 *
 * Created: 1/07/2022 16:49:32
 * Author : Diego
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD_Libreria.h"
#include "spi.h"

#define SS_OFF PORTB|=(1<<PINB2)
#define SS_ON PORTB &= ~(1<<PINB2)

char buffer[20]=" ";
uint8_t dato_high, dato_low;
uint16_t dato;


void read_MAX6675(void);

int main(void)
{
    /* Replace with your application code */
	LCD_AVR_Init();
	spi_init(MASTER);
	LCD_AVR_Set_Cursor(2,Fila1);
	LCD_AVR_Print_String("THERMOCUPLE - SPI");
	_delay_us(20);
    while (1) 
    {
		read_MAX6675();
		
    }
}

void read_MAX6675(void){
	SS_ON;
	_delay_us(20);
	dato_high=spi_read();
	_delay_us(20);
	dato_low=spi_read();
	SS_OFF;
	
	_delay_ms(10);
	dato=(uint16_t)((((dato_high & 0x08)<<8)|dato_low)>>4);
	sprintf(buffer,"%5X",dato);
	
	LCD_AVR_Set_Cursor(4,Fila2);
	LCD_AVR_Print_String("Temp: ");
	LCD_AVR_Print_String(buffer);
	_delay_ms(50);
}

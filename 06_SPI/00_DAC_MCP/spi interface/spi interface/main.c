/*
 * spi interface.c
 *
 * Created: 30/06/2022 20:37:02
 * Author : Diego
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "spi.h"
#include "ADC_AVR.h"
#include "LCD_Libreria.h"


uint8_t data_buffer;
float valor1;
unsigned int valor;
char buffer[20]=" ";

#define SS_OFF PORTB |= (1<<2)
#define SS_ON PORTB &= ~(1<<2)

void MCP_WRITE(unsigned int dato);

int main(void)
{
    /* Replace with your application code */
	ADC_Init();
	spi_init(MASTER);
	LCD_AVR_Init();
	SS_OFF;
    while (1) 
    {
		valor=ADC_AnalogRead(0);
		valor1=(4095.0/1023.0)*valor;
		sprintf(buffer,"%4d",valor);
		LCD_AVR_Set_Cursor(0,0);
		LCD_AVR_Print_String(buffer);
		MCP_WRITE(valor1);
		_delay_ms(300);
    }
}

void MCP_WRITE(unsigned int dato){
	
	_delay_us(15);
	SS_ON;
	_delay_us(15);
	data_buffer=spi_transceive((unsigned char)(((dato&0x0F00)>>8)|0x30));
	_delay_us(15);
	data_buffer=spi_transceive((unsigned char)(dato&0x00FF));
	_delay_us(15);
	SS_OFF;
	_delay_us(15);
}
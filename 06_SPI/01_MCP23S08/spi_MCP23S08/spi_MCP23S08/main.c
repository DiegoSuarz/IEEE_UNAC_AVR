/*
 * spi_MCP23S08.c
 *
 * Created: 1/07/2022 15:47:51
 * Author : Diego
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "spi.h"

#define SS_OFF PORTB|=(1<<PINB2);
#define SS_ON PORTB &= ~(1<<PINB2);

unsigned  char dato;
uint8_t data_dummy;

void Init_MCP(void);
void Read_MCP(void);

int main(void)
{
	DDRD=0xFF;
    spi_init(MASTER);
	SS_OFF;
	Init_MCP();
    while (1) 
    {
		Read_MCP();
    }
}

void Init_MCP(void){
	_delay_us(25);
	SS_ON; //habilitando comunicacion con el esclavo
	data_dummy=spi_transceive(0b01000000); //direccion + bit de escritura
	_delay_us(25);
	data_dummy=spi_transceive(0x00); //accediendo al registro IODIR
	_delay_us(25);
	data_dummy=spi_transceive(0xFF); //todo puerto como entrada digital
	_delay_us(25);
	SS_OFF; //deshabilitando comunicacion con el esclavo
	
	/*****habilitando PULL-UP*****/
	_delay_us(15);
	SS_ON; //habilitando comunicacion con el esclavo
	data_dummy=spi_transceive(0b01000000); //direccion + bit de escritura
	_delay_us(25);
	data_dummy=spi_transceive(0x06); //accediendo al registro GPPU
	_delay_us(25);
	data_dummy=spi_transceive(0xFF); //todos lo pines del puerto con pull-ups habilitadas
	_delay_us(25);
	SS_OFF; //deshabilitando comunicacion con el esclavo
}

void Read_MCP(void){
	_delay_us(15);
	SS_ON; //habilitando comunicacion con el esclavo
	data_dummy=spi_transceive(0b01000001); //direccion + bit de lectura
	_delay_us(25);
	data_dummy=spi_transceive(0x09); //accediendo al registro GPIO para leer el valor del puerto
	_delay_us(25);
	dato=spi_read(); //recepcionar y enviando dato dummy(dato falso) para generar la señal SCK y que el esclavo pueda enviar la informacion
	_delay_us(25);
	SS_OFF; //deshabilitando comunicacion con el esclavo
	PORTD=dato;
	_delay_ms(200);
}

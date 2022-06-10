/*
 * I2C_EEPROM.c
 *
 * Created: 9/06/2022 18:50:28
 * Author : Diego
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_AVR.h"
#include "USART_AVR.h"
#include <string.h>

//direcciones de memoria bus I2C
#define EEPROM1 0b10100110
#define EEPROM2 0b10100010
#define EEPROM3 0b10100000

char Str_1[]= "Hola PROTOLO i2C";
char Str_2[]= "GRABANDO EEPROM";
char Str_3[]= "Hola EEPROM3";

char ReadString[20];
char *ptr_read; //puntero para apuntar a una dirección de memoria 

void Write_EEPROM_I2C(char *ptr_Str, uint16_t ADD_EEPROM);
void Read_EEPROM_I2C(uint8_t address,char *ptr_Str,uint16_t Nbytes, uint16_t ADD_EEPROM);

int main(void)
{
	USART0_Init(9600);
    I2C_Init();
    I2C_Start();
	I2C_Address_Slave(EEPROM1,I2C_WRITE);
	Write_EEPROM_I2C(Str_1,0x0028); //escribir en la posicion de memoria 0x0028 la cadena str_1
	I2C_Stop();
	_delay_ms(5);
	
	
	//Lectura
	I2C_Start();
	I2C_Address_Slave(EEPROM1,I2C_WRITE);
	Read_EEPROM_I2C(EEPROM1,ReadString,strlen(Str_1),0x028); //strlen permite obtener la longitud de la cadena
	I2C_Stop();
	
	_delay_ms(5);
	
	USART0_PrintString(ReadString);
	while (1) 
    {
		
		
    }
}

void Write_EEPROM_I2C(char *ptr_Str, uint16_t ADD_EEPROM)
{
	I2C_Write_Data((uint8_t)(ADD_EEPROM>>8)); //enviar la direccion la parte alta (son 16 bits)
	I2C_Write_Data((uint8_t)(ADD_EEPROM)); //enviar la direecion la parte baja
	while(*ptr_Str)
		I2C_Write_Data(*ptr_Str++); //enviar letra por letra hasta que encuentre el caracter nulo '\0'
}

void Read_EEPROM_I2C(uint8_t address, char *ptr_Str,uint16_t Nbytes, uint16_t ADD_EEPROM)
{
	uint8_t dato_leido;
	I2C_Write_Data((uint8_t)(ADD_EEPROM>>8)); //enviar la direccion la parte alta (son 16 bits)
	I2C_Write_Data((uint8_t)(ADD_EEPROM)); //enviar la direecion la parte baja
	I2C_Start(); //restart, enviamos nuevamente el bit de start para proceder hacer la lectura
	I2C_Address_Slave(address,I2C_READ); //i2c modo lectura
	 while(Nbytes>1){
		 I2C_Read_Data(&dato_leido,I2C_ACK); //los datos enviados por la memoria se almacenan desde el puntero dato leido, enviamos bit ACK
		 *ptr_Str = dato_leido;
		 ptr_Str++; //aumentamos el valor del puntero
		 Nbytes--;
	 }
	 //leemos el ultimo byte
	 I2C_Read_Data(&dato_leido,I2C_NACK); //leemos el ultimo dato, enviamos el bit NACK
	 *ptr_Str = dato_leido;	 
}
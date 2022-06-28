/*
 * USART_AVR.c
 *
 * Created: 7/06/2022 15:16:23
 *  Author: Diego
 */ 
#include "USART_AVR.h"

void USART0_Init(uint32_t BaudRate){
	//Configuramos los baudios
	UBRR0 = (uint16_t)((F_CPU/8UL/BaudRate)-1);
	
	//Configuramos UART0 doble speed mode
	UCSR0A |= (1<<U2X0);
	
	//Configuramos 8 bits de datos para tx y rx:
	UCSR0B &= ~(1<<UCSZ02);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	//Configuramos el modo Asincrono
	UCSR0C &= ~(1<<UMSEL01) & ~(1<<UMSEL00);
	
	//Configuramos el bit de paridad por hardware
	UCSR0C &= ~(1<<UPM01) & ~(1<<UPM00); //desactivamos el bit de paridad
	
	//Configuramos el bit de stop
	UCSR0C &= ~(1<<USBS0); //solo 1 bit de stop

	//habilitar tx UART
	UCSR0B |= (1<<TXEN0);
	
	//habilitar rx UART
	UCSR0B |= (1<<RXEN0);
	
	//habilitar interrupcion por rx
	UCSR0B |= (1<<RXCIE0);
}
void USART0_PrintChar(char C){
	while((UCSR0A & (1<<UDRE0))==0);
	UDR0 = C;
	
}
void USART0_PrintString(char *C){
	char *ptr_c;
	ptr_c = C;
	
	while(*ptr_c){
		USART0_PrintChar(*ptr_c++);
	}
	
}





/*
 * USART_AVR.h
 *
 * Created: 7/06/2022 15:16:45
 *  Author: Diego
 */ 


#ifndef USART_AVR_H_
#define USART_AVR_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>

void USART0_Init(uint32_t BaudRate);
void USART0_PrintChar(char C);
void USART0_PrintString(char *C);




#endif /* USART_AVR_H_ */
/*
 * ADC_AVR.h
 *
 * Created: 6/06/2022 19:04:36
 *  Author: Diego
 */ 


#ifndef ADC_AVR_H_
#define ADC_AVR_H_

#define  F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define  Resolucion_AVR 1023.0
#define  VREF_AVR 5.0

/*para activar la conversion en punto flotante se debe hacer los siguiente:
	1)	ir a propiedades del projecto
	2)  ir a la pestaña toolchain
	3)	ir a la seccion AVR/GNU LINKER
	4)	ir a la opcion GENERAL y marcar la casilla; use vprintf library
	5)	ir a la seccion MISCELLANEUS
	6)	escribir el siguiente comando: -lprintf_flt
*/
typedef enum{
	AN0=0,
	AN1,
	AN2,
	AN3,
	AN4,
	AN5,
	AN6,
	AN7
}Channel;

void ADC_Init(void); //Inicializamos el periferico
void ADC_Enable(void);	//Habilita el ADC
void ADC_Disable(void);	//Desabilita el ADC
uint16_t ADC_AnalogRead(uint8_t channel);	//Seleccionamos el canal
bool ADC_State_Conversion(void);
void ADC_Select_Channel(uint8_t channel);
void ADC_Select_Channel(Channel ANx);
void ADC_Start_Conversion(void);

#endif /* ADC_AVR_H_ */
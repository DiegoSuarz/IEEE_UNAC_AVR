/*
 * ADC_AVR.h
 *
 * Created: 6/06/2022 19:04:36
 *  Author: Diego
 */ 


#ifndef ADC_AVR_H_
#define ADC_AVR_H_

//#include <avr/io.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <stdbool.h>
//
//#define	Resolucion_AVR	1023.0
//#define VREF_AVR 5.0
//
//typedef enum{
	//AN0 = 0x00,
	//AN1,
	//AN2,
	//AN3,
	//AN4,
	//AN5,
	//AN6,
	//AN7
		//
	//}Channel_ADC;
//
//void ADC_Init(void); //Inicializamos el periferico
//void ADC_Enable(void);	//Habilita el ADC
//void ADC_Disable(void);	//Desabilita el ADC
//uint16_t ADC_AnalogRead(uint8_t channel);	//Seleccionamos el canal
//bool ADC_State_Conversion(void);
//void ADC_Select_Channel(uint8_t channel);
//void ADC_Start_Conversion(void);



#define  F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define  Resolucion_AVR 1023.0
#define  VREF_AVR 5.0


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
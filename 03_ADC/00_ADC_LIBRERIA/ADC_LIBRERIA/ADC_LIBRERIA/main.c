/*
 * ADC_LIBRERIA.c
 *
 * Created: 6/06/2022 18:59:53
 * Author : Diego
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC_AVR.h"
#include "LCD_Libreria.h"

float pot0,pot1,pot2,pot3,pot4,pot5,pot6,pot7;
uint16_t adc_0,adc_1,adc_2,adc_3,adc_4,adc_5,adc_6,adc_7;

char Buffer0[20],Buffer1[20],Buffer2[20],Buffer3[20],Buffer4[20],Buffer5[20],Buffer6[20],Buffer7[20];

void Ejemplo1(void);
void Ejemplo2(void);

int main(void)
{
	ADC_Init();
    LCD_AVR_Init();
	LCD_AVR_Set_Cursor(0,Fila1);
	LCD_AVR_Print_String("P0:");
	LCD_AVR_Set_Cursor(12,Fila1);
	LCD_AVR_Print_String("P1:");
	LCD_AVR_Set_Cursor(0,Fila2);
	LCD_AVR_Print_String("P2:");
	LCD_AVR_Set_Cursor(12,Fila2);
	LCD_AVR_Print_String("P3:");
	LCD_AVR_Set_Cursor(0,Fila3);
	LCD_AVR_Print_String("P4:");
	LCD_AVR_Set_Cursor(12,Fila3);
	LCD_AVR_Print_String("P5:");
	LCD_AVR_Set_Cursor(0,Fila4);
	LCD_AVR_Print_String("P6:");
	LCD_AVR_Set_Cursor(12,Fila4);
	LCD_AVR_Print_String("P7:");
	
	
	
    while (1) 
    {
		Ejemplo2();
    }
}

void Ejemplo1(void){
	//inciamos la conversion
	adc_0 = ADC_AnalogRead(AN0);
	adc_1 = ADC_AnalogRead(AN1);
	adc_2 = ADC_AnalogRead(AN2);
	adc_3 = ADC_AnalogRead(AN3);
	adc_4 = ADC_AnalogRead(AN4);
	adc_5 = ADC_AnalogRead(AN5);
	adc_6 = ADC_AnalogRead(AN6);
	adc_7 = ADC_AnalogRead(AN7);
	//
	//convertimos uint a string (ascii)
	sprintf((char*)Buffer0,"%04u",adc_0);
	sprintf((char*)Buffer1,"%04u",adc_1);
	sprintf((char*)Buffer2,"%04u",adc_2);
	sprintf((char*)Buffer3,"%04u",adc_3);
	sprintf((char*)Buffer4,"%04u",adc_4);
	sprintf((char*)Buffer5,"%04u",adc_5);
	sprintf((char*)Buffer6,"%04u",adc_6);
	sprintf((char*)Buffer7,"%04u",adc_7);

	//escribimos en la lcd:
	LCD_AVR_Set_Cursor(4,Fila1);
	LCD_AVR_Print_String(Buffer0);
	LCD_AVR_Set_Cursor(15,Fila1);
	LCD_AVR_Print_String(Buffer1);
	LCD_AVR_Set_Cursor(4,Fila2);
	LCD_AVR_Print_String(Buffer2);
	LCD_AVR_Set_Cursor(15,Fila2);
	LCD_AVR_Print_String(Buffer3);
	LCD_AVR_Set_Cursor(4,Fila3);
	LCD_AVR_Print_String(Buffer4);
	LCD_AVR_Set_Cursor(15,Fila3);
	LCD_AVR_Print_String(Buffer5);
	LCD_AVR_Set_Cursor(4,Fila4);
	LCD_AVR_Print_String(Buffer6);
	LCD_AVR_Set_Cursor(15,Fila4);
	LCD_AVR_Print_String(Buffer7);
}

void Ejemplo2(void){
	//inciamos la conversion
	pot0 = (float)ADC_AnalogRead(AN0)*VREF_AVR/Resolucion_AVR;
	pot1 = (float)ADC_AnalogRead(AN1)*VREF_AVR/Resolucion_AVR;
	pot2 = (float)ADC_AnalogRead(AN2)*VREF_AVR/Resolucion_AVR;
	pot3 = (float)ADC_AnalogRead(AN3)*VREF_AVR/Resolucion_AVR;
	pot4 = (float)ADC_AnalogRead(AN4)*VREF_AVR/Resolucion_AVR;
	pot5 = (float)ADC_AnalogRead(AN5)*VREF_AVR/Resolucion_AVR;
	pot6 = (float)ADC_AnalogRead(AN6)*VREF_AVR/Resolucion_AVR;
	pot7 = (float)ADC_AnalogRead(AN7)*VREF_AVR/Resolucion_AVR;
	//
	//convertimos uint a string (ascii)
	sprintf((char*)Buffer0,"%0.2f",pot0);
	sprintf((char*)Buffer1,"%0.2f",pot1);
	sprintf((char*)Buffer2,"%0.2f",pot2);
	sprintf((char*)Buffer3,"%0.2f",pot3);
	sprintf((char*)Buffer4,"%0.2f",pot4);
	sprintf((char*)Buffer5,"%0.2f",pot5);
	sprintf((char*)Buffer6,"%0.2f",pot6);
	sprintf((char*)Buffer7,"%0.2f",pot7);

	//escribimos en la lcd:
	LCD_AVR_Set_Cursor(4,Fila1);
	LCD_AVR_Print_String(Buffer0);
	LCD_AVR_Set_Cursor(15,Fila1);
	LCD_AVR_Print_String(Buffer1);
	LCD_AVR_Set_Cursor(4,Fila2);
	LCD_AVR_Print_String(Buffer2);
	LCD_AVR_Set_Cursor(15,Fila2);
	LCD_AVR_Print_String(Buffer3);
	LCD_AVR_Set_Cursor(4,Fila3);
	LCD_AVR_Print_String(Buffer4);
	LCD_AVR_Set_Cursor(15,Fila3);
	LCD_AVR_Print_String(Buffer5);
	LCD_AVR_Set_Cursor(4,Fila4);
	LCD_AVR_Print_String(Buffer6);
	LCD_AVR_Set_Cursor(15,Fila4);
	LCD_AVR_Print_String(Buffer7);
}
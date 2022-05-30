/*
 * LCD_LIBRERIA.c
 *
 * Created: 18/05/2022 21:07:17
 * Author : Diego
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_Libreria.h"

int main(void)
{
	LCD_AVR_Init();
	LCD_AVR_New_Char(4,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x00,0x00);
	//LCD_AVR_New_Char(2,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x01,0x00);
	//LCD_AVR_New_Char(3,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x02,0x00);
	//LCD_AVR_New_Char(4,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x03,0x00);
	//LCD_AVR_New_Char(2,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x04,0x00);
	//LCD_AVR_New_Char(2,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x05,0x00);
	//LCD_AVR_New_Char(2,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x06,0x00);
	//LCD_AVR_New_Char(2,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x07,0x00);
	//LCD_AVR_New_Char(2,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x08,0x00);
	
	//LCD_AVR_Set_Cursor(0,Fila1);
	//LCD_AVR_Print_Char('H');
	//LCD_AVR_Set_Cursor(0,Fila2);
	//LCD_AVR_Print_Char('O');
	//LCD_AVR_Set_Cursor(0,Fila3);
	//LCD_AVR_Print_Char('L');
	//LCD_AVR_Set_Cursor(0,Fila4);
	//LCD_AVR_Print_Char('A');
	
	
	
	LCD_AVR_Print_New_Char(1);
	LCD_AVR_Print_New_Char(2);
	LCD_AVR_Print_New_Char(3);
	LCD_AVR_Print_New_Char(4);
	LCD_AVR_Print_New_Char(5);
	LCD_AVR_Print_New_Char(6);
	LCD_AVR_Print_New_Char(7);
	//LCD_AVR_Set_Cursor(0,Fila2);
	//LCD_AVR_Print_New_Char(2);
	//LCD_AVR_Set_Cursor(0,Fila3);
	//LCD_AVR_Print_New_Char(3);
	//LCD_AVR_Set_Cursor(0,Fila4);
	//LCD_AVR_Print_New_Char(4);
	
	for (;;)
	{
		
		
	}
}


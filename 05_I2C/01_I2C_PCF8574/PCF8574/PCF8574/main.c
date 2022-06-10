/*
 * PCF8574.c
 *
 * Created: 8/06/2022 21:57:53
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_AVR.h"

#define  ADDS_PCF1 0b01000000
#define  ADDS_PCF2 0b01001100
#define  ADDS_PCF3 0b01000110

uint8_t unidades,decenas,centenas;

uint8_t Display_7Seg_A[10] = {0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
	
int main(void)
{
	I2C_Init();
	while (1)
	{
		for(centenas=0;centenas<10;centenas++)
		{
			I2C_Start();
			I2C_Address_Slave(ADDS_PCF3,I2C_WRITE);
			I2C_Write_Data(Display_7Seg_A[centenas]);
			for(decenas=0;decenas<10;decenas++)
			{
				I2C_Start();
				I2C_Address_Slave(ADDS_PCF2,I2C_WRITE);
				I2C_Write_Data(Display_7Seg_A[decenas]);
				for(unidades=0;unidades<10;unidades++)
				{
					I2C_Start();
					I2C_Address_Slave(ADDS_PCF1,I2C_WRITE);
					I2C_Write_Data(Display_7Seg_A[unidades]);
					_delay_ms(50);
				}
			}
			I2C_Stop();
		}
	}
}

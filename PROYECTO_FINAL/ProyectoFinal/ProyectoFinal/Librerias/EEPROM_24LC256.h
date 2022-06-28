/*
 * EEPROM_24LC256.h
 *
 * Created: 25/06/2022 19:38:33
 *  Author: Diego
 */ 


#ifndef EEPROM_24LC256_H_
#define EEPROM_24LC256_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_AVR.h"

#define DIR_EEPROM 0b10100110

void WriteEEPROM(uint16_t dir_mem,uint8_t dato1,uint8_t dato2,uint8_t dato3,uint8_t dato4);
void ReadEEPROM(uint16_t dir_mem, uint8_t *data1, uint8_t *data2, uint8_t *data3, uint8_t *data4);


#endif /* EEPROM_24LC256_H_ */
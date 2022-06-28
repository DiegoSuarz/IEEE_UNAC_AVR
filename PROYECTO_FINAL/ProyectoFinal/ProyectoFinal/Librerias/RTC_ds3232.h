/*
 * RTC_ds3232.h
 *
 * Created: 25/06/2022 19:11:07
 *  Author: Diego
 */ 


#ifndef RTC_DS3232_H_
#define RTC_DS3232_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_AVR.h"

#define DIR_RTC 0xD0

extern uint8_t data_aux,data_seg,data_min,data_hor;
extern uint8_t data_diaS, data_dia, data_mes, data_year;
extern uint8_t a_min,a_hor;

void ConfiRegRTC_Hora(uint8_t dir, uint8_t data_seg, uint8_t data_min, uint8_t data_hor);
void ConfiRegRTC_Fecha(uint8_t dir, uint8_t diaS, uint8_t dia, uint8_t mes, uint8_t year);
void getDataDs3232(void);


#endif /* RTC_DS3232_H_ */
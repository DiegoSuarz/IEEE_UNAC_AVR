/*
 * I2C_AVR.h
 *
 * Created: 8/06/2022 19:01:54
 *  Author: Diego
 */ 


#ifndef I2C_AVR_H_
#define I2C_AVR_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

#define I2C_WRITE	0x00
#define I2C_READ	0x01

#define I2C_ACK		0x00
#define I2C_NACK	0x01

#define F_SCL 100000UL
#define Preescaler 1UL
#define Bit_Rate()	((((F_CPU/F_SCL)/Preescaler)-16UL)/2UL)

#define MASCARA_STATUS 0xF8
#define Condition_start_ok 0x08
#define Condition_restart_ok 0x10

#define MASTER_TX_SLAVE_ACK 0x18
#define MASTER_RX_SLAVE_ACK 0x40 
#define MASTER_TX_DATA_ACK 0x28
#define MASTER_RX_DATA_ACK 0x50
#define MASTER_RX_DATA_NACK 0x58

void I2C_Init(void); //Inicializar el periferico
uint8_t I2C_Start(void); //Vamos a iniciar la comunicación
uint8_t I2C_Address_Slave(uint8_t address,uint8_t modo); //direccionamiento al esclavo rx,tx
uint8_t I2C_Write_Data(uint8_t data);
uint8_t I2C_Read_Data(uint8_t *ptr_dato, uint8_t ack_nack);
void I2C_Stop(void); //Finalizamos al comunicación


#endif /* I2C_AVR_H_ */
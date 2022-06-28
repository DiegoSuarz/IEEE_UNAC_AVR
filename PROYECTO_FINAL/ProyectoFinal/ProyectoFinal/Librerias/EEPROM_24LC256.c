/*
 * EEPROM_24LC256.c
 *
 * Created: 25/06/2022 19:38:49
 *  Author: Diego
 */ 
#include "EEPROM_24LC256.h"

void ReadEEPROM(uint16_t dir_mem, uint8_t *data1, uint8_t *data2, uint8_t *data3, uint8_t *data4){
	uint8_t dato_leido;
	I2C_Start();
	I2C_Address_Slave(DIR_EEPROM,I2C_WRITE);
	I2C_Write_Data((uint8_t)(dir_mem>>8));
	I2C_Write_Data((uint8_t)(dir_mem));
	I2C_Start();
	I2C_Address_Slave(DIR_EEPROM,I2C_READ);
	I2C_Read_Data(&dato_leido,I2C_ACK);
	*data1=dato_leido;
	I2C_Read_Data(&dato_leido,I2C_ACK);
	*data2=dato_leido;
	I2C_Read_Data(&dato_leido,I2C_ACK);
	*data3=dato_leido;
	I2C_Read_Data(&dato_leido,I2C_NACK);
	*data4=dato_leido;
	I2C_Stop();
}

void WriteEEPROM(uint16_t dir_mem,uint8_t dato1,uint8_t dato2,uint8_t dato3,uint8_t dato4){
	I2C_Start();
	I2C_Address_Slave(DIR_EEPROM,I2C_WRITE);
	I2C_Write_Data((uint8_t)(dir_mem>>8));
	I2C_Write_Data((uint8_t)(dir_mem));
	I2C_Write_Data(dato1);
	I2C_Write_Data(dato2);
	I2C_Write_Data(dato3);
	I2C_Write_Data(dato4);
	I2C_Stop();
}
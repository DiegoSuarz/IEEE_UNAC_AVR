/*
 * RTC_ds3232.c
 *
 * Created: 25/06/2022 19:10:51
 *  Author: Diego
 */ 
#include "RTC_ds3232.h"

void ConfiRegRTC_Hora(uint8_t dir, uint8_t data_seg, uint8_t data_min, uint8_t data_hor){
	
	data_seg=(uint8_t)((data_seg/10)<<4)|(data_seg%10);
	data_min=(uint8_t)((data_min/10)<<4)|(data_min%10);
	data_hor=(uint8_t)((data_hor/10)<<4)|(data_hor%10);
	
	I2C_Start();
	I2C_Address_Slave(DIR_RTC,I2C_WRITE);
	I2C_Write_Data(0x00);
	I2C_Write_Data(data_seg);
	I2C_Write_Data(data_min);
	I2C_Write_Data(data_hor);
	I2C_Stop();
}

void ConfiRegRTC_Fecha(uint8_t dir, uint8_t diaS, uint8_t dia, uint8_t mes, uint8_t year){
	
	diaS=(uint8_t)((diaS%10)&0x07);
	dia=(uint8_t)(((dia/10)&0x03)<<4)|(dia%10);
	mes=(uint8_t)(((mes/10)&0x01)<<4)|(mes%10);
	year=(uint8_t)((year/10)<<4)|(year%10);
	
	I2C_Start();
	I2C_Address_Slave(DIR_RTC,I2C_WRITE);
	I2C_Write_Data(0x03);
	I2C_Write_Data(diaS);
	I2C_Write_Data(dia);
	I2C_Write_Data(mes);
	I2C_Write_Data(year);
	I2C_Stop();
}

void getDataDs3232(void){
	uint8_t data;
	I2C_Start();
	I2C_Address_Slave(DIR_RTC,I2C_WRITE);
	I2C_Write_Data(0x00);
	I2C_Start(); //restart
	I2C_Address_Slave(DIR_RTC,I2C_READ);
	I2C_Read_Data(&data,I2C_ACK);
	data_seg=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Read_Data(&data,I2C_ACK);
	data_min=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Read_Data(&data,I2C_ACK); //I2C_Read_Data(&data,I2C_NACK)
	data_hor=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Read_Data(&data,I2C_ACK);
	data_diaS=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Read_Data(&data,I2C_ACK);
	data_dia=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Read_Data(&data,I2C_ACK);
	data_mes=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Read_Data(&data,I2C_NACK);
	data_year=((data & 0xF0)>>4)*10 + (data&0x0F);
	I2C_Stop();
}

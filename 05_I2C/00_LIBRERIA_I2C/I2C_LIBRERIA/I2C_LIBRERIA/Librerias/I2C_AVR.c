/*
 * I2C_AVR.c
 *
 * Created: 8/06/2022 19:01:38
 *  Author: Diego
 */ 
#include "I2C_AVR.h"

void I2C_Init(void)
{
	//Preescalador
	TWSR &= ~(1<<TWPS0) & ~(1<<TWPS1);
	//Bit Rate
	TWBR = (uint8_t)Bit_Rate(); //velocidad de tx 100Khz
		
}
uint8_t I2C_Start(void)
{
	
	uint8_t status;
	TWCR |= (1<<TWEN) |(1<<TWSTA) |(1<<TWINT);//habilitar i2c, bit de start, habilitar bandera de interrupcion
	while((TWCR & (1<<TWINT))==0); //esperar hasta que se envie el bit de start
	status = (TWSR & MASCARA_STATUS);
	if((status == Condition_start_ok)||(status == Condition_restart_ok)){ //revisar Status Codes for Master Receiver Mode pag 189
		
		return 1; //operacion exitosa
	}
	return status;//hubo un problema
	
}
uint8_t I2C_Address_Slave(uint8_t address,uint8_t modo)
{
	uint8_t status = 0;
	TWDR = ((address & 0xFE)|(modo & 0x01)); //enviar direccion de esclavo, mas bit de lectura o escritura
	TWCR = (1<<TWEN)|(1<<TWINT); //habilitar i2c, habilitar bandera de interrupcion (inicia la transmiscion)
	
	while((TWCR & (1<<TWINT))==0); //esperar a que se envien los datos a tx
	
	status = (TWSR & MASCARA_STATUS);
	if((status == MASTER_TX_SLAVE_ACK)||(status == MASTER_RX_SLAVE_ACK)){ //revisar Status Codes for Master Receiver Mode pag 189
		
		return 1; //transmision exitosa
	}
	return status;//hubo un problema
	
	
}
uint8_t I2C_Write_Data(uint8_t data)
{
	uint8_t status =0;
	TWDR = data;  //escribimos el dato a transmitir
	TWCR = (1<<TWEN)|(1<<TWINT); //habilitar i2c, habilitar bandera de interrupcion (inicia la transmiscion)
	
	while((TWCR & (1<<TWINT))==0); //esperar a que se envien los datos a tx
	
	//evalua el estado del bus
	status = (TWSR & MASCARA_STATUS);
	if(status == MASTER_TX_DATA_ACK){ //revisar Status Codes for Master Receiver Mode pag 189
		
		return 1; //transmision exitosa
	}
	return status;//hubo un problema	
	
}

uint8_t I2C_Read_Data(uint8_t *ptr_dato, uint8_t ack_nack);

void I2C_Stop(void)
{
	TWCR |= (1<<TWEN) |(1<<TWSTO) |(1<<TWINT);//habilitar i2c, bit de stop, habilitar bandera de interrupcion
	while((TWCR & (1<<TWSTO))==1); //esperar hasta que se complete el bit de stop

}
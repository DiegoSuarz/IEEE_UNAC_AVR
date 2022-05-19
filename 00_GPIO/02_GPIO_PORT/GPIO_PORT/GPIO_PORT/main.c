/*
 * GPIO_PORT.c
 *
 * Created: 18/05/2022 19:28:34
 * Author : Diego
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void Ejemplo1(void);
void Ejemplo2(void);
void Ejemplo3(void);
void Ejemplo4(void);
void Ejemplo5(void);
void Ejemplo6(void);
void Ejemplo_pulsadores(void);

int main(void)
{
	Ejemplo_pulsadores();
	
}

void Ejemplo1(void){

	DDRB |= (1<<7)|(1<<0); //definir como salida pinb 7 y 0

	while (1)
	{
		PORTB |= (1<<7);
		PORTB &= ~(1<<0);
		_delay_ms(300);
		
		PORTB |= (1<<0);
		PORTB &= ~(1<<7);
		_delay_ms(300);
	}
	
}

void Ejemplo2(void){
	
	DDRB = 0xFF;
	
	while(1){
		PORTB = 0x0F;
		_delay_ms(200);
		PORTB = 0xF0;
		_delay_ms(200);
	}
	
}

void Ejemplo3(void){
	DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7); //todo el puerto B como salida
	int8_t i;
	
	while(1){
		for(i = 0;i<=8;i++){
			PORTB = pow(2,i)-1;
			_delay_ms(300);
		}
		for(i = 7;i>0;i--){
			PORTB = pow(2,i)-1;
			_delay_ms(300);
		}
	}

}

void Ejemplo4(void){
	DDRB = 0xFF;
	int8_t j=0;
	
	while(1){
		while(j<8){
			PORTB |= (1<<j);
			_delay_ms(300);
			j++;
		}
		j--;
		while(j>=0){
			PORTB &= ~(1<<j);
			_delay_ms(300);
			j--;
		}
		j=0;
	}
}

void Ejemplo5(void){
	DDRB = 0xFF;
	int8_t k=0;
	
	while(1){
		while(k<8){
			PORTB |= (1<<k);
			_delay_ms(300);
			k++;
		}
		k--;
		while(k>=0){
			PORTB = (PORTB>>1);
			_delay_ms(300);
			k--;
		}
		k=0;
	}
	
}

void Ejemplo6(void){
	DDRB = 0xFF;
	int8_t k=0;
	
	while(1){
		PORTB = 0x01;
		while(k<8){
			PORTB = (PORTB<<1);
			_delay_ms(300);
			k++;
		}
		PORTB = 0x80;
		k=7;
		while(k>0){
			PORTB = (PORTB>>1);
			_delay_ms(300);
			k--;
		}
		k=1;
	}
	
}

void Ejemplo_pulsadores(void){
	
	//BT1	PD0
	//BT2	PD5
	//BT3	PC0
	
	DDRB |= (1<<0)|(1<<1)|(1<<2); //pb0, pb1, pb2 salidas
	DDRD &= ~(1<<0) & ~(1<<5); //pd0 y pd5 entradas
	DDRC &= ~(1<<0); //pc0 entrada
	
	
	for(;;){
		
		if((PINC & (1<<0))==0){  //if((PINC & (1<<0))!=1)
			
			PORTB |= (1<<0);
			
			}else{
			PORTB &= ~(1<<0);
		}
		
		if(!(PIND & (1<<0))){ //if((PIND & (1<<0))==0)
			
			PORTB |= (1<<1);
			
			}else{
			PORTB &= ~(1<<1);
		}
		
		if((PIND & (1<<5))){  //if((PIND & (1<<5))!=0)
			
			PORTB |= (1<<2);
			
			}else{
			
			PORTB &= ~(1<<2);
		}
	}
	
}
/*
 * ProyectoFinal.c
 *
 * Created: 18/06/2022 18:57:35
 * Author : Diego
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "Interrupts.h"
#include "I2C_AVR.h"
#include "LCD_Libreria.h"
#include "Timers_AVR.h"
#include "ADC_AVR.h"
#include "USART_AVR.h"
#include "RTC_ds3232.h"
#include "EEPROM_24LC256.h"

char aux[20];
char buffer_usart[50]=" ";

int16_t lectura_adc;
float LM35,temp,sensor;

uint8_t data_aux,data_seg=45,data_min=33,data_hor=7;
uint8_t data_diaS=0, data_dia=1, data_mes=1, data_year=20;
uint8_t a_min=0,a_hor=0;

uint8_t menu=0;
uint8_t config=0;
uint8_t flag,flag_a,flag_f;
uint8_t alarmaOn;

float Read_LM35(uint8_t Channel);
void visualizar_Parametros(void);
void DataSerial(void); 
  
void menu0(void);
void menu1(void);
void menu2(void);
void menu3(void);
void menu4(void);


int main(void)
{
	DDRD |= (1<<5);
	DDRD &= ~(1<<7); 
	DDRD &= ~(1<<6); 
	cli();
	LCD_AVR_Init();
	LCD_AVR_New_Char(1,0b00010000,0b00011000,0b00011100,0b00011110,0b00011100,0b00011000,0b00010000,0b00000000);
	LCD_AVR_New_Char(2,0b00000100,0b00001110,0b00001110,0b00011111,0b00000000,0b00000100,0b00000000,0b00000000);
	USART0_Init(9600);
	I2C_Init();
	Timer1_Init();
	ADC_Init();
	INTx_Init();
	ReadEEPROM(0x0000,&a_hor,&a_min,&alarmaOn,&data_aux);
	ReadEEPROM(0x0004,&data_diaS,&data_dia,&data_mes,&data_year);
	
	ConfiRegRTC_Hora(DIR_RTC,data_seg,data_min,data_hor);
	ConfiRegRTC_Fecha(DIR_RTC,data_diaS,data_dia,data_mes,data_year);
	sei();
	
	LCD_AVR_Set_Cursor(4,0);
	LCD_AVR_Print_String("Proyecto Final");
	LCD_AVR_Set_Cursor(4,1);
	LCD_AVR_Print_String("del curso AVR");
	LCD_AVR_Set_Cursor(6,2);
	LCD_AVR_Print_String("IEEE UNAC");
	_delay_ms(2000);	
	while (1)
	{
		switch(menu){
			case 0: menu0(); break;
			case 1: menu1(); break;
			case 2: menu2(); break;
			case 3: menu3(); break;
			case 4: menu4(); break;
		}
	}
}

ISR(TIMER1_OVF_vect){ //rutina de servicio de interrupción
	if(menu!=2 && menu!=3){
		getDataDs3232(); 
		temp=Read_LM35(AN6);
	}
	DataSerial();
	TCNT1 = Valor_500ms; 
	TIFR1 |= (1<<TOV1); //Limpiamos la bandera de interrupción del TIMER1
	
}

ISR(INT0_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT0
	if(config==0){
		menu=1;
	}
	if(config==1){
		menu=2;
	}
	if(config==2){
		menu=3;
	}
	if(config==3){
		menu=4;
	}
	EIFR |= (1<<INTF0); //limpiamos la bandera de interrupcion INT0
}

ISR(INT1_vect){  //servicio de rutina de interrupcion, apuntar al vector de interrupcion INT0
	if(menu==0){
		config++;
		if(config==4)config=0;
	}
	if(menu==1){menu=0;}
	if(menu==2){menu=0;}
	if(menu==3){menu=0;}	
	if(menu==4){menu=0;}		
	EIFR |= (1<<INTF0); //limpiamos la bandera de interrupcion INT0
}

ISR(USART_RX_vect){  //servicio de rutina de interrupción, se activa cada vez que se recepciona un dato
	char dato = UDR0;
	switch(dato){
		case 'a':
		alarmaOn=1;
		break;
		
		case 'b':
		alarmaOn=1;
		break;
		
		case 'c':
		alarmaOn=0;
		break;
			
		case 'd':
		alarmaOn=0;
		break;
				
	}
}

float Read_LM35(uint8_t Channel){
	lectura_adc = ADC_AnalogRead(Channel);
	LM35 =	(lectura_adc*4.88)/10;
	return LM35;
}

void visualizar_Parametros(void){
	
	if(menu==1){
		
		LCD_AVR_Set_Cursor(0,1);
		LCD_AVR_Print_String("Hora:  ");
		LCD_AVR_Print_Char((data_hor/10)+48);
		LCD_AVR_Print_Char((data_hor%10)+48);
		LCD_AVR_Print_Char(':');
		LCD_AVR_Print_Char((data_min/10)+48);
		LCD_AVR_Print_Char((data_min%10)+48);
		LCD_AVR_Print_Char(':');
		LCD_AVR_Print_Char((data_seg/10)+48);
		LCD_AVR_Print_Char((data_seg%10)+48);
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		if(alarmaOn==1){LCD_AVR_Print_New_Char(2);}
		LCD_AVR_Print_Char(' ');
				
		LCD_AVR_Set_Cursor(0,2);
		LCD_AVR_Print_String("Fecha: ");
		LCD_AVR_Print_Char((data_dia/10)+48);
		LCD_AVR_Print_Char((data_dia%10)+48);
		LCD_AVR_Print_Char('/');
		LCD_AVR_Print_Char((data_mes/10)+48);
		LCD_AVR_Print_Char((data_mes%10)+48);
		LCD_AVR_Print_Char('/');
		LCD_AVR_Print_Char((data_year/10)+48);
		LCD_AVR_Print_Char((data_year%10)+48);
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		
		if(data_diaS==0)LCD_AVR_Print_String("Lu");
		if(data_diaS==1)LCD_AVR_Print_String("Ma");
		if(data_diaS==2)LCD_AVR_Print_String("Mi");
		if(data_diaS==3)LCD_AVR_Print_String("Ju");
		if(data_diaS==4)LCD_AVR_Print_String("Vi");
		if(data_diaS==5)LCD_AVR_Print_String("Sa");
		if(data_diaS==6)LCD_AVR_Print_String("Do");
		
		sprintf(aux,"Temp: %4.1f",temp);
		LCD_AVR_Set_Cursor(0,3);
		LCD_AVR_Print_String(aux);
		LCD_AVR_Print_Char(0xDF);
		LCD_AVR_Print_Char('C');
		LCD_AVR_Print_String("        ");
		return;
	}
}

void menu0(void){
	if(config==0){
		LCD_AVR_Set_Cursor(0,0);
		LCD_AVR_Print_New_Char(1);
		LCD_AVR_Print_String("Reloj             ");
		}else{
		LCD_AVR_Set_Cursor(0,0);
		LCD_AVR_Print_String(" Reloj             ");
	}
	
	if(config==1){
		LCD_AVR_Set_Cursor(0,1);
		LCD_AVR_Print_New_Char(1);
		LCD_AVR_Print_String("Configurar Hora    ");
		}else{
		LCD_AVR_Set_Cursor(0,1);
		LCD_AVR_Print_String(" Configurar Hora   ");
	}
	if(config==2){
		LCD_AVR_Set_Cursor(0,2);
		LCD_AVR_Print_New_Char(1);
		LCD_AVR_Print_String("Configurar fecha   ");
		}else{
		LCD_AVR_Set_Cursor(0,2);
		LCD_AVR_Print_String(" Configurar fecha  ");
	}
	if(config==3){
		LCD_AVR_Set_Cursor(0,3);
		LCD_AVR_Print_New_Char(1);
		LCD_AVR_Print_String("Establecer alarma  ");
		}else{
		LCD_AVR_Set_Cursor(0,3);
		LCD_AVR_Print_String(" Establecer alarma  ");
	}
	
}

void menu1(void){
	LCD_AVR_Set_Cursor(0,0);
	LCD_AVR_Print_String("  Reloj despertador ");
	visualizar_Parametros();
		
	if(a_hor==data_hor && a_min==data_min && alarmaOn==1){
		PORTD^=(1<<5);
		}else{
		PORTD&=~(1<<5);
	}
	
	
	if(!(PIND & (1<<6))){
		while(!(PIND & (1<<6)));
		alarmaOn=0;
	}
	if(!(PIND & (1<<7))){
		while(!(PIND & (1<<7)));
		alarmaOn=0;
	}
	_delay_ms(200);
	
}

void menu2(void){
	while(menu==2){
		if(!(PIND & (1<<6))){
			while(!(PIND & (1<<6)));
			if(flag==0){
				data_seg++;
				if(data_seg==60)data_seg=0;
			}
			if(flag==1){
				data_min++;
				if(data_min==60)data_min=0;
			}
			if(flag==2){
				data_hor++;
				if(data_hor==23)data_hor=0;
			}
		}
		if(!(PIND & (1<<7))){
			while(!(PIND & (1<<6)));
			flag++;
			if(flag==3)flag=0;
		}
		
		if(flag==0){
			LCD_AVR_Set_Cursor(12,2);
			LCD_AVR_Print_String("  ");
			
		}
		if(flag==1){
			LCD_AVR_Set_Cursor(9,2);
			LCD_AVR_Print_String("  ");
			
		}
		if(flag==2){
			LCD_AVR_Set_Cursor(6,2);
			LCD_AVR_Print_String("  ");
		}
		_delay_ms(30);
		LCD_AVR_Set_Cursor(0,0);
		LCD_AVR_Print_String("Establecer hora:    ");
		LCD_AVR_Set_Cursor(0,1);
		LCD_AVR_Print_String("                    ");
		LCD_AVR_Set_Cursor(0,2);
		LCD_AVR_Print_String("Hora: ");
		LCD_AVR_Print_Char((data_hor/10)+48);
		LCD_AVR_Print_Char((data_hor%10)+48);
		LCD_AVR_Print_Char(':');
		LCD_AVR_Print_Char((data_min/10)+48);
		LCD_AVR_Print_Char((data_min%10)+48);
		LCD_AVR_Print_Char(':');
		LCD_AVR_Print_Char((data_seg/10)+48);
		LCD_AVR_Print_Char((data_seg%10)+48);
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Set_Cursor(0,3);
		LCD_AVR_Print_String("                    ");
		_delay_ms(100);
	}
	flag=0;
	ConfiRegRTC_Hora(DIR_RTC,data_seg,data_min,data_hor);
}

void menu3(void){
	while(menu==3){
		if(!(PIND & (1<<6))){
			while(!(PIND & (1<<6)));
			if(flag_f==0){
				data_dia++;
				if(data_dia==32)data_dia=1;
			}
			if(flag_f==1){
				data_mes++;
				if(data_mes==13)data_mes=1;
			}
			if(flag_f==2){
				data_year++;
				if(data_year==100)data_year=20;
			}
			if(flag_f==3){
				data_diaS++;
				if(data_diaS==7)data_diaS=0;
			}
		}
		if(!(PIND & (1<<7))){
			while(!(PIND & (1<<6)));
			flag_f++;
			if(flag_f==4)flag_f=0;
		}
		
		if(flag_f==0){
			LCD_AVR_Set_Cursor(7,1);
			LCD_AVR_Print_String("  ");
			
		}
		if(flag_f==1){
			LCD_AVR_Set_Cursor(10,1);
			LCD_AVR_Print_String("  ");
			
		}
		if(flag_f==2){
			LCD_AVR_Set_Cursor(13,1);
			LCD_AVR_Print_String("  ");
		}
		if(flag_f==3){
			LCD_AVR_Set_Cursor(6,2);
			LCD_AVR_Print_String("         ");
		}
		_delay_ms(30);
		LCD_AVR_Set_Cursor(0,0);
		LCD_AVR_Print_String("  Configurar fecha  ");
		LCD_AVR_Set_Cursor(0,1);
		LCD_AVR_Print_String("Fecha: ");
		LCD_AVR_Print_Char((data_dia/10)+48);
		LCD_AVR_Print_Char((data_dia%10)+48);
		LCD_AVR_Print_Char('/');
		LCD_AVR_Print_Char((data_mes/10)+48);
		LCD_AVR_Print_Char((data_mes%10)+48);
		LCD_AVR_Print_Char('/');
		LCD_AVR_Print_Char((data_year/10)+48);
		LCD_AVR_Print_Char((data_year%10)+48);
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Set_Cursor(0,2);
		LCD_AVR_Print_String("Dia:  ");
		if(data_diaS==0)LCD_AVR_Print_String("Lunes         ");
		if(data_diaS==1)LCD_AVR_Print_String("Martes        ");
		if(data_diaS==2)LCD_AVR_Print_String("Miercoles     ");
		if(data_diaS==3)LCD_AVR_Print_String("Jueves        ");
		if(data_diaS==4)LCD_AVR_Print_String("Viernes       ");
		if(data_diaS==5)LCD_AVR_Print_String("Sabado        ");
		if(data_diaS==6)LCD_AVR_Print_String("Domingo       ");
		LCD_AVR_Set_Cursor(0,3);
		LCD_AVR_Print_String("                    ");
	}
	flag_f=0;
	ConfiRegRTC_Fecha(DIR_RTC,data_diaS,data_dia,data_mes,data_year);
	WriteEEPROM(0x0004,data_diaS,data_dia,data_mes,data_year);
}

void menu4(void){
	while(menu==4){
		if(!(PIND & (1<<6))){
			while(!(PIND & (1<<6)));
			if(flag_a==0){
				a_min++;
				if(a_min==60)a_min=0;
			}
			if(flag_a==1){
				a_hor++;
				if(a_hor==23)a_hor=0;
			}
			if(flag_a==2){
				alarmaOn++;
				if(alarmaOn==2)alarmaOn=0;
			}
		}
		if(!(PIND & (1<<7))){
			while(!(PIND & (1<<6)));
			flag_a++;
			if(flag_a==3)flag_a=0;
		}
		
		if(flag_a==0){
			LCD_AVR_Set_Cursor(11,2);
			LCD_AVR_Print_String("  ");
			
		}
		if(flag_a==1){
			LCD_AVR_Set_Cursor(8,2);
			LCD_AVR_Print_String("  ");
		}
		if(flag_a==2){
			LCD_AVR_Set_Cursor(8,3);
			LCD_AVR_Print_String("   ");
		}
		
		_delay_ms(30);
		LCD_AVR_Set_Cursor(0,0);
		LCD_AVR_Print_String("Configurar alarma:");
		LCD_AVR_Set_Cursor(0,1);
		LCD_AVR_Print_String("                 ");
		LCD_AVR_Set_Cursor(0,2);
		LCD_AVR_Print_String("Alarma: ");
		LCD_AVR_Print_Char((a_hor/10)+48);
		LCD_AVR_Print_Char((a_hor%10)+48);
		LCD_AVR_Print_Char(':');
		LCD_AVR_Print_Char((a_min/10)+48);
		LCD_AVR_Print_Char((a_min%10)+48);
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		LCD_AVR_Print_Char(' ');
		if(alarmaOn==1){
			LCD_AVR_Set_Cursor(0,3);
			LCD_AVR_Print_String("ESTADO: ON          ");
			}else{
			LCD_AVR_Set_Cursor(0,3);
			LCD_AVR_Print_String("ESTADO: OFF         ");
		}
		_delay_ms(100);
	}
	flag_a=0;
	if(alarmaOn==1){WriteEEPROM(0x0000,a_hor,a_min,alarmaOn,0);}
	else{a_hor=0,a_min=0,WriteEEPROM(0x0000,a_hor,a_min,alarmaOn,0);}
}

void DataSerial(void){
	sprintf((char*)buffer_usart,"%02u;%02u;%02u;%02u;%02u;%02u;%02u;%02u;%.2f;%u;%u\n",data_hor,data_min,data_seg,data_dia,data_mes,data_year,a_hor,a_min,temp,alarmaOn,data_diaS);
	USART0_PrintString(buffer_usart);
	
}
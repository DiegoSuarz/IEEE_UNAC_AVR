/*
 * FAST_PWM.c
 *
 * Created: 9/07/2022 20:30:15
 * Author : Diego
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

void Config_FastPWM(void);


int main(void)
{
    Config_FastPWM();
    while (1) 
    {
		
		
    }
}

void Config_FastPWM(void){
	
	//configurar timer1 modo FAST PWM de 10 bits  
	TCCR1A |= (1<<WGM10) | (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//modo de operación FAST PWM (no invertido)
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1B1);
	
	//seleccionar el prescaler (pree = 8)
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~((1<<CS12)|(1<<CS10));
	
	//Configurar el pin de salida asociado al comparado 0C1
	DDRB |= (1<< PINB1); //pb1 salida
	
	/*Para configurar el Duty Cycle se carga un
	 valor en el registro OCR1A comprendido entre BOTTOM y TOP
	 0 y 1023 (ya que escogimos FAST PWM de 10 bits)
	
			 OCR1A      duty cycle 
			 1023		100%
			 512		50%
			 256		25%
			 102		10%
			 
	 si quiero un duty cycle del 30%:  0.3*1023=306.9 ->307
			 
	 Formula del PWM  FocsPWM = FOSC/N(1+TOP)
	 N: prescaler  FOSC: frecuencia de oscilacion   TOP: resolucion del PWM
	
	valores de prescaler: 1,8,64,256,1024
	valores de TOP (resolucion PWM): 8bits, 9bits, 10bits
	
	ejm: N=8   FOSC=16Mhz	TOP=10bits  (1023)
				
				FocsPWM = 16000000/8(1+102 3)
				foscPWM = 1953 hz ->1.9Khz
	 */
	
	//cargando un valor de duty cycle:
	//OCR1A = 512;	// duty cycle del 50%
	//OCR1A = 307;	// duty cycle del 30%	
	OCR1A = 818;	// duty cycle del80% 0.8*1023=818.4 ->818
}
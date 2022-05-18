/*
 * Read_gpio.c
 *
 * Created: 17/05/2022 22:42:47
 * Author : Diego
 */ 

#include <avr/io.h>


int main(void)
{
   
   DDRB |= (1<<5); // definiendo como salida el pin PB5
   DDRB &= ~(1<<7); // definiendo como entrada al pin PB7
   
   for(;;)
   {
	   if((PINB & (1<<7))==0){ // es lo mismo if(!(PINB & (1<<7)))
		   PORTB |= (1<<5); //poner el pin PB5 en alto (1 logico)
	   }else{
		    PORTB &= ~(1<<5);
	   }
	   	 	 
   }
   
}


/*
 * Timers_AVR.h
 *
 * Created: 31/05/2022 20:50:54
 *  Author: Diego
 */ 


#ifndef TIMERS_AVR_H_
#define TIMERS_AVR_H_

#define Valor_100ms 40536

void Timer1_Init(void);
void Timer2_Init(void);

//extern #define LedC0_Toggle()	(PORTC ^= (1<<PINC0))

#endif /* TIMERS_AVR_H_ */
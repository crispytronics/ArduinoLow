#include "ArduinoLow.h"
#include <avr/interrupt.h>

void on(char prr)
{
	PRR &= ~prr;
}

void off(char prr)
{
	PRR |= prr;
}

void sleepMode(char mode)
{
	SMCR |= mode;
}

void sleep()
{
	SMCR|=(1<<SE);
	asm volatile("sleep"::);
	SMCR&=~(1<<SE);
}

void sleepTimer(char prescaler)
{
	//Disable timer2 interrupts
	TIMSK2  = 0;
	//Enable asynchronous mode
	ASSR  = (1<<AS2);
	//set initial counter value
	TCNT2=0;
	//set prescaler
	TCCR2B &= ~7;
	TCCR2B |= prescaler;
	//wait for registers update
	while (ASSR & ((1<<TCN2UB)|(1<<TCR2BUB)));
	//clear interrupt flags
	TIFR2  = (1<<TOV2);
	//enable TOV2 interrupt
	TIMSK2  = (1<<TOIE2);
}

ISR(TIMER2_OVF_vect)
{
	asm volatile("nop"::);
}
#include "ArduinoLow.h"
#include <avr/interrupt.h>
#include <avr/delay.h>

char _isTicking = 0;
uint16_t _delay = 0;

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

char isTicking() {
	return _isTicking;
}

void sleep()
{
	if (ASSR & ((1<<TCN2UB)|(1<<TCR2BUB))) {
		// timer not ticking yet
		_isTicking = 0;
		_delay_ms(_delay);
	}
	else {
		_isTicking = 1;
		//clear interrupt flags
		TIFR2  = (1<<TOV2);
		//enable TOV2 interrupt
		TIMSK2  = (1<<TOIE2);
		// sleep
		SMCR|=(1<<SE);
		asm volatile("sleep"::);
		SMCR&=~(1<<SE);
	}
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

	switch(prescaler) {
		case PRESCALE_1:
			_delay = 16;
			break;
		case PRESCALE_8:
			_delay = 125;
			break;
		case PRESCALE_32:
			_delay = 500;
			break;
		case PRESCALE_64:
			_delay = 1000;
			break;
		case PRESCALE_128:
			_delay = 2000;
			break;
		case PRESCALE_256:
			_delay = 4000;
			break;
		case PRESCALE_1024:
			_delay = 16000;
			break;
		default:
			_delay = 0;
	}
}

ISR(TIMER2_OVF_vect)
{
	asm volatile("nop"::);
}
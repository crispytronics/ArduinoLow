#include "ArduinoLow.h"

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
	SMCR |= (1 << SE);
	asm("sleep");
}

void sleepTimer(char prescaler)
{
	TIMSK2 &= ~((1 << OCIE2B) | (1 << OCIE2B) | (1 << TOIE2));
	ASSR |= (1 << AS2);
	TCNT2 = 0;
	OCR2A = 0;
	OCR2B = 0;
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM21) | (1 << WGM20));
	TCCR2B &= ~((1 << FOC2A) | (1 << FOC2B) | (1 << WGM22));
	TCCR2B |= PRESCALE_1024;
	TCCR2B &= prescaler;
	while(ASSR & ((1 << TCN2UB) | (1 << OCR2AUB) | (1 << OCR2AUB) | (1 << TCR2AUB) | (1 << TCR2BUB))) {
	}
	TIFR2 |= (1 << OCF2B) | (1 << OCF2A) | (1 << TOV2);
	TIMSK2 |= (0 << OCIE2B) | (0 << OCIE2B) | (1 << TOIE2);
}
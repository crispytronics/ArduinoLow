#include <avr/io.h>

/* Power Reduction */
#define PRR_TWI    (1 << 7)
#define PRR_TIMER2 (1 << 6)
#define PRR_TIMER0 (1 << 5)
#define PRR_TIMER1 (1 << 3)
#define PRR_SPI    (1 << 2)
#define PRR_UART   (1 << 1)
#define PRR_ADC    (1 << 0)

/* Sleep Modes */
#define SLEEP_IDLE 0
#define SLEEP_ADC_NOISE_REDUCTION (1 << SM0)
#define SLEEP_POWER_DOWN (1 << SM1)
#define SLEEP_POWER_SAVE (1 << SM1) | (1 << SM0)
#define SLEEP_STANDBY (1 << SM2) | (1 << SM1)
#define SLEEP_EXTENDED_STANDBY (1 << SM2) | (1 << SM1) | (1 << SM0)

/* Sleep Timer Prescaler */
#define PRESCALE_0    0 // timer off
#define PRESCALE_1    1 // 7.813 ms
#define PRESCALE_8    2 // 62.5 ms
#define PRESCALE_32   3 // 250 ms
#define PRESCALE_64   4 // 500 ms
#define PRESCALE_128  5 // 1 s
#define PRESCALE_256  6 // 2 s
#define PRESCALE_1024 7 // 8 s

void on(char prr);

void off(char prr);

void sleepMode(char mode);

void sleep();

void sleepTimer(char prescaler);
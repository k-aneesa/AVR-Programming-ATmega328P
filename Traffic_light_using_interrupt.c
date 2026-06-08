/*
 * Traffic_light_using_interrupt.c
 *
 * Created: 6/8/2026 3:25:12 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define  GREEN	PB0
#define  ORANGE PB1
#define  RED	PB2

volatile uint8_t flag = 0;

ISR(INT0_vect) // ISR for INT0 PD2
{
	flag = 1; // flag set for button press
}

void external_interrupt_config()
{
	sei(); // global interrupt enable
	// INT0 interrupt enable
	EIMSK |=(1<<INT0);
	// config. INT0 for falling edge trigger
	EICRA |=(1<<ISC01);  // ISC01= 1
	EICRA &=~ (1<<ISC00); // ISC01= 0
	// INT0 interrupt enable
	//EIMSK |=(1<<INT0);
	//sei();// global interrupt enable
}


int main(void)
{
   // config PORTB pins as output for LEDs(Traffic Lights)
   DDRB |= (1 << GREEN) | (1 << ORANGE) | (1 << RED);
    //  config. INT0 pin (PD2) as input with internal pullup
	DDRD &=~(1 << PD2);
	PORTD |= (1 << PD2);
	
	external_interrupt_config();
	
    while (1) 
    {
		PORTB |= (1 << GREEN);
		_delay_ms(10000);  // 10 seconds
		PORTB &= ~(1 << GREEN);
		_delay_ms(3000);
		if (flag)
		{
			PORTB |= (1 << GREEN);
			_delay_ms(10000);
			PORTB &= ~(1 << GREEN);
			flag=0;
			continue;
		}
		
		PORTB |= (1 << ORANGE);
		_delay_ms(3000);  // 10 seconds
		PORTB &= ~(1 << ORANGE);
		if (flag)
		{
			PORTB |= (1 << GREEN);
			_delay_ms(10000);
			PORTB &= ~(1 << GREEN);
			flag=0;
			continue;
		}
		
		PORTB |= (1 << RED);
		_delay_ms(10000);  // 10 seconds
		PORTB &= ~(1 << RED);
		if (flag)
		{
			PORTB |= (1 << GREEN);
			_delay_ms(10000);
			PORTB &= ~(1 << GREEN);
			flag=0;
			continue;
		}
    }
}


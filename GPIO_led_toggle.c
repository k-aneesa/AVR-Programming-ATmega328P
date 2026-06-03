/*
 * GPIO_led_toggle.c
 *
 * Created: 6/3/2026 1:56:08 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* config PORTD pin5 as output*/
	DDRD |= (1 << PD5);
    while (1) 
    {
		/* Making the pin5 high for 3 seconds*/
		PORTD |= (1 << PD5);
		_delay_ms(3000); // wait for 3 seconds
		
		/* Making the pin5 low for 5 seconds*/
		PORTD &= ~(1 << PD5);
		_delay_ms(5000);
    }
}


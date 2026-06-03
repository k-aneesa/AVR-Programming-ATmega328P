/*
 * GPIO_led_train.c
 *
 * Created: 6/3/2026 10:32:06 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Make PORTB as output*/
	DDRB = 0b11111111;
    while (1) 
    {
		for(uint8_t i=0; i<8; i++)
		{
			PORTB |=(1<< i);
			_delay_ms(1000);
			PORTB &=~(1<< i);
			_delay_ms(1000);
			
		}
    }
}


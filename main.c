/*
 * 4led_binary_count.c.c
 *
 * Created: 6/6/2026 6:18:04 AM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SWITCH_PIN PD2

void led_count(uint8_t count) // for updating leds based on count value
{
	PORTB = (PORTB & 0xF0) | (count & 0x0F); 
	/* if count = 8 ie; 00001000 and PORTB = 10101000
	count & 0X0F ==> 00001000		PORTB & 0xF0 ==> 10101000
					 00001111					     11110000
				&   -----------					&  -----------
				     00001000						 10100000
					 
	hence;	(PORTB & 0xF0) | (count & 0x0F)==>10100000 | 00001000	=10100000
																	 00001000
																| --------------
																	 10101000	 ==> hence the lower upper 4 bit values of portb remain unchanged and lower 4 bits entered as count value																															
	*/
}


int main(void)
{
    // config. PORTB pins 0-3 as output for LEDs
	DDRB |=(1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
	// clear all LEDS initially
	PORTB &= 0xF0;
	 
	// config. PD2 as input for switch with internal pullup
	 DDRD &=~(1 << SWITCH_PIN );
	 PORTD |=(1 << SWITCH_PIN);
	 
	 uint8_t counter =0;
	 led_count(counter);
	 
    while (1) 
    {
		// cheking for button press
		if(!(PIND & (1 << SWITCH_PIN)))
		{
			_delay_ms(50); // wait for debounce
			if(!(PIND & (1 << SWITCH_PIN)))
			{
				counter = (counter + 1) & 0x0F;
				 led_count(counter);
				 /* it  increment counter and wrap the counter at 16
				 if the count reaches 15 , count +1 = 16 ==> 10000
				 when we mask it with 0x0f,, ie, 00010000 &
												 00001111
												----------
												 00000000  
						hence counter returns to 0*/
				 // wait until button released
				  while (!(PIND & (1 << SWITCH_PIN)));
			}
		}
				
    }
}


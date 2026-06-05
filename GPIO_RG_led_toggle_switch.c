/*
 * GPIO_RG_led_toggle_switch.c
 *
 * Created: 6/3/2026 2:15:16 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
  /* Set PORTB pin 0 and 1  as output for Red and Green LEDs */
   DDRB |= ((1 << PB0) | (1 << PB1));
  /* Set PORTD pin 3 as input for switch*/
   DDRD &= ~(1 << PD2);
   PORTB |=(1 << PB0);  // red led ON
   PORTB &=~(1 << PB1); // Green led OFF
    while (1) 
    {
		if((PIND & (1 << PD2))==0) // check for button press
		{
			_delay_ms(50 ); // wait for debounce
			PORTB &=~(1 << PB0); // red off
			PORTB |=(1 << PB1);  // green on
		}
	

			if(!(PIND & (1 << PD2)))  // check for button press
			{
				
				_delay_ms(50 );
				PORTB |=(1 << PB0); // red on
				PORTB &=~(1 << PB1); // green off
				
			}
		
		else
		{
			PORTB &=~(1 << PB0); // red off
			PORTB |=(1 << PB1);  //green on
		}
		
		while(!(PIND & (1 << PD2))); // wait for release
		}
		
}





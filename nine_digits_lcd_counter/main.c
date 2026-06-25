/*
 * nine_digits_lcd_counter.c
 *
 * Created: 6/25/2026 1:54:47 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define BUTTON PD2
#define SHORT_PRESS 1
#define LONG_PRESS  2

/* Function to update lcd with 9 digits*/
void lcd_update(uint32_t value)
{
	char digits[9];
	for(int i=8; i>=0; i--)
	{
		digits[i]=(value%10)+'0' ;  // conversion to ASCII
		value/=10;
	}
	lcd_clear();
	lcd_set_cursor(0,0);
	for (int i=0; i,9; i++)
	{
		lcd_data(digits[i]); // sending digits to lcd
	}
}

/* Function to check pressing duration*/
uint8_t button_press(void)
{
	 if (!(PIND & (1 << BUTTON))) 
	 {
		 uint16_t ms=0;
		 while (!(PIND & (1<<BUTTON))) 
		 {
			 _delay_ms(10);
			 ms+=10;
			 if(ms>=2000) return LONG_PRESS;  // >=2s
		 }
		 return SHORT_PRESS;
	 }
	 return 0;   // no press
}
int main(void)
{
	lcd_init();
	lcd_clear();
	
	
   DDRD &=~(1 << BUTTON);   // PD2 input
   PORTD |= (1 << BUTTON);   // Enable pull-up
   
   uint32_t counter =0;
   lcd_update(counter);
   
    while (1) 
    {
		uint8_t press= button_press();
		if(press == SHORT_PRESS)
		{
			counter++;
			if(counter >999999999) counter=0;
			lcd_update(counter);
		}
			
    }
}


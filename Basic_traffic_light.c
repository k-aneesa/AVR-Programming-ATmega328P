/*
 * Basic_traffic_light.c
 *
 * Created: 6/7/2026 10:57:13 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(uint16_t seconds)
 {
	 //step 1:
	 TCNT0 = 0;
	 //step 2: select CTC mode
	 TCCR0A |= (1 << WGM01);
	 TCCR0A &= ~(1 << WGM00);
	 //step 3: prescalar value : 64
	 TCCR0B |=((1<<CS01) | (1<<CS00));
	 TCCR0B &= ~(1<<CS02);
	 /*
	     calculation part
		 fclk = 16000000
		 prescalar = 64
		 new frequency =250000
		 1 tick = 1/ 250000 = 4 microsec
		 1ms = 1000 microsec
		 1000/4 = 250
		 250-1=249  value to be loaded
	*/	 
	 OCR0A = 249;
	 for (uint16_t i=0;i< seconds *1000; i++)
	 {
		 while(!(TIFR0 & (1<< OCF0A)));
		 TIFR0 |=(1<<OCF0A);
	 }
 }
 
 
int main(void)
{
   // initiallising LEDs for traffic light
   DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);  //PB0=Green , PB1=Orange , PB2=Red
   
    while (1) 
    {
		PORTB = (1 << PB0); // Green ON
		delay_1s(10);
		
		PORTB = (1 << PB1); // Orange ON
		delay_1s(3);
			
		PORTB = (1 << PB2); // Red ON
		delay_1s(10);
		
    }
}


/*
 * PWM_Led_control.c
 *
 * Created: 6/10/2026 2:28:47 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void dutycycle_transition();

//Duty cycle OCR0A Values 
uint8_t duty_cycles[5] = {64,128,192,255,0};
volatile uint8_t duty_index =0;


void fast_pwm_init()
{
	//Step1: config. PD6 as output
	DDRD |=(1 << PD6);
	
	//Step2: config in fast pwm mode
	TCCR0A |=(1<<WGM00) | (1<<WGM01);
	
	//Step3: Choosing Non- inverting mode
	TCCR0A |=(1<<COM0A1);
	TCCR0A &=~(1<<COM0A0);
	
	/* Fast PWM mode :  fclk/(n*256)
	fclk=16000000   n=8
	16000000/(8*256)=7812.5 ~ 7.8kHz ~8kHz */
	
	//Step4: Choosing prescalar value as 8
	TCCR0B |=(1<<CS01) ;
	/*Step5: setting the value in OCR0A
	 OCR0A= (Duty cycle(%)/100)255
		for 25%;   (25/100)255=64
		for 50%;   (50/100)255=128
		for 75%;   (75/100)255=192
		for 100%;   (100/100)255=255
		for 0%;       0					*/
								
	OCR0A=duty_cycles[duty_index];
}

int main(void)
{
	fast_pwm_init();  // initializing pwm
	
	// config. PD2 as button input
	DDRD &=~(1 << PD2);// pd2 as input
	PORTD |=(1 << PD2); // pullup enable
    while (1) 
    {
		// button press
		if(!(PIND & (1 << PD2)))
		{
			_delay_ms(50);
			if(!(PIND & (1 << PD2)))
			{
				dutycycle_transition();
				
				while (!(PIND & (1 << PD2))); 
			}
		}
			
    }
}

 void dutycycle_transition()
{
	duty_index++;
	if (duty_index >= 5) duty_index = 0; // wrap around
	OCR0A=duty_cycles[duty_index];
	
}



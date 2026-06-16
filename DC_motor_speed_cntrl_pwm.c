/*
 * DC_motor_speed_cntrl_pwm.c
 *
 * Created: 6/13/2026 5:22:28 PM
 * Author : ANEESA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define BUTTON   PD2   // Push-button connected to PD2
#define LED		 PD6   // OC0A output pin

uint8_t duty_cycles[] = {64, 128, 192, 255, 0}; // duty cycle values 25%, 50%, 75%, 100%, OFF
uint8_t duty_index = 0;

void timer0_init(void)
 {
	// Set PD6 (OC0A) as output
	DDRD |= (1 << LED);

	// Fast PWM mode: WGM01=1, WGM00=1, WGM02=0
	// Clear OC0A on compare match, non-inverting mode
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
	TCCR0A &= ~(1 << COM0A0);

	// Pre-scaler = 64 ? PWM frequency ~976 Hz
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TCCR0B &= ~(1 << CS02);

	// Start with 25% duty cycle
	OCR0A = duty_cycles[duty_index];
}

void button_init(void) 
{
	// Set PD2 as input with pull-up enabled
	DDRD &= ~(1 << BUTTON);
	PORTD |= (1 << BUTTON);
}

uint8_t button_pressed(void) 
{
	if (!(PIND & (1 << BUTTON)))
	 { 
		 
		_delay_ms(50); // debounce delay
		if (!(PIND & (1 << BUTTON)))
		 {
			while (!(PIND & (1 << BUTTON))); // wait until release
			return 1;
		}
	}
	return 0;
}

int main(void)
 {
	timer0_init();
	button_init();

	while (1)
	 {
		if (button_pressed())
		 {
			duty_index++;
			if (duty_index >= 5) duty_index = 0; // wrap around
			OCR0A=duty_cycles[duty_index];
		}
	}
}

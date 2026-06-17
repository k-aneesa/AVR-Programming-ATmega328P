/*
 * cooling_system_with_LM35.c
 *
 * Created: 6/16/2026 3:03:17 PM
 * Author : ANEESA
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BUTTON   PD2   // Push button on INT0
#define MOTOR    PB1   // OC1A pin for PWM output
#define LM35	 0     // ADC0 channel

volatile uint8_t systemOn = 0; // 0 = OFF, 1 = ON

void adc_init(void)
{
	// step1: setting the reference voltage , AVcc
	ADMUX |= (1<<REFS0);
	// step2: ADC Enable
	ADCSRA |= (1<<ADEN);
	// Step3: Choosing the prescalar value : 128 ~ 125kHz
	ADCSRA |= ((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));	
}

/*to read adc value from the corresponding given channel (0 -7)*/
uint16_t read_adc(uint8_t channel)
{
	/*step4: limit the choosen channel b/w 0 - 7
	-channel limit is 0 -7 (0000 _0111)
	-if choose 8 ==1000  ie; beyond our limit
	-channel = 8(1000)
	-channel & 0x07= 0000 1000 & 0000 0111 == 0000 0000
	-so automatically channel is selected as 0 ie;  with in our limit
	*/
	channel &= 0x07;
	// step 5:  to clear the previous channel and update the register with the new channel
	ADMUX = (ADMUX & 0xF0) | channel;
	//step6: to start the adc conversion 
	ADCSRA |= (1<<ADSC);
	// step7: wait until the conversion is done or completed
	while(ADCSRA & (1<<ADSC));
	// step8 : return adc 
	return ADC;	
}

//ADC reading to temperature
float Read_Temperature(void)
 {
	uint16_t adcValue =read_adc(LM35);
	float voltage = (adcValue * 5.0) / 1024.0; // Assuming 5V reference
	return voltage * 100.0; // °C
}

// Initialize PWM on OC1A (PB1)
void pwm_init(void)
{
	DDRB |= (1 << MOTOR); // Set PB1 as output
	TCCR1A = (1 << COM1A1) | (1 << WGM10); // Fast PWM 8-bit, non-inverting
	TCCR1B = (1 << WGM12) | (1 << CS11);   // Prescaler = 8
}

void Set_MotorSpeed(uint8_t duty) 
{
	OCR1A = duty;
}

void button_init(void) 
{
	DDRD &= ~(1 << BUTTON);   // Input
	PORTD |= (1 << BUTTON);   // Pull-up enabled
	EICRA |= (1 << ISC01);        // Falling edge trigger
	EIMSK |= (1 << INT0);         // Enable INT0
}

void Control_Motor(float temperature)
{
	if (temperature < 30.0) 
	{
		Set_MotorSpeed(80);   // ~30% duty
	} 
	else if (temperature < 40.0)
	{
		Set_MotorSpeed(150);  // ~60% duty
	} 
	else
	{
		Set_MotorSpeed(230);  // ~90% duty
	}
}

ISR(INT0_vect) 
{
	systemOn ^= 1; // Toggle between 0 and 1
}

int main(void)
 {
	 button_init();
	 adc_init();
	 pwm_init();
	 sei(); // Enable global interrupts

	while (1)
	 {
		if (systemOn)
		 {
			float temp = Read_Temperature();
			Control_Motor(temp);
		 } 
		 else
		 {
			Set_MotorSpeed(0); // Motor OFF
		 }
	}
}
	

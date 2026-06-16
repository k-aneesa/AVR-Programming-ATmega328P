/*
 * status_heartbeat_led.c.c
 *
 * Created: 6/16/2026 2:17:08 PM
 * Author : ANEESA
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init(void)
 {
	
	TCCR1B |= (1 << WGM12);  // Configure Timer1 in CTC mode 
	
	TCCR1B |= (1 << CS12) | (1 << CS10);  // Prescaler = 1024
	/*	Compare value for 2 seconds at 16 MHz
		Formula: OCR1A = (F_CPU / (Prescaler * Frequency)) - 1
		Frequency = 0.5 Hz (toggle every 2s)
		(16000000UL / (1024UL * 0.5)) - 1 = 31249	*/
	OCR1A =  31249;
	
	TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 Compare Match A interrupt
 }
 
 void timer2_init(void)
  {
	 
	 TCCR2A |= (1 << WGM21);	// Configure Timer2 in CTC mode
	 // Prescaler = 128 
	 TCCR2B |= (1 << CS22) | (1 << CS20);  // 128 prescaler
	 /*	Compare value for 500 ms at 16 MHz
		Frequency = 2 Hz (toggle every 0.5s)
		(16000000UL / (128UL * 2)) - 1 = 
		OCR2A = ;  // ? 62499, but too large for 8-bit
		Instead, we generate smaller ticks and count in ISR */
	 OCR2A = 249;  // 2 ms tick (16MHz / 128 * (249+1) = 500 Hz)
	
	 TIMSK2 |= (1 << OCIE2A);   // Enable Timer2 Compare Match A interrupt
 }
 
 volatile uint16_t heartbeat_counter = 0;

 ISR(TIMER1_COMPA_vect)
 {
	 PORTB ^= (1 << PB1);	// Toggle Status LED (PB1) every 2s
 }
 
 
 ISR(TIMER2_COMPA_vect) 
 {
	 // Count 250 ticks of 2 ms = 500 ms
	 heartbeat_counter++;
	 if (heartbeat_counter >= 250) 
	 {
		 PORTB ^= (1 << PB2);  // Toggle Heartbeat LED
		 heartbeat_counter = 0;
	 }
 }
 
 int main(void) {
	 // Configure PB1 and PB2 as outputs
	 DDRB |= (1 << PB1) | (1 << PB2);

	 // Initialize timers
	 timer1_init();
	 timer2_init();

	 // Enable global interrupts
	 sei();

	 while (1) 
	 {
		 // Main loop does nothing, LEDs are handled in ISRs
	 }
 }

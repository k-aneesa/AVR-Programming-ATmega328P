/*
 * lcd.h
 *
 * Created: 4/23/2026 8:16:33 PM
 *  Author: ANEESA
 */ 

#ifndef LCD_H_
#define LCD_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//ATmega328P RS = B4, R/W = Ground, EN = B3,  D4, D5, D6, D6, D7 - this is our connection
//Arduino UNO board rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  This is our connection


// define some macros for the pins used

// for RS pin
#define LCD_RS_PORT   PORTB
#define LCD_RS_DDR    DDRB
#define LCD_RS_PIN    PB4

// for enable pin EN
#define LCD_EN_PORT   PORTB
#define LCD_EN_DDR    DDRB
#define LCD_EN_PIN    PB3

// for data/commands
#define LCD_D_PORT    PORTD
#define LCD_D_DDR     DDRD
#define LCD_D7_PIN    PD2
#define LCD_D6_PIN    PD3
#define LCD_D5_PIN    PD4PD5

#define LCD_D4_PIN    

// now lets declare  our  functions

void lcd_init(void);  					// for initialization sequence
void lcd_cmd(uint8_t c);				// for commands(instructions
void lcd_data(uint8_t d);				// for data
void lcd_set_cursor(uint8_t row, uint8_t col);		  // for setting cursor(row: 0 or 1, col: 0..15)
void lcd_print(const char *s);				// to print string
void lcd_clear(void);					// to clear_lcd
void lcd_home(void);					// to return cursor to origin (row=0. Column =0)

void lcd_print_uint16(uint16_t v);		// to print an integer value
void lcd_print_float(float value);



#endif /* LCD_H_ */

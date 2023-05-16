﻿
#ifndef LCD_H_
#define LCD_H_

#include <inttypes.h>

/*
 * To be used with lcd_write()
 */
enum lcd_register
{
	INSTRUCTION,	// to write data to the Instruction Register
	DATA			// to write data (characters) to the Data Register
};

/*
 * To be used with lcd_set_cursor_mode()
 */
enum lcd_cursor
{
	CURSOR_OFF		= 0x0,
	CURSOR_ON		= 0x0E,		// UPPGIFT: ändra värdet!
	CURSOR_BLINK	= 0x0F			// UPPGIFT: ändra värdet!
};

void lcd_init(void);
void lcd_write(enum lcd_register, uint8_t);
void lcd_write_str(char *);
void lcd_clear(void);
void lcd_set_cursor_mode(enum lcd_cursor);
void lcd_set_cursor_pos(uint8_t, uint8_t);

#endif /* LCD_H_ */
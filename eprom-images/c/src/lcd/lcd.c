#include "65c02.h"
#include "lcd.h"

void wait_while_busy();

void lcd_send_instruction(const uint8_t instruction)
{
	wait_while_busy();
	STA(PORTB, instruction);
	STA(PORTA, 0x00);
	STA(PORTA, E);
	STA(PORTA, 0x00);
}

void lcd_write_char(const uint8_t character)
{
	wait_while_busy();
	STA(PORTB, character);
	STA(PORTA, RS);
	STA(PORTA, (RS | E));
	STA(PORTA, RS);
}

void lcd_write_string(uint8_t* string)
{
	while(*string)
	{
		lcd_write_char(*string);
		++string;
	}
}

void wait_while_busy()
{
	STA(DDRB, 0x00);	/* Set all PORTB pins to read */

	STA(PORTA, RW);
	STA(PORTA, (RW | E));
	do {} while (LDA(PORTB) & 0x80);

	STA(PORTA, RW);
	STA(DDRB, 0xff);	/* Reset all PORTB pins to output */
}


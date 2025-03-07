#include "65c02.h"
#include "lcd.h"

void wait_while_busy()
{
	STA(DDRB, 0x00);	/* Set all PORTB pins to read */

	STA(PORTA, RW);
	STA(PORTA, (RW | E));
	do {} while (LDA(PORTB) & 0x80);

	STA(PORTA, RW);
	STA(DDRB, 0xff);	/* Reset all PORTB pins to output */
}

void send_instruction(const uint8_t instruction)
{
	STA(PORTB, instruction);
	STA(PORTA, 0x00);
	STA(PORTA, E);
	STA(PORTA, 0x00);
	wait_while_busy();
}

void write_char(const uint8_t character)
{
	STA(PORTB, character);
	STA(PORTA, RS);
	STA(PORTA, (RS | E));
	STA(PORTA, RS);
	wait_while_busy();
}

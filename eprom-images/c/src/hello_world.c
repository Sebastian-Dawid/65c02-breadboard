#include "65c02.h"
#include "lcd/lcd.h"

const unsigned char msg[] = "Hello, world!";

void main()
{
	STA(DDRB, 0xff);	/* Set all PORTB pins to output. */
	STA(DDRA, 0b11100000);	/* Set the upper three pins of PORTA to output. */

	lcd_send_instruction(INIT);
	lcd_send_instruction(DISP_ON);
	lcd_send_instruction(NO_SHIFT);
	lcd_send_instruction(CLS);

	lcd_write_string((uint8_t*)msg);

	do {} while (1);
}

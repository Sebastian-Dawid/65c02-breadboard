#include "65c02.h"
#include "lcd/lcd.h"
#include "common/common.h"

void main()
{
	uint8_t* msg;
	uint8_t message[9] = { '0','0','0','0','0','0','0','0','0' };
	STA(DDRB, 0xff);	/* Set all PORTB pins to output. */
	STA(DDRA, 0b11100000);	/* Set the upper three pins of PORTA to output. */

	lcd_send_instruction(INIT);
	lcd_send_instruction(DISP_ON);
	lcd_send_instruction(NO_SHIFT);
	lcd_send_instruction(CLS);

	msg = bin_to_dec(1729, (uint8_t*)message, 9);
	// write only the generated decimal number
	lcd_write_string(msg);
	lcd_send_instruction(NEXT_LINE);
	// write full buffer on the next line
	lcd_write_string(message);

	do {} while (1);
}

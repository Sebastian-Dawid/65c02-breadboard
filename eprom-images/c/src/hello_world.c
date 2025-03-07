#include "65c02.h"
#include "lcd/lcd.h"

const unsigned char msg[] = "Hello, world!";

void main()
{
	register unsigned char x;

	STA(DDRB, 0xff);	/* Set all PORTB pins to output. */
	STA(DDRA, 0b11100000);	/* Set the upper three pins of PORTA to output. */

	send_instruction(INIT);
	send_instruction(DISP_ON);
	send_instruction(NO_SHIFT);
	send_instruction(CLS);

	for (x = 0; x < sizeof(msg) - 1; ++x)
	{
		write_char(msg[x]);
	}

	do {} while (1);
}

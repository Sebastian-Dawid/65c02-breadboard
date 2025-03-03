#define STA(address, value) ((*(volatile unsigned char*)(address)) = (value))
#define LDA(address) (*(volatile unsigned char*)(address))

#define DDRA		0x6003
#define DDRB		0x6002
#define PORTA		0x6001
#define PORTB		0x6000

#define E		0b10000000
#define RW		0b01000000
#define RS		0b00100000

#define INIT		0b00111000
#define DISP_ON		0b00001110
#define NO_SHIFT	0b00000110
#define CLS		0b00000001

const unsigned char msg[] = "Hello, world!";

void wait_while_busy();
void send_instruction(unsigned char);
void write_char(unsigned char);

void main()
{
	unsigned char x;

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

void wait_while_busy()
{
	STA(DDRB, 0x00);	/* Set all PORTB pins to read */

	do {
		STA(PORTA, RW);
		STA(PORTA, (RW | E));
	}
	while (LDA(PORTB) & 0x80);

	STA(PORTA, RW);
	STA(DDRB, 0xff);	/* Reset all PORTB pins to output */
}

void send_instruction(unsigned char instruction)
{
	STA(PORTB, instruction);
	STA(PORTA, 0x00);
	STA(PORTA, E);
	STA(PORTA, 0x00);
	wait_while_busy();
}

void write_char(unsigned char character)
{
	STA(PORTB, character);
	STA(PORTA, RS);
	STA(PORTA, (RS | E));
	STA(PORTA, RS);
	wait_while_busy();
}

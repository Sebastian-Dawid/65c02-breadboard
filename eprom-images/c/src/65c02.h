/*
 *
 * Helpers for loading and storing data at literal addresses.
 *
 */
#define STA(address, value) ((*(volatile unsigned char*)(address)) = (value))
#define LDA(address) (*(volatile unsigned char*)(address))

/*
 *
 * 65C22 VIA registers, ports and iterrupts
 *
 */
#define PORTB		0x6000
#define PORTA		0x6001
#define DDRB		0x6002
#define DDRA		0x6003

#define T1CL		0x6004
#define T1CH		0x6005
#define T1LL		0x6004
#define T1LH		0x6005

#define ACR		0x600b
#define PCR		0x600c
#define IFR		0x600d
#define IER		0x600e

#define CA1		0x02
#define TIMER1		0x40

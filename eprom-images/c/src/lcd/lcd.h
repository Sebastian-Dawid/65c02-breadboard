/*******************************************/
/* Basic HD44780U LCD API                  */
/* Author: Sebastian Dawid                 */
/* E-Mail: sdawid@techfak.uni-bielefeld.de */
/*******************************************/

#include <stdint.h>

/*
 *
 * LCD Instructions
 *
 */
#define E		0b10000000
#define RW		0b01000000
#define RS		0b00100000

#define INIT		0b00111000
#define DISP_ON		0b00001110
#define NO_SHIFT	0b00000110
#define CLS		0b00000001

void send_instruction(const uint8_t instruction);
void write_char(const uint8_t character);

#include "65c02.h"
#include "common.h"

uint8_t* bin_to_dec(const uint16_t number, uint8_t*const string, uint8_t length)
{
	uint8_t c;

	--length;
	*(string + length) = 0;

	// value = number
	asm ("ldy #%o", number);
	asm ("lda (sp),y");
	asm ("sta tmp1");
	asm ("iny");
	asm ("lda (sp),y");
	asm ("sta tmp2");

divide:
	--length;
	// mod10 = 0
	asm ("stz tmp3");
	asm ("stz tmp4");
	asm ("clc");

	// i = 16
	asm ("ldx #16");
divloop:
	// rol value
	asm ("rol tmp1");
	asm ("rol tmp2");
	// rol mod10
	asm ("rol tmp3");
	asm ("rol tmp4");

	// a,y = dividend - divisor
	asm ("sec");
	asm ("lda tmp3");
	asm ("sbc #10");
	asm ("tay");
	asm ("lda tmp4");
	asm ("sbc #0");
	asm ("bcc %g", ignore_result);

	// store mod10
	asm ("sty tmp3");
	asm ("sta tmp4");

ignore_result:
	// --i
	asm ("dex");
	asm ("bne %g", divloop);

	// rol value
	asm ("rol tmp1");
	asm ("rol tmp2");

	asm ("ldy #%o", c);
	asm ("lda tmp3");
	asm ("clc");
	asm ("adc #$30");
	asm ("sta (sp),y");

	*(string + length) = c;

	if (!length)
		goto end;

	// while value != 0
	asm ("lda tmp1");
	asm ("ora tmp2");
	asm ("bne %g", divide);


end:
	return (string + length);
}

uint8_t* bin_to_hex(uint16_t number, uint8_t*const string, uint8_t length)
{
	uint8_t c;
	--length;
	*(string + length) = 0;

	while (number && length > 0)
	{
		length--;
		c = 0xf & number;
		*(string + length) = (c < 0xa) ? c + '0' : c + ('A'-10);
		number = number >> 4;
	}

	if (length > 1)
	{
		length--;
		*(string + length) = 'x';
		length--;
		*(string + length) = '0';
	}

	return (string + length);
}

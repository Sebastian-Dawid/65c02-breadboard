PORTB	= $6000
PORTA	= $6001
DDRB	= $6002
DDRA	= $6003

T1CL	= $6004
T1CH	= $6005
T1LL	= $6006
T1LH	= $6007

ACR	= $600b
PCR	= $600c
IFR	= $600d
IER	= $600e

CA1	= $02
TIMER1	= $40

value	= $0200	;;; 2 bytes
mod10	= $0202	;;; 2 bytes
message	= $0204	;;; 6 bytes
counter	= $020a

E	= %10000000
RW	= %01000000
RS	= %00100000

	.org $8000
reset:
	ldx #$ff
	txs
	cli

	lda #($80 | CA1)
	sta IER

	stz ACR		;;; T1 one shot timed interrupt
	stz PCR		;;; Trigger CA1 interrupt on negative edge

	lda #%11111111	;;; Output on all pins of PORT B
	sta DDRB

	lda #%11100000	;;; Output on the 3 most significant pins of PORT A
	sta DDRA

	lda #%00111000	;;; Use 8-Bit mode, 2-Line display and the 5x8 font
	jsr send_instruction

	lda #%00001110	;;; Display on; Cursor on; Blinking off
	jsr send_instruction

	lda #%00000110	;;; Increment address; Don't shift display
	jsr send_instruction

	lda #%00000001	;;; Clear display
	jsr send_instruction

	stz counter
	stz counter + 1


loop:
	lda #%00000010	;;; Return cursor to home
	jsr send_instruction

	stz message

	;;; Initialize value to be the number
	sei		;;; Set interrupt disable bit to prevent incorrect loading of the counter
	lda counter
	sta value
	lda counter + 1
	sta value + 1
	cli		;;; clear interrupt disable bit

divide:
	;;; Initialize the remainder to 0
	stz mod10
	stz mod10 + 1
	clc

	ldx #16
divloop:
	rol value
	rol value + 1
	rol mod10
	rol mod10 + 1

	;;; a,y = dividend - divisor
	sec
	lda mod10
	sbc #10
	tay		;;; Save low byte in Y
	lda mod10 + 1
	sbc #0
	bcc ignore_result	;;; branch if dividend < divisor

	sty mod10
	sta mod10 + 1

ignore_result:
	dex
	bne divloop

	rol value	;;; rotate in last bit of result
	rol value + 1

	lda mod10
	clc
	adc #"0"	;;; turn digit into character
	jsr push_char	;;; add char to string

	lda value
	ora value + 1
	bne divide	;;; repeat if result is not zero

	ldx #$0		;;; Set loop counter to 0
write:
	lda message,X	;;; Load string, use X as offset
	beq loop
	jsr write_char
	inx
	jmp write

;;; Add the character in the A register to the beginning of the null-terminated string `message`
push_char:
	pha
	ldy #0

char_loop:
	lda message,Y	;;; Get current char of the string
	tax
	pla
	sta message,Y	;;; Pull char of stack and add to string
	iny
	txa
	pha		;;; Push char from string onto stack
	bne char_loop

	pla
	sta message,Y	;;; Put null terminater back into the string
	rts

send_instruction:
	jsr wait_while_busy
	sta PORTB
	lda #$0		;;; Clear RS/RW/E bits
	sta PORTA
	lda #E		;;; Send instruction by setting E bit
	sta PORTA
	lda #$0		;;; Clear RS/RW/E bits
	sta PORTA
	rts

write_char:		;;; Write char in register A to the display
	jsr wait_while_busy
	sta PORTB
	lda #RS		;;; Set RS; Clear RW/E bits
	sta PORTA
	lda #(RS | E)	;;; Send instruction by setting E bit
	sta PORTA
	lda #RS		;;; Clear RS/RW/E bits
	sta PORTA
	rts

wait_while_busy:
	pha
	lda #%00000000	;;; Read on all pins of PORT B
	sta DDRB

	lda #RW
	sta PORTA
	lda #(RW | E)
	sta PORTA
while_busy:
	lda PORTB
	bmi while_busy

	lda #RW
	sta PORTA
	lda #%11111111	;;; Output on all pins of PORT B
	sta DDRB
	pla
	rts

nmi:
	rti

irq:
	pha
	lda IFR
	and #CA1		;;; is this a timer interrupt or CA1 interrupt?
	bne irq_ca1
irq_timer:
	lda #%11000000
	jsr send_instruction
	lda #"I"
	jsr write_char
	lda #"N"
	jsr write_char
	lda #"T"
	jsr write_char

	lda #TIMER1		;;; Disable Timer1 interrupt
	sta IER
	bit T1CL		;;; Read T1C-L to reset Timer1 bit in IFR
	lda #($80 | CA1)	;;; Reenable CA1 interrupt
	sta IER
	jmp irq_exit
irq_ca1:
	inc counter
	bne irq_ca1_exit
	inc counter + 1
irq_ca1_exit:
	lda #($80 | TIMER1)	;;; Enable Timer1 interrupt
	sta IER
	lda #CA1		;;; Disable CA1 interrupt
	sta IER
	bit PORTA		;;; Read PORTA to reset CA1 bit in IFR
	lda #$ff		;;; Set Timer1 to 0xffff
	sta T1CL
	lda #$ff
	sta T1CH
irq_exit:
	pla
	rti

	.org $fffa
	.word nmi
	.word reset
	.word irq

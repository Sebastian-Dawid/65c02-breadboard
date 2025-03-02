PORTA	= $6001
PORTB	= $6000
DDRA	= $6003
DDRB	= $6002

E	= %10000000
RW	= %01000000
RS	= %00100000

	.org $8000
reset:
	ldx #$ff
	txs

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

	ldx #$0		;;; Set loop counter to 0
loop:
	lda str,X	;;; Load string, use X as offset
	cmp #$0
	beq halt
	jsr write_char
	inx
	jmp loop
halt:
	jmp halt	;;; This is the end of the programm

send_instruction:
	sta PORTB
	lda #$0		;;; Clear RS/RW/E bits
	sta PORTA
	lda #E		;;; Send instruction by setting E bit
	sta PORTA
	lda #$0		;;; Clear RS/RW/E bits
	sta PORTA
	rts

write_char:		;;; Write char in register A to the display
	sta PORTB
	lda #RS		;;; Set RS; Clear RW/E bits
	sta PORTA
	lda #(RS | E)	;;; Send instruction by setting E bit
	sta PORTA
	lda #RS		;;; Clear RS/RW/E bits
	sta PORTA
	rts

	.org $ffe0
str:
	.asciiz "Hello, world!"

	.org $fffc
	.word reset
	.word $0000

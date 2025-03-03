
	.export _init, _exit
	.import _main

	.export __STARTUP__ : absolute = 1
	.import __RAM_START__, __RAM_SIZE__

	.import zerobss, copydata, initlib, donelib

	.include "zeropage.inc"

	.segment "VECTORS"

	.word $eaea
	.addr _init
	.word $eaea

	.segment "STARTUP"
_init:
	ldx #$ff
	txs
	cld

	lda #<(__RAM_START__ + __RAM_SIZE__)
	sta sp
	lda #>(__RAM_START__ + __RAM_SIZE__)
	sta sp+1

	jsr zerobss
	jsr copydata
	jsr initlib

	jsr _main

_exit:
	jsr donelib
	brk

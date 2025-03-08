	.import _stop
	.export _irq_int, _mni_int

	.segment "CODE"

	.PC02

_mni_int:
	rti

_irq_int:
	phx
	tsx
	pha
	inx		;;; set to address of saved status register
	inx
	lda $0100,X	;;; load status register contents
	and #$10	;;; check if brk bit is set
	bne break	;;; if A = 1; brk detected
	
irq:
	pla
	plx
	rti

break:
	jsr _stop

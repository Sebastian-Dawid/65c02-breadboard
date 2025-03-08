	.export _wait, _stop

	.segment "CODE"
	.PC02

;;;==========================================
;;;	 Wait for an iterrupt to happen.
.proc	_wait: near
	cli
	wai
	rts
.endproc

;;;==========================================
;;;	 Stop the processor.
.proc	_stop: near
	stp
.endproc

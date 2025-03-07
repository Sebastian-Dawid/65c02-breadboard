	.import _init
	.import _irq_int, _mni_int

	.segment "VECTORS"

	.addr _mni_int
	.addr _init
	.addr _irq_int

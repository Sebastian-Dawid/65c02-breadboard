SHELL := sh
.DEFAULT_GOAL := all
.PHONY: clean all

targets = blink.bin

asm_available := $(shell command -v ../vasm/vasm6502_oldstyle 2> /dev/null)

all: $(targets)

%.bin: %.s
ifndef asm_available
	echo $(asm_available)
	pushd ../vasm;\
	$(MAKE) CPU=6502 SYNTAX=oldstyle;\
	popd
endif
	../vasm/vasm6502_oldstyle -Fbin $< -o $@

clean:
	rm $(targets)

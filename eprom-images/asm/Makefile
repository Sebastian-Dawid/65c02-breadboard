SHELL := sh
.SUFFIXES:
.DEFAULT_GOAL := all
.PHONY: clean all

targets = blink.bin rotate.bin hello_world.bin print_num.bin counter.bin

asm_available := $(shell command -v ./vasm/vasm6502_oldstyle 2> /dev/null)

MINIPRO=minipro
EEPROM=AT28C256

all: $(targets)

%: %.bin
	@$(MINIPRO) -p $(EEPROM) -uP -w $<

%.bin: %.s
ifndef asm_available
	@curl -O http://sun.hasenbraten.de/vasm/release/vasm.tar.gz;\
	tar xf vasm.tar.gz;\
	rm vasm.tar.gz;\
	pushd ./vasm;\
	$(MAKE) CPU=6502 SYNTAX=oldstyle;\
	popd
endif
	./vasm/vasm6502_oldstyle -c02 -dotdir -Fbin $< -o $@

clean:
	rm $(targets)

# 65C02 Breadboard Computer
This repository contains software designed for use with a computer based on the 65C02 microprocessor.

This repository provides the following:
- `monitor`: Arduino sketch designed for monitoring the address and data bus of the processor.
- `eprom-images`: Code to generate images to program onto the AT28C256 EEPROM.
    - `eprom-images/asm`: Assembly based software.
    - `eprom-images/c`: C based software.

To be able to program the software onto the AT28C256 EEPROM using the provided `Makefile`s only `minipro` and `make` are needed.
Typing `make <prog_name>.bin` in either the `eprom-images/asm` or `eprom-images/c` directories will generate a binary
image of the program that can be programmed onto the EEPROM. `make <prog_name>` will try to immediately program the
binary onto the EEPROM. This requires that a `minipro` compatible EEPROM programmer (e.g. the T48) is connected and the
EEPROM is inserted. The `Makefile`s assume the EEPROM to be an AT28C256 by default, this can be changed by setting
`EEPROM` to the model you use.

For example, you can compile and program the C based hello world program like this:
```sh
$ cd eprom-images/c
$ make hello_world
```

## References
- [Ben Eater's 6502 series](https://eater.net/6502)
- [vasm - Assembler with 6502 asm support](http://sun.hasenbraten.de/vasm/)
- [cc65 - 6502 C compiler](https://github.com/cc65/cc65)

SHELL := sh
.SUFFIXES:
.PHONY: clean all

BUILD_DIR=build

CC65=./cc65/bin/cc65
CA65=./cc65/bin/ca65
AR65=./cc65/bin/ar65
LD65=./cc65/bin/ld65

MINIPRO=minipro
EEPROM=AT28C256

FIRMWARE_CFG=firmware.cfg
CPU=65sc02

TARGETS = hello_world.bin

ALLOCATORS = allocators/page_allocator.c
LCD = lcd/lcd.c

COMMON = common/interrupt.s common/vector.s common/wait.s

all: $(TARGETS)

$(BUILD_DIR)/common.lib: $(BUILD_DIR)/common/crt0.o
	@mkdir -p $(dir $@)
	@cp ./cc65/lib/none.lib $(BUILD_DIR)/common.lib
	$(AR65) a $@ $<

$(BUILD_DIR)/common_c.lib: $(ALLOCATORS:%.c=$(BUILD_DIR)/%.o) $(LCD:%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/common/common.o
	@mkdir -p $(dir $@)
	$(AR65) a $@ $^

$(BUILD_DIR)/%.s: src/%.c
	@mkdir -p $(dir $@)
	$(CC65) -t none --cpu $(CPU) -Oi -r -I src -o $@ $<

$(BUILD_DIR)/%.o: src/%.s
	@mkdir -p $(dir $@)
	$(CA65) --cpu $(CPU) -o $@ $< 

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.s
	@mkdir -p $(dir $@)
	$(CA65) --cpu $(CPU) -o $@ $< 

%.bin: $(BUILD_DIR)/%.o $(BUILD_DIR)/common_c.lib $(COMMON:%.s=$(BUILD_DIR)/%.o) $(BUILD_DIR)/common.lib
	$(LD65) -C $(FIRMWARE_CFG) -o $@ $^

%: %.bin
	$(MINIPRO) -p $(EEPROM) -uP -w $<

clean:
	@rm -rf $(BUILD_DIR) $(TARGETS)

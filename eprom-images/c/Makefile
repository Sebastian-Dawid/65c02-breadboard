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

all: $(TARGETS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR);\
	cp ./cc65/lib/none.lib $(BUILD_DIR)/common.lib

$(BUILD_DIR)/common.lib: $(BUILD_DIR)/crt0.o $(BUILD_DIR)
	$(AR65) a $(BUILD_DIR)/common.lib $(BUILD_DIR)/crt0.o

$(BUILD_DIR)/%.s: %.c $(BUILD_DIR)
	$(CC65) -t none --cpu $(CPU) -Or -r -o $@ $<

$(BUILD_DIR)/%.o: %.s $(BUILD_DIR)
	$(CA65) --cpu $(CPU) -o $@ $< 

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.s $(BUILD_DIR)
	$(CA65) --cpu $(CPU) -o $@ $< 

%.bin: $(BUILD_DIR)/%.o $(BUILD_DIR)/common.lib
	$(LD65) -C $(FIRMWARE_CFG) -o $@ $^

%: %.bin
	$(MINIPRO) -p $(EEPROM) -uP -w $<

clean:
	@rm -rf $(BUILD_DIR) $(TARGETS)

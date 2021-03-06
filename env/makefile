
CEMU=-m32
CSTD=c11
LDEMU=-melf_i386


CCFLAGS = -std=$(CSTD) -I$(FROOT)/include -I$(FROOT)/systems -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-exceptions -fno-leading-underscore -fno-pic
CCFLAGS += -W -Wall -Wno-unused-parameter -Wno-type-limits -Wno-parentheses -Wno-unused-variable -Wno-maybe-uninitialized -Wno-return-local-addr -Wno-return-type -Wno-comment
TEMUFLAGS= -M pc-i440fx-2.8
TEMURUNCMD=-kernel $(FROOT)/DepthOS.elf
BINCROOT ?= /bin
FROOT ?=.
CC = $(BINCROOT)/i686-elf-gcc
ASC = $(BINCROOT)/i686-elf-as
LD = $(BINCROOT)/i686-elf-ld
TEMU=qemu-system-i386

# CSOURCES = $(FROOT)/main.c
# ASMSOURCES = $(FROOT)/bootloader.S

# CSOURCES += $(wildcard $(FROOT)/*/*.c)
# CSOURCES += $(wildcard $(FROOT)/*/*.cc)
# ASMSOURCES += $(wildcard $(FROOT)/*/*.S)
# ASMSOURCES += $(wildcard $(FROOT)/*/*.s)

CSOURCES += $(shell find $(FROOT) -name "*.c" -o -name "*.cc")
ASMSOURCES += $(shell find $(FROOT) -name "*.s" -o -name "*.S")

.PHONY: all clean

clean:
	@echo -- Removing cache files --
	rm -f ./*.o
	rm -f ./*.bin
	rm -f ./*.elf

build: $(CSOURCES) $(ASMSOURCES)
	@echo ------ Build ------
	$(CC) -g $(CEMU) $(CCFLAGS) -c  $(CSOURCES)

	@mkdir -p $(FROOT)/build

	@mv *.o $(FROOT)/build/

	$(CC) $(CEMU) -std=$(CSTD) -g -c $(ASMSOURCES)

	@mv *.o $(FROOT)/build/

	$(LD) $(LDEMU) -T$(FROOT)/env/linker-config.ld -o $(FROOT)/build/DepthOS.bin $(FROOT)/build/*.o --build-id=none

	@cp $(FROOT)/build/DepthOS.bin $(FROOT)/DepthOS.elf

test: $(FROOT)/DepthOS.elf
	$(TEMU) $(TEMUFLAGS) $(TEMURUNCMD)
all: build test

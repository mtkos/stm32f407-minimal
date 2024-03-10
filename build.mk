PREFIX = arm-none-eabi
OC = $(PREFIX)-objcopy
CC = $(PREFIX)-gcc
SZ = $(PREFIX)-size
READELF = $(PREFIX)-readelf
OBJDUMP = $(PREFIX)-objdump
NM = $(PREFIX)-nm

FLAGS = -Os -nostdlib -mcpu=cortex-m4 -ffreestanding -Wall -Wl,-Map,$(TARGET).map

all: $(TARGET).elf

$(TARGET).elf: $(SRC)
	$(CC) $(FLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $^ $@

clean:
	$(RM) *.elf
	$(RM) *.bin
	$(RM) *.map
	$(RM) *.dmp
	$(RM) *.html

bin: $(TARGET).bin

load: $(TARGET).bin
	dfu-util -a 0 -s 0x08000000:leave -D $^

edit:
	nano -l main.c

touch:
	touch $(SRC)

size: $(TARGET).elf
	$(SZ) --format=SysV $^

readelf: $(TARGET).elf
	$(READELF) $^ -a

objdump: $(TARGET).elf
	$(OBJDUMP) -D > $(TARGET).dmp $^

nm: $(TARGET).elf
	$(NM) $^

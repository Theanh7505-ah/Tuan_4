TARGET = Bai01_FreeRTOS

CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = cortex-m3

CFLAGS = -mcpu=$(CPU) \
         -mthumb \
         -O0 \
         -Wall \
         -ffreestanding \
         -fno-common \
         -I. \
         -I../FreeRTOS/include \
         -I../FreeRTOS/portable/GCC/ARM_CM3

LDFLAGS = -mcpu=$(CPU) \
          -mthumb \
          -nostartfiles \
          -T stm32f103c8.ld \
          -Wl,--gc-sections

SOURCES = main.c \
          ../FreeRTOS/tasks.c \
          ../FreeRTOS/list.c \
          ../FreeRTOS/queue.c \
          ../FreeRTOS/portable/GCC/ARM_CM3/port.c \
          ../FreeRTOS/portable/MemMang/heap_4.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET).bin

$(TARGET).elf: startup.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lgcc

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

startup.o: startup.s
	$(AS) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

size: $(TARGET).elf
	$(SIZE) $(TARGET).elf

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

clean:
	rm -f *.o *.elf *.bin
	rm -f ../FreeRTOS/*.o
	rm -f ../FreeRTOS/portable/GCC/ARM_CM3/*.o
	rm -f ../FreeRTOS/portable/MemMang/*.o

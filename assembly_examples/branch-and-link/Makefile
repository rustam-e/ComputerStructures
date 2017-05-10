TOOLROOT=/l/arm/codesourcery/bin

CC=$(TOOLROOT)/arm-none-eabi-gcc
CFLAGS = -O1 -mcpu=cortex-m3 -mthumb


all: test.s

test.s: test.c
	$(CC) $(CFLAGS) -S $< -o $@
CC=c99
CFLAGS= -Wall -Wextra -pedantic -O0 -g -lm -Wno-unused-variable -Wno-unused-parameter
NASM=nasm
NASMFLAGS=-f elf64 -g -F DWARF

all: main tester

main: main.c string_processor_c.o string_processor_asm.o
	$(CC) $(CFLAGS) $^ -o $@

tester: tester.c string_processor_c.o string_processor_asm.o
	$(CC) $(CFLAGS) $^ -o $@

string_processor_c.o: string_processor.c
	$(CC) $(CFLAGS) -c $< -o $@

string_processor_asm.o: string_processor.asm
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f main tester
	rm -f salida.caso.*


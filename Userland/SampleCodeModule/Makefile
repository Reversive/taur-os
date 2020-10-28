include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)

all: $(MODULE)

u_libasm.o: u_libasm.asm
			$(ASM) -f elf64 u_libasm.asm


$(MODULE): $(SOURCES) u_libasm.o
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) u_libasm.o -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print

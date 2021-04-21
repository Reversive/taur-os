include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

SOURCES_SYS=$(wildcard sys/*.c)
OBJECTS_SYS=$(SOURCES_SYS:.c=.o)

SOURCES_CPU=$(wildcard cpu/*.c)
OBJECTS_CPU=$(SOURCES_CPU:.c=.o)

SOURCES_MEM=$(wildcard mem/*.c)
OBJECTS_MEM=$(SOURCES_MEM:.c=.o)

SOURCES_TASK=$(wildcard task/*.c)
OBJECTS_TASK=$(SOURCES_TASK:.c=.o)

SOURCES_DISPATCHER=$(wildcard dispatcher/*.c)
OBJECTS_DISPATCHER=$(SOURCES_DISPATCHER:.c=.o)

SOURCES_DRIVERS=$(wildcard drivers/keyboard/*.c drivers/video/*.c drivers/shell/*.c drivers/timer/*.c)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)

SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_SYS) $(OBJECTS_MEM) $(OBJECTS_DRIVERS) $(OBJECTS_CPU) $(OBJECTS_TASK) $(OBJECTS_DISPATCHER)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_SYS) $(OBJECTS_MEM) $(OBJECTS_DRIVERS) $(OBJECTS_CPU) $(OBJECTS_TASK) $(OBJECTS_DISPATCHER) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

mem:
	cd mem; make all;
clean:
	rm -rf asm/*.o
	rm -rf task/*.o
	rm -rf dispatcher/*.o 
	rm -rf sys/*.o 
	rm -rf mem/*.o 
	rm -rf drivers/keyboard/*.o drivers/video/*.o drivers/shell/*.o drivers/timer/*.o 
	rm -rf cpu/*.o *.o *.bin
.PHONY: all clean

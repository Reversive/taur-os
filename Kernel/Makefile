include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

SOURCES_SYS=$(wildcard sys/*.c)
OBJECTS_SYS=$(SOURCES_SYS:.c=.o)

SOURCES_CPU=$(wildcard cpu/*.c)
OBJECTS_CPU=$(SOURCES_CPU:.c=.o)

SOURCES_DRIVERS=$(wildcard drivers/keyboard/*.c drivers/video/*.c drivers/shell/*.c drivers/timer/*.c)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)

SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

SOURCES_MEM=$(wildcard memory/*.c)
OBJECTS_MEM=$(SOURCES_MEM:.c=.o)

SOURCES_PROCESS=$(wildcard process/*.c)
OBJECTS_PROCESS=$(SOURCES_PROCESS:.c=.o)

LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_SYS) $(OBJECTS_DRIVERS) $(OBJECTS_CPU) $(OBJECTS_MEM) $(OBJECTS_PROCESS)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_SYS) $(OBJECTS_DRIVERS) $(OBJECTS_CPU) $(OBJECTS_MEM) $(OBJECTS_PROCESS) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin
	rm -rf sys/*.o
	rm -rf process/*.o
	rm -rf memory/*.o
	rm -rf drivers/keyboard/*.o drivers/video/*.o drivers/shell/*.o drivers/timer/*.o
	rm -rf cpu/*.o
.PHONY: all clean

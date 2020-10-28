#include "include/exceptions.h"

const char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Corprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault Exception",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};


void exceptionDispatcher(int exception, uint64_t * rip, uint64_t * rsp) {
	switch (exception) {
		case ZERO_EXCEPTION_ID:
			kernel_panic(rip, rsp, ZERO_EXCEPTION_ID, exception_messages[ZERO_EXCEPTION_ID], 0x1);
			break;
		case INVALID_OPCODE_EXCEPTION_ID:
			kernel_panic(rip, rsp, INVALID_OPCODE_EXCEPTION_ID, exception_messages[INVALID_OPCODE_EXCEPTION_ID], 0x1);
			break;
	}
}

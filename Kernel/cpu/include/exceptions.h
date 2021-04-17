#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define NULL ((void *)0)
#define ZERO_EXCEPTION_ID 0x0
#define INVALID_OPCODE_EXCEPTION_ID 0x6
#define DELEGATE_BEHAVIOR 1
#include <kernel.h>
#include "../../asm/include/interrupts.h"
typedef uint64_t exception(uint64_t * rip, uint64_t * rsp, uint64_t * top);
enum exception_numbers {
    _EXCEPTION_DIV_BY_ZERO = 0,
	_EXCEPTION_DEBUG,
    _EXCEPTION_NON_MASKABLE_INTERRUPT,
    _EXCEPTION_BREAKPOINT,
    _EXCEPTION_OVERFLOW,
    _EXCEPTION_OUT_OF_BOUNDS,
    _EXCEPTION_INVALID_OPCODE
};

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

#define _EXCEPTIONS_LAST _EXCEPTION_INVALID_OPCODE
#define _EXCEPTIONS_SIZE (_EXCEPTIONS_LAST + 1)

exception ex_div_by_zero;
exception ex_invalid_opcode;

extern exception * exception_table[_EXCEPTIONS_SIZE];
void exceptionDispatcher(int exception, uint64_t * rip, uint64_t * rsp, uint64_t * top);


#endif
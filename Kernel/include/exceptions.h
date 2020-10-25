#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define ZERO_EXCEPTION_ID 0x0
#define INVALID_OPCODE_EXCEPTION_ID 0x6
#include <lib.h>


void exceptionDispatcher(int exception, uint64_t * rip, uint64_t * rsp);


#endif
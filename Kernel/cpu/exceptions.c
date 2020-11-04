#include "include/exceptions.h"



exception * exceptions_table[_EXCEPTIONS_SIZE] = {
	[_EXCEPTION_DIV_BY_ZERO] = ex_div_by_zero,
	[_EXCEPTION_DEBUG] = NULL,
    [_EXCEPTION_NON_MASKABLE_INTERRUPT] = NULL,
    [_EXCEPTION_BREAKPOINT] = NULL,
    [_EXCEPTION_OVERFLOW] = NULL,
    [_EXCEPTION_OUT_OF_BOUNDS] = NULL,
    [_EXCEPTION_INVALID_OPCODE] = ex_invalid_opcode
};

void exceptionDispatcher(int ex_id, uint64_t * rip, uint64_t * rsp, uint64_t * top) {
    uint64_t *_old_rip = rip;
    uint64_t *_old_rsp = rsp;
    if( ex_id < 0 || ex_id > _EXCEPTIONS_SIZE) return;
    exceptions_table[ex_id](_old_rip, _old_rsp, top);
    *rsp = (uint64_t)_b_rsp;
    *rip = (uint64_t)_b_rip;
    return;
}

uint64_t ex_div_by_zero(uint64_t * rip, uint64_t * rsp, uint64_t * top) {
    dump_reg(_EXCEPTION_DIV_BY_ZERO, exception_messages[_EXCEPTION_DIV_BY_ZERO], rip, rsp, top);
    return DELEGATE_BEHAVIOR;
}

uint64_t ex_invalid_opcode(uint64_t * rip, uint64_t * rsp, uint64_t * top) {
    dump_reg(_EXCEPTION_INVALID_OPCODE, exception_messages[_EXCEPTION_INVALID_OPCODE], rip, rsp, top);
    return DELEGATE_BEHAVIOR;
}

#include <lib.h>

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void clear_interrupts() {
	_cli();
}

void * memcpy(void * destination, const void * source, uint64_t length)
{

	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void halt_system() {
	_hlt();
}

void remask_pic() {
	picMasterMask(PIC_MASK);
}

void kernel_panic(uint64_t * rip, uint64_t * rsp, uint64_t * top, int id, const char * desc, bool halt) {
	/*ncNewline();
	ncPrint("[KERNEL PANIC]");
	ncNewline();
	ncPrint("[EXCEPTION ID]: ");
	ncPrintDec(id);
	ncNewline();
	ncPrint("[DESCRIPTION]: ");
	ncPrint(desc);
	dump_reg(rip, rsp, top);
	if(halt != 0) {
		clear_interrupts();
		remask_pic();
		halt_system();
	}*/
}

void dump_reg(int id, const char * desc, uint64_t * rip, uint64_t * rsp, uint64_t * top) {
	full_reg_snapshot * regs = (full_reg_snapshot *)top;
	_set_cursor_state(0);
	int bg_color_b = _get_bg_color();
	int text_color_b = _get_text_color();
	print_char('\n');
	_set_bg_color(0xFF0000);
	_set_text_color(0xFFFFFF);
	_internal_print_string("[EXCEPTION ID]: ");
	_internal_print_dec(id);
	print_char('\n');
	_internal_print_string("[DESCRIPTION]: ");
	_internal_print_string(desc);
	print_char('\n');
	_internal_print_string("[Instruction Pointer address]: ");
	_internal_print_hex(*rip);
	print_char('\n');
	_internal_print_string("[Registers]");
	print_char('\n');
	_internal_print_string("[RAX] = ");
	_internal_print_hex(regs->rax);
	_internal_print_string(" [RBX] = ");
	_internal_print_hex(regs->rbx);
	_internal_print_string(" [RCX] = ");
	_internal_print_hex(regs->rcx);
	print_char('\n');
	_internal_print_string("[RDX] = ");
	_internal_print_hex(regs->rdx);
	_internal_print_string(" [RDI] = ");
	_internal_print_hex(regs->rdi);
	_internal_print_string(" [RSI] = ");
	_internal_print_hex(regs->rsi);
	print_char('\n');
	_internal_print_string("[R8] = ");
	_internal_print_hex(regs->r8);
	_internal_print_string(" [R9] = ");
	_internal_print_hex(regs->r9);
	_internal_print_string(" [R10] = ");
	_internal_print_hex(regs->r10);
	_internal_print_string(" [R11] = ");
	_internal_print_hex(regs->r11);
	print_char('\n');
	_internal_print_string("[R12] = ");
	_internal_print_hex(regs->r12);
	_internal_print_string(" [R13] = ");
	_internal_print_hex(regs->r13);
	_internal_print_string(" [R14] = ");
	_internal_print_hex(regs->r14);
	_internal_print_string(" [R15] = ");
	_internal_print_hex(regs->r15);
	print_char('\n');
	_set_bg_color(bg_color_b);
	_set_text_color(text_color_b);
}

void get_registers(unsigned char *data){
	save_registers_data(data);
}

char get_char_data( char hexa_num) {
    return (hexa_num < 0xA) ? hexa_num + '0' : hexa_num + 'A' - 10;
}


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
	ncNewline();
	ncPrint("[EXCEPTION ID]: ");
	ncPrintDec(id);
	ncNewline();
	ncPrint("[DESCRIPTION]: ");
	ncPrint(desc);
	ncNewline();
	ncPrint("[Instruction Pointer address]: ");
	ncPrintHex(*rip);
	ncNewline();
	ncPrint("[Registers]");
	ncNewline();
	ncPrint("[RAX] = ");
	ncPrintHex(regs->rax);
	ncPrint(" [RBX] = ");
	ncPrintHex(regs->rbx);
	ncPrint(" [RCX] = ");
	ncPrintHex(regs->rcx);
	ncNewline();
	ncPrint("[RDX] = ");
	ncPrintHex(regs->rdx);
	ncPrint(" [RDI] = ");
	ncPrintHex(regs->rdi);
	ncPrint(" [RSI] = ");
	ncPrintHex(regs->rsi);
	ncNewline();
	ncPrint("[R8] = ");
	ncPrintHex(regs->r8);
	ncPrint(" [R9] = ");
	ncPrintHex(regs->r9);
	ncPrint(" [R10] = ");
	ncPrintHex(regs->r10);
	ncPrint(" [R11] = ");
	ncPrintHex(regs->r11);
	ncNewline();
	ncPrint("[R12] = ");
	ncPrintHex(regs->r12);
	ncPrint(" [R13] = ");
	ncPrintHex(regs->r13);
	ncPrint(" [R14] = ");
	ncPrintHex(regs->r14);
	ncPrint(" [R15] = ");
	ncPrintHex(regs->r15);
	ncNewline();
}

void get_registers(char *data){
	int i =test();
	//ncPrintDec(i);
	save_registers_data(data);

}



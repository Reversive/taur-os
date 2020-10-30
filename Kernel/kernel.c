#include "include/kernel.h"


uint64_t * _b_rsp;
uint64_t * _b_rip;
static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

uint64_t get_rsp_position(void) {
	return _rsp() - sizeof(uint64_t) * 4;
}

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main()
{	
	load_idt();

	_b_rip = sampleCodeModuleAddress;
	_b_rsp = get_rsp_position();
	//ncPrint("Return from useland syscall: ");
	//ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	//ncNewline();
	
	/*
	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();*/
	paint_character(300, 300, 'H', 2, 0x000000FF, 0xFFFFFFFF);
	paint_character(316, 300, 'O', 2, 0x000000FF, 0xFFFFFFFF);
	paint_character(332, 300, 'L', 2, 0x000000FF, 0xFFFFFFFF);
	paint_character(348, 300, 'A', 2, 0x000000FF, 0xFFFFFFFF);
	//ncPrint("[Finished]");
	while(1) {}
	return 0;
}

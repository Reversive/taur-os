#include "include/kernel.h"


uint64_t * _b_rsp;
uint64_t * _b_rip;
static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void *const systemVar = (void *)0x0000000000005A00;
typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8			
		- sizeof(uint64_t)			
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
	initialize_scheduler();
	_b_rip = sampleCodeModuleAddress;
	_b_rsp = (uint64_t *)(_rsp() - (sizeof(uint64_t) << 1));
	create_process("sh", sampleCodeModuleAddress, (char *[]){NULL}, MIN_PAGE_AMOUNT * PAGE_SIZE, 0);
	_sti();
	_idle();
	return 0;
}

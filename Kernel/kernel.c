// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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



uint8_t memcheck(void *start, uint8_t value, uint32_t size){
  uint8_t *p = (uint8_t *) start;
  uint32_t i;

  for (i = 0; i < size; i++, p++)
    if (*p != value)
      return 0;

  return 1;
}

#define MAX_BLOCKS 128
#define MAX_MEMORY 1024 //Should be around 80% of memory managed by the MM
#include "./mem/include/buddy.h"
#include "./mem/include/mm.h"

typedef struct MM_rq{
  void *address;
  uint32_t size;
}mm_rq;

static uint32_t m_z = 362436069;
static uint32_t m_w = 521288629;

uint32_t GetUint(){
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  return (m_z << 16) + m_w;
}


uint32_t GetUniform(uint32_t max){
  uint32_t u = GetUint();
  return (u + 1.0) * 2.328306435454494e-10 * max;
}

void test_mm(){
  mm_rq mm_rqs[MAX_BLOCKS];
  uint8_t rq;
  int32_t total;

  while (1){
    rq = 0;
    total = 0;

    // Request as many blocks as we can
    while(rq < MAX_BLOCKS && total < MAX_MEMORY){
      mm_rqs[rq].size = GetUniform(MAX_MEMORY - total - 1) + 1;;
      
      mm_rqs[rq].address = malloc(mm_rqs[rq].size); // TODO: Port this call as required
      if(mm_rqs[rq].address == 0) {
        _internal_print_string("malloc: NULL pointer returned\n");
        // exit(-1);
        break;
      }
      total += mm_rqs[rq].size;
      rq++;
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address != 0)
        memset(mm_rqs[i].address, i, mm_rqs[i].size); // TODO: Port this call as required

    // Check
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address != 0)
        if(!memcheck(mm_rqs[i].address, i, mm_rqs[i].size))
          _internal_print_string("memcheck: ERROR!\n"); // TODO: Port this call as required
	_internal_print_string("all ok\n");

    // Free
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address != 0)
        free(mm_rqs[i].address);  // TODO: Port this call as required
  } 
}

int main()
{	
	load_idt();
	test_mm();
	// initialize_scheduler();
	// _b_rip = sampleCodeModuleAddress;
	// _b_rsp = (uint64_t *)(_rsp() - (sizeof(uint64_t) << 1));
	
	// _internal_print_string("im gonna call samplecodemodule");
	// create_process("sh", sampleCodeModuleAddress, (char *[]){NULL}, MIN_PAGE_AMOUNT * PAGE_SIZE, 0);
	// _internal_print_string("created process\n");
	// _sti();
	// _internal_print_string("sti\n");
	// _idle();
	// _internal_print_string("idle\n");
	return 0;
}

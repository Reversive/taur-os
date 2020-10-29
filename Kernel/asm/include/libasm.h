#ifndef _LIB_ASM_H
#define _LIB_ASM_H
#include <stdint.h>


void _cli(void);
void _sti(void);
void _hlt(void);
uint64_t _rsp(void);

//Termina la ejecución de la cpu.
void haltcpu(void); 

void picMasterMask(uint8_t mask);
void picSlaveMask(uint8_t mask);
char _fetch_key(void);

#endif
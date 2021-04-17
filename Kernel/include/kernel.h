#ifndef _KERNEL_H
#define _KERNEL_H

#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include "../cpu/include/idt_loader.h"
#include "../drivers/video/include/video_driver.h"
#include "../drivers/shell/include/shell.h"
extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
extern uint64_t * _b_rip;
extern uint64_t * _b_rsp;

#endif
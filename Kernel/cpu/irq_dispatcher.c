// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "include/irq_dispatcher.h"

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case TIMER_TICK:
			timer_handler();
			break;
		case KEYBOARD:
			kb_trigger();
			break;
	}
	return;
}
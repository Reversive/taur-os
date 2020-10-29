
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
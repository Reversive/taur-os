 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include "../../cpu/include/idt_loader.h"
#include <stdint.h>
void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);

void _sys80handler(void);
void _exception0Handler(void);
void _exception6Handler(void);


#endif /* INTERRUPS_H_ */

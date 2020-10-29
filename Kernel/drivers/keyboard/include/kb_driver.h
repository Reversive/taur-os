#ifndef _KB_DRIVER_H
#define _KB_DRIVER_H
#include "../../../asm/include/libasm.h"
#include "../../../include/naiveConsole.h"
#include "kb_scancodes.h"
typedef unsigned char key;
typedef unsigned char bool;
void kb_trigger(void);
typedef enum states { NONE, SHIFT, CTRL, ALT} state;
int is_letter(key current_key);

#endif
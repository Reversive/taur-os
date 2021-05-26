#ifndef _KB_DRIVER_H
#define _KB_DRIVER_H
#include "../../../asm/include/libasm.h"
#include "kb_scancodes.h"
typedef unsigned char key;
typedef unsigned char bool;

#define KB_BUFFER_OVERFLOW 256

#define KB_BUFFER_SIZE 255
typedef struct {
    int queue_pos;
    int dequeue_pos;
    int pending_read;
    key kb_buffer[KB_BUFFER_SIZE];
} ring;


void kb_trigger(void);
typedef enum { NONE, SHIFT, CTRL, ALT, CAPS} states;
int is_letter(key current_key);
void queue(key current_key);
key getchar();
void backup_kb_buffer();
int restore_kb_buffer();
void clean_kb_buffer();
#endif
#ifndef _SHELL_H
#define _SHELL_H
#include "../../video/include/video_driver.h"
#include "../../../include/time.h"
void print_char(unsigned char key);
void _enable_cursor();
void _disable_cursor();
enum common_keys {
    _NEWLINE = '\n',
    _BACKSPACE = '\b'
};

#endif
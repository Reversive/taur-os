#include "../include/stdio.h"

unsigned int getchar(void) {
    char c;
    if(sys_read(STDIN, &c, 1) == 0) return EOF;
    return (unsigned int)c;
}
#include "../include/stdio.h"

unsigned int getchar(void) {
    char c;
    if(sys_read(_FD_STD_IN, &c, 1) == 0) return EOF;
    return (unsigned int)c;
}

unsigned int putchar(char c) {
    if( sys_write(_FD_STD_OUT, &c, 1) == 1 )
        return 1;
    return EOF;
}

int puts(const char *str) {
	for(int i = 0; str[i] != '\0'; i++) {
		if( putchar( str[i] ) == -1 )
            return EOF;
	}
    return 1;
}
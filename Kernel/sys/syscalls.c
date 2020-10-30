#include "include/syscalls.h"


int read(unsigned int fd, char * buffer, size_t count) {
    unsigned int bytes_read = 0;
    char popped_key;
    for( bytes_read = 0; bytes_read < count && (popped_key = getchar()) != -1; bytes_read++) {
        buffer[bytes_read] = popped_key;
    }
    return bytes_read;
}
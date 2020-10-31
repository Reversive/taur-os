#include "include/syscalls.h"


int read(unsigned int fd, char * buffer, size_t count) {
    unsigned int bytes_read = 0;
     char popped_key;
    switch (fd)
    {
        case _FD_STD_IN:
            for( bytes_read = 0; bytes_read < count && (popped_key = getchar()) != -1; bytes_read++ )
                buffer[bytes_read] = popped_key;
            break;
    }
    
    return bytes_read;
}


int write(unsigned int fd, char * buffer, size_t count) {
    unsigned int bytes_written = 0;
    switch (fd)
    {
        case _FD_STD_OUT:
            for(bytes_written = 0; bytes_written < count; bytes_written++)
                print_char(buffer[bytes_written]);
            break;

        case _FD_STD_ERR:
            break;
    }
    
    return bytes_written;
}
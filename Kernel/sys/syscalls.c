#include "include/syscalls.h"
#include "../include/lib.h"


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

void copy_mem(char * from, char * buffer) {
	int _byte_idx;
	unsigned char aux;

	for(_byte_idx = 0; _byte_idx < 32; _byte_idx++) {
		//Por cada byte leo 2 valores hexa
		aux = from[_byte_idx] & 0xF0;// & 1111 0000
		aux = aux >> 4;
		buffer[_byte_idx * 2] = get_char_data(aux);
		aux = from[_byte_idx] & 0x0F;// & 0000 1111
		buffer[_byte_idx * 2 + 1] = get_char_data(aux);
	}
	buffer[_byte_idx * 2] = 0;
}

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

void copy_mem(char * from, char * buffer) {
	int iByte;
	unsigned char aux;

	for(iByte = 0; iByte < 32; iByte++) {
		//Por cada byte leo 2 valores hexa
		aux = from[iByte] & 0xF0;// & 1111 0000
		aux = aux >> 4;
		buffer[iByte * 2] = get_char_data(aux);
		aux = from[iByte] & 0x0F;// & 0000 1111
		buffer[iByte * 2 + 1] = get_char_data(aux);
	}
	buffer[iByte * 2] = 0;
}
char get_char_data( char hexaNum) {
    return (hexaNum < 0xA) ? hexaNum + '0' : hexaNum + 'A' - 10;
}
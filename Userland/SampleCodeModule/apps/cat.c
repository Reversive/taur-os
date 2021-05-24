#include "include/cat.h"
#include "stdio.h"

int cat(int argc, char *args[]) {
	int sizebuff=512;
	char * buff = sys_malloc(sizebuff);
    if (buff == NULL) {
        printf("Error: Malloc");
        return -1;
    }
	int cant = sys_read(STDIN, buff, sizebuff);
    int pos = cant - 1;
	printf("%s", buff);

    while (cant == sizebuff && buff[pos] != 0) {
        cant = sys_read(STDIN, buff, sizebuff);
	    printf("%s", buff);
        pos = cant - 1;
    }
    sys_free(buff);
	return 0;
}
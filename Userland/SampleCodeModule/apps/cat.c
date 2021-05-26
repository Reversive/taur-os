#include "include/cat.h"
#include "stdio.h"

int cat(int argc, char *args[]) {
	int sizebuff=512;
	char * buff = sys_malloc(sizebuff);
    if (buff == NULL) {
        printfd("Error: Malloc");
        return -1;
    }
	int cant = sys_read(fd_pipe[0], buff, sizebuff);
    int pos = cant - 1;
	printfd("%s", buff);

    while (cant == sizebuff && buff[pos] != 0) {
        cant = sys_read(fd_pipe[0], buff, sizebuff);
	    printfd("%s", buff);
        pos = cant - 1;
    }
    sys_free(buff);
    sys_sem_post("pipe");
	return 0;
}
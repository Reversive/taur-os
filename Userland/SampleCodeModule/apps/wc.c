#include "include/wc.h"


int wc(int argc, char **argv) {
	
	printf("im  wc\n");
	char c[2] = {0};
	int count = 1;
	printf("read from: %d", fd_pipe[0]);
	sys_pipe_open("pipe");
	sys_read(2, c, 2); // puse 2 paa probar nomas, tendria que ser fd_pipe[0]
	while( c[0]!= EOF){
		printf("%s\n",c[0]);
		if(c[0] == '\n'){
			count++;
			printf("im gonna print\n");
		}
		sys_read(2, c, 2); // same
	}	
	printfd("Cantidad de lineas: %d\n", count);
	sys_sem_post("pipe");
	return 0;
}
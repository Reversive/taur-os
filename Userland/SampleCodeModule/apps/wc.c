#include "include/wc.h"


int wc(int argc, char **argv) {
	
	//printf("im  wc\n");
	char c[] = {0, 0, 0};
	int count = 1;
	//printf("wc will read from: %d", fd_pipe[0]);

	sys_read(fd_pipe[0], c, 1); // puse 2 paa probar nomas, tendria que ser fd_pipe[0]

	while( c[0]!= 0){
		//printf("%s",c);
		if(c[0] == '\n'){
			count++;
			//printf("im gonna print\n");
		}
		sys_read(fd_pipe[0], c, 1); // same
	}	
	printfd("Cantidad de lineas: %d\n", count);
	sys_sem_post("pipe");
	return 0;
}
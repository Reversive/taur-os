#include "include/filter.h"

bool isVowel(char c) {
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U';
}

int filter(int argc, char **argv) {
	char c[] = {0,0,0};
	sys_read(fd_pipe[0], c, 1);
	while(c[0] !=0) {
		if(!isVowel(c[0])){
			printfd("%s", c);
		}
		sys_read(fd_pipe[0], c, 1);
	}
	sys_sem_post("pipe");
	return 0;
}
#include "include/filter.h"

bool isVowel(char c) {
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U';
}

int filter(int argc, char **argv) {
	char buf[128];
	while(sys_read(fd_pipe[0], buf, sizeof(buf))) {
		char out[128];
		int j = 0;
		for(int i = 0; i < sizeof(buf) && buf[i]; i++){
			char c = buf[i];
			if(!isVowel(c))
				out[j++] = c;
		}
		out[j] = 0;
		printfd("%s", out);
	}
	sys_sem_post("pipe");
	return 0;
}
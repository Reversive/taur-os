// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/filter.h"

bool isVowel(char c) {
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U';
}

int filter(int argc, char **argv) {
	char buff[1000]={0};
    
	int cant = sys_read(fd_pipe[0], buff, 1000);
    
    for(int i = 0; buff[i]!=0; i++){
        if(!isVowel(buff[i])){
            printfd("%c", buff[i]);
    	}
    }
    
    while ( cant==1000) {
        cant = sys_read(fd_pipe[0], buff, 1000);
	    for(int i = 0; buff[i]!=0; i++){
            if(!isVowel(buff[i]))
                printfd("%c", buff[i]);
        }       
        
    }
    sys_sem_post("pipe");
	return 0;
}
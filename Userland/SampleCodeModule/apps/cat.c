// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/cat.h"
#include "stdio.h"

int cat(int argc, char *args[]) {
/*    char c[] = {0,0};
    sys_read(fd_pipe[0], c, 1);
    while(c[0]!=0){
        printfd("%s", c);
        sys_read(fd_pipe[0], c, 1);
    }
    sys_sem_post("pipe");*/
int sizebuff=1000;
	char buff[1000]={0};
    
	int cant = sys_read(fd_pipe[0], buff, sizebuff);
    
    for(int i = 0; buff[i]!=0; i++){
        //if(buff[i] != '\n'){
            printfd("%c", buff[i]);
            
        //}
    }
    
    while ( cant==1000) {
        cant = sys_read(fd_pipe[0], buff, sizebuff);
	    for(int i = 0; buff[i]!=0; i++){
        //    if(buff[i] != '\n')
                printfd("%c", buff[i]);
        }       
        
    }
    sys_sem_post("pipe");
	return 0;
}
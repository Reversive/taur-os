
#include "include/test_pipe.h"
#define MAXTIMES 20

int pr1(int argc, char **argv) {
	char r[50];
	int fd = atoi(argv[0]);
	
	//sys_pipe_close(fd);
	for (size_t i = 0; i < MAXTIMES; i++)
    {
        sys_read(fd, r, 5);
		printf("Im process: %d this is what i read %s\n", sys_getpid() ,r);
        sys_write(fd, "Im pr1", 7);
    }
    
	return 0;
}
int pr2(int argc, char **argv) {
    char r[50];
	int fd = atoi(argv[0]);

    for (size_t i = 0; i < MAXTIMES; i++)
    {
        sys_read(fd, r, 5);
		printf("Im process: %d this is what i read %s\n", sys_getpid() ,r);
        sys_write(fd, "Im pr2", 7);
    }
    return 0;
}

char* params[] = {"9", NULL};
void test_pipe(){
    int fd1 = sys_pipe_open("p1");
    int fd2 = sys_pipe_open("p2");
    int fd3 = sys_pipe_open("p3");

    sys_write(fd1, "0", 2);
    sys_write(fd2, "1", 2);
    sys_write(fd3, "Hello, this is taur-os using pipes", 35);
    
    char * info = sys_pipes_info();
    printf("%s\n", info);
    sys_pipe_close(fd1);
    sys_pipe_close(fd2);

    params[0] = itoa(fd3, params[0], 10);
    execv("pipe_test", pr1, params, 1);
    execv("pipe_test", pr2, params, 1);
    
    
}

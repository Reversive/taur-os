/* sampleCodeModule.c */

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

#define SECONDS 0
#define MINUTES 2
#define HOURS 4
#define DAYS 6

extern unsigned int sys_get_time(char t);


int main() {
	return sys_get_time(MINUTES);
}
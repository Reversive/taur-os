/* sampleCodeModule.c */

#define SECONDS 0
#define MINUTES 2
#define HOURS 4
#define DAYS 6


unsigned int sys_get_time(char t);
void invalid_opcode_test(void);
void puts(const char * str);
static char conditional = 'a';
int main() {
	
	if(conditional == 'a') {
		conditional = 'b';
		int b = 5 / 0;
	} else if(conditional == 'b') {
		conditional = 'c';
		invalid_opcode_test();
	}

	puts("I reached here!");
	return 0;
}
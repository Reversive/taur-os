#include "include/wc.h"

int wc(int argc, char **argv) {
	int c;
	int count = 1;
	while((c = getchar()) != EOF)
		if(c == '\n')
			count++;
	printf("Cantidad de lineas: %d\n", count);
	return 0;
}
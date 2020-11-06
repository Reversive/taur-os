#include "../include/stdio.h"


unsigned int getchar(void) {
    char c;
    if(sys_read(_FD_STD_IN, &c, 1) == 0) return EOF;
    return (unsigned int)c;
}

unsigned int putchar( char c) {
    if( sys_write(_FD_STD_OUT, &c, 1) == 1 )
        return 1;
    return EOF;
}

int puts(const char *str) {
	for(int i = 0; str[i] != '\0'; i++) {
		if( putchar( str[i] ) == -1 )
            return EOF;
	}
    return 1;
}

unsigned int strlen(char * str){
    int i=0;
    while (str[i]!=0)
    {
        i++;
    }
    return i;
}

void print_string(char * str){
    sys_write(_FD_STD_OUT,str,strlen(str));
    return;
}

char *itoa(uint64_t value, char *buffer, uint32_t base) {
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    do {
        uint32_t reminder = value % base;
        *p++ = (reminder < 10) ? reminder + '0' : reminder + 'A' - 10;
        digits++;
    } while (value /= base);

   
    *p = 0;

    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return buffer;
}


int printf(char * fmt, ...) {

  va_list pa; 
  va_start(pa, fmt);
  char * format = fmt;

  char buffer[255];
	char* tmp;
	int zeroes = 0;

	while( *format != '\0' ) {

		if( *format != '%' ) {

			putchar(*format);

			format++;
			continue;
		}

		format++;

		zeroes = 0;
		while ('0' <= *format && *format <= '9') {
			zeroes = zeroes * 10 + (*format - '0');
			format++;
		}

		switch(*format) {
			case 'd':
			case 'X':
				tmp = itoa(va_arg(pa, int), buffer, (*format=='d') ? 10:16);
				zeroes -= strlen(tmp);
				while (zeroes > 0) {
					putchar('0');
					zeroes--;
				}
				puts(tmp);
				break;
			case 'c':
				putchar( va_arg(pa, int) );
				break;
			case 's':
				puts( va_arg(pa, char*) );
				break;
		}

		format++;

	}

	va_end(pa);
    return 0;
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int charToDigit(char c) {
	return c - '0';
}

static int scanNumber(char* source, int* dest, int* cantArgs) {
	int aux = 0;
	int counter1 = 0;
    int counter2 = 0;

	if(!isDigit(*source)) {
		while(!isDigit(*(source + counter1))) {
            counter1++;
        }
	}
	if(isDigit(*(source + counter1))) {
		(*cantArgs)++;
		while(isDigit(*(source + counter1))) {
            counter2++;
            counter1++;
		}
        for(int i = 0; i < counter2; i++) {
            aux = aux + (pow(10, i))*charToDigit(*(source + counter1 - i - 1));
        }
		*dest = aux;
	}
	return counter1;
}

static int scanString(char* source, char*dest, int* cantArgs) {
	int counter = 0;
	if((*source) == ' ' || (*source) == '\n') {
		while((*source++) == ' ' || (*source) == '\n') {
            counter++;
        }
	}
	if((*source) != '\0') {
		(*cantArgs)++;
	}
	while((*source) != ' ' && (*source) != '\0' && (*source) != '\n') {
		*dest = *source;
		dest++;
		source++;
		counter++;
	}
	(*dest) = '\0';
	return counter;
}

static int scanChar(char* source, char* dest, int* cantArgs) {
	if((*source) == ' ' || (*source) == '\n') {
		while((*source++) == ' ' || (*source) == '\n');
	}
	if((*source) == '\0' || (*source) == '\n') {
		return 0;
	}
	*dest = *source;
	(*cantArgs)++;
	return 1;
}

int vscanf(char *source, char *format, va_list pa) {
    int arg_count = 0;
    while ((*source) != '\0' && (*format) != '\0') {
        switch (*format) {
            case ' ':
                format++;
                break;
            case '%':
                format++;
                break;
            case 'd':
                source += scanNumber(source, va_arg(pa, int *), &arg_count);
                format++;
                break;
            case 'c':
                source += scanChar(source, va_arg(pa, char *), &arg_count);
                format++;
                break;
            case 's':
                source += scanString(source, va_arg(pa, char *), &arg_count);
                format++;
                break;
        }
    }
    return arg_count;
}

int sscanf(char *source, char *format, ...) {
    va_list pa;
    va_start(pa, format);
    int aux = vscanf(source, format, pa);
    va_end(pa);
    return aux;
}
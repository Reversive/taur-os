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

char * strcpy(char* destination, const char* source) {
    if (destination == 0)
        return 0;

    char *ptr = destination;
 
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
 
    return ptr;
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
    // Invertimo' 
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
				tmp = itoa(va_arg(pa, int), buffer, (*format=='d') ? 10 : 16);
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

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int char_to_dec(char c) {
	return c - '0';
}

static int scan_number(char* source, int* dest, int* arg_count) {
	int aux = 0;
	int counter1 = 0;
    int counter2 = 0;

	if(!is_digit(*source)) {
		while(!is_digit(*(source + counter1))) {
            counter1++;
        }
	}
	if(is_digit(*(source + counter1))) {
		(*arg_count)++;
		while(is_digit(*(source + counter1))) {
            counter2++;
            counter1++;
		}
        for(int i = 0; i < counter2; i++) {
            aux = aux + (pow(10, i))*char_to_dec(*(source + counter1 - i - 1));
        }
		*dest = aux;
	}
	return counter1;
}

static int scan_str(char* source, char*dest, int* arg_count) {
	int counter = 0;
	if((*source) == ' ' || (*source) == '\n') {
		while((*source++) == ' ' || (*source) == '\n') {
            counter++;
        }
	}
	if((*source) != '\0') {
		(*arg_count)++;
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

static int scan_char(char* source, char* dest, int* arg_count) {
	if((*source) == ' ' || (*source) == '\n') {
		while((*source++) == ' ' || (*source) == '\n');
	}
	if((*source) == '\0' || (*source) == '\n') {
		return 0;
	}
	*dest = *source;
	(*arg_count)++;
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
                source += scan_number(source, va_arg(pa, int *), &arg_count);
                format++;
                break;
            case 'c':
                source += scan_char(source, va_arg(pa, char *), &arg_count);
                format++;
                break;
            case 's':
                source += scan_str(source, va_arg(pa, char *), &arg_count);
                format++;
                break;
        }
    }
    return arg_count;
}

int scanf(char *source, char *format, ...) {
    va_list pa;
    va_start(pa, format);
    int aux = vscanf(source, format, pa);
    va_end(pa);
    return aux;
}

void hex_to_string(long num, char * buffer){
    if (num==0){
      buffer[0] = '0';
      return;
    }
    int i=0;
    int j=0;
    while(num > 0){
        buffer[i++] = get_char_data(num%16);
        num = num / 16 ;
    }
    char aux; 
    buffer[i--]=0;
     while(j<i){
        aux = buffer[i];
        buffer[i] = buffer[j];
        buffer[j]=aux;
        j++;
        i--;
    }
}
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/stdio.h"
#include "../include/print_mem.h"
int fd_pipe[2] = {1, 0};
//fd_pipe[0] =  0; // in
//fd_pipe[1] = 1; //out

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
char* strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

void print_string(char * str){
    sys_write(_FD_STD_OUT,str,strlen(str));
    return;
}

void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j) {
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

// https://www.techiedelight.com/implement-itoa-function-in-c/
char * itoa(uint64_t value, char* buffer, uint32_t base) {
	if (base < 2 || base > 32)
		return buffer;

	int n = value;
	if (value < 0) 
		n *= -1;

	int i = 0;
	while (n) {
		int r = n % base;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	if (i == 0)
		buffer[i++] = '0';

	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0';

	return reverse(buffer, 0, i - 1);
}
// long atoi(const char* S)
// {
//     long num = 0;
 
//     int i = 0;
 
//     // run till the end of the string is reached, or the
//     // current character is non-numeric
//     while (S[i] && (S[i] >= '0' && S[i] <= '9'))
//     {
//         num = num * 10 + (S[i] - '0');
//         i++;
//     }
 
//     return num;
// }

void align_string(char * str, char * buffer, int length) {
	
	int i, j = 0;
	for(i = 0; (i < length || length == 0) && str[i] != 0; i++) {
		buffer[i] = str[i];
	}

	if(i < length) {
		int dif = (length - i);
		for(j = 0; j < dif; j++)
			buffer[i + j] = ' ';
	}

	buffer[i + j] = '\0';
}
int printfd(char *fmt, ...){
    va_list pa;
    va_start(pa, fmt);
    char *format = fmt;

    char buffer[255];

    char string[255]; 
    int cur_char = 0;

    char *tmp;
    int zeroes = 0;

    while (*format != '\0') {
        if (*format != '%') {

            string[cur_char] = *format;
            cur_char++;
            format++;
            continue;
        }

        format++;

        zeroes = 0;
        while ('0' <= *format && *format <= '9') {
            zeroes = zeroes * 10 + (*format - '0');
            format++;
        }

        switch (*format) {
            case 'd':
            case 'X':
                tmp = itoa(va_arg(pa, int), buffer, (*format == 'd') ? 10 : 16);
                zeroes -= strlen(tmp);
                while (zeroes > 0) {
                    string[cur_char] = '0';
                    cur_char++;
                    zeroes--;
                }

                strcpy(&string[cur_char], tmp);
                cur_char += strlen(tmp);
                break;
            case 'c':
                string[cur_char] = va_arg(pa, int);
                cur_char++;
                break;
            case 's':
                cur_char += 0;
                tmp = va_arg(pa, char *);

                align_string(tmp, buffer, zeroes);

                strcpy(&string[cur_char], buffer);
                cur_char += strlen(buffer);

                break;
        }

        format++;
    }
    string[cur_char] = 0;
    sys_write(fd_pipe[1], string, strlen(string));

    va_end(pa);
    return 0;

}
int printf(char *fmt, ...) {
    va_list pa;
    va_start(pa, fmt);
    char *format = fmt;

    char buffer[255];

    char string[255]; 
    int cur_char = 0;

    char *tmp;
    int zeroes = 0;

    while (*format != '\0') {
        if (*format != '%') {

            string[cur_char] = *format;
            cur_char++;
            format++;
            continue;
        }

        format++;

        zeroes = 0;
        while ('0' <= *format && *format <= '9') {
            zeroes = zeroes * 10 + (*format - '0');
            format++;
        }

        switch (*format) {
            case 'd':
            case 'X':
                tmp = itoa(va_arg(pa, int), buffer, (*format == 'd') ? 10 : 16);
                zeroes -= strlen(tmp);
                while (zeroes > 0) {
                    string[cur_char] = '0';
                    cur_char++;
                    zeroes--;
                }

                strcpy(&string[cur_char], tmp);
                cur_char += strlen(tmp);
                break;
            case 'c':
                string[cur_char] = va_arg(pa, int);
                cur_char++;
                break;
            case 's':
                cur_char += 0;
                tmp = va_arg(pa, char *);

                align_string(tmp, buffer, zeroes);

                strcpy(&string[cur_char], buffer);
                cur_char += strlen(buffer);

                break;
        }

        format++;
    }

    string[cur_char] = 0;
    puts(string);

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
	int counter1 = 0;
	if(!is_digit(*source)) {
		while(!is_digit(*(source + counter1))) {
            if(*(source+counter1) == 0) { 
                break; 
            }
            counter1++;
        }
	}
	if(is_digit(*(source + counter1))) {
        int counter2 = 0;
		(*arg_count)++;
		while(is_digit(*(source + counter1))) {
            counter2++;
            counter1++;
		}
        int aux = 0;
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

// https://www.geeksforgeeks.org/write-your-own-atoi/
int atoi(char* str) { 
    int res = 0; 
    int sign = 1; 
    int i = 0; 
    if (str[0] == '-') { 
        sign = -1; 
        i++; 
    } 
    for (; str[i] != '\0'; ++i) 
        res = res * 10 + str[i] - '0'; 
    return sign * res; 
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
    
    buffer[i--]=0;
     while(j<i){
        char aux = buffer[i];
        buffer[i] = buffer[j];
        buffer[j]=aux;
        j++;
        i--;
    }
}

char * strchr (register const char *s, int c)
{
  do {
    if (*s == c)
      {
        return (char*)s;
      }
  } while (*s++);
  return (0);
}
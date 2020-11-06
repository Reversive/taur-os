#include "../include/math.h"

long long int pow(int base, int exp) {
    if( exp == 0 )
        return 1;

    int num = base;

    for(int i = 2; i <= exp; i++)
        num *= base;

    return num;

}
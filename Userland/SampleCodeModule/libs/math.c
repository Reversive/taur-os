// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/math.h"

long long int pow(int base, int exp) {
    if( exp == 0 )
        return 1;

    int num = base;

    for(int i = 2; i <= exp; i++)
        num *= base;

    return num;

}


unsigned int abs(int n) {
  if (n < 0)
    return n*-1;
  return n;
}
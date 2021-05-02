#ifndef SBRK_H
#define SBRK_H
#include <stdint.h>

/***************************************************************/
/*                      Declaraciones                          */
/***************************************************************/

//  sbrk_handler() increments the end of DataSeg and return the beginning of the allocked space 
void sbrk_handler(int increment, void ** buffer);

#endif
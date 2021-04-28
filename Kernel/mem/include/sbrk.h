// #ifndef SBRK_H
// #define SBRK_H
// #include <stdint.h>

// /***************************************************************/
// /*                      Declaraciones                          */
// /***************************************************************/

// //  sbrk_handler() increments the end of DataSeg and return the beginning of the allocked space 
// void sbrk_handler(int increment, void ** buffer);

// // It reserves memory until the address passed as a parameter
// int brk_handler( void * addr);

// //  It retrieves information about the state of the memory
// void mem_state(void ** top,void ** max,void ** currentTop);

// #endif
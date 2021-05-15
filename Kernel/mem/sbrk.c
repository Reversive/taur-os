// // This is a personal academic project. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/sbrk.h"
#include <stdlib.h>

/***************************************************************/
/*                        Variables                            */
/***************************************************************/
static void *const sampleDataModuleAddress = (void *)0x600000; 
static void *const maxAddress = (void *)0xF00000;             
void *topAddress = NULL;

/***************************************************************/
/*                   Funciones Publicas                        */
/***************************************************************/

void sbrk_handler(int increment, void **buffer)
{
        if (topAddress == NULL)
        {
                topAddress = sampleDataModuleAddress;
        }

        if ((topAddress + increment) <= maxAddress)
        {

                *buffer = topAddress;
                topAddress += increment;
        }
        else
        {
                *buffer = NULL;
        }
        return;
}
int brk_handler(void *addr)
{
        if (topAddress == NULL)
        {
                topAddress = sampleDataModuleAddress;
        }
        // No puede reservar mas memoria que la que tiene asignada el proceso, o
        // un valor menor al que tiene ya asignado
        if (addr > maxAddress || addr < topAddress)
        {
                return -1;
        }

        topAddress = addr;
        return 0;
}
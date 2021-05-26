// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// // This is a personal academic project. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "include/sbrk.h"

//---------------------------DECLARACION DE VARIABLES--------------------------------------//

static void *const sampleDataModuleAddress = (void *)0x600000; 
static void *const maxAddress = (void *)0xF00000;             
void *topAddress = NULL;

//-----------------------------------------------------------------------------------------//


void sbrkHandler(int increment, void **buffer)
{
        if (topAddress == NULL)
        {
                topAddress = sampleDataModuleAddress;
        }

        if ((topAddress + increment) <= maxAddress)
        {

                *buffer = topAddress;
                topAddress += increment;
        } else
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
        if (addr > maxAddress || addr < topAddress)     // Can't have more memory than the process
        {                                               // nor less than the already assigned value
                return -1;
        }

        topAddress = addr;
        return 0;
}
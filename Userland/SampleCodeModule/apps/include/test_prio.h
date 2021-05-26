#ifndef TEST_PRIO_H
#define TEST_PRIO_H
#include "../../include/stdio.h"
#include "../../include/unistd.h"
#include <stdint.h>
#include <stdio.h>
#include "../../include/basic_lib.h"

#define MINOR_WAIT 1000000                               // TODO: To prevent a process from flooding the screen
#define WAIT      100000000                           // TODO: Long enough to see theese processes beeing run at least twice
int main_test_prio(int argc, char **argv);
void bussy_wait(uint64_t n);
int prio_endless_loop(int argc, char **argv);
#endif
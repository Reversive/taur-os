#ifndef _TIME_H_
#define _TIME_H_
typedef void (*function)(void);
void timer_restart();
void timer_handler();
int timer_append_function(function f, unsigned long int ticks);
int timer_remove_function(function f);
#endif

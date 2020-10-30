#include "../include/time.h"

unsigned int get_day_seconds() {
    return sys_time(0x0);
}

unsigned int get_day_minutes() {
    return sys_time(0x2);
}

unsigned int get_day_hour() {
    return sys_time(0x4);
}

unsigned int get_day() {

}
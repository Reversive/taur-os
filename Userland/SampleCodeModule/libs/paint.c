// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/paint.h"

void draw_square(int x, int y, int size, int color) {
    sys_draw_rect(x, y, size, size, color);
}
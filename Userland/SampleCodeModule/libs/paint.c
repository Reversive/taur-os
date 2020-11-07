#include "../include/paint.h"

void draw_square(int x, int y, int size, int color) {
    sys_draw_rect(x, y, size, size, color);
}
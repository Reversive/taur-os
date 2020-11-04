#include "../include/chess_bitmap.h"


char bishop [256] = {
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
  '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
  '0','0','0','0','1','0','0','1','0','0','0','1','0','0','0','0',
  '0','0','0','0','1','0','0','0','1','0','0','1','0','0','0','0',
  '0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0',
  '0','0','0','0','0','1','1','1','1','1','1','0','0','0','0','0',
  '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
  '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
  '0','0','1','1','0','0','1','1','1','1','0','0','1','1','0','0',
  '0','1','0','1','1','1','0','1','1','0','1','1','1','0','1','0',
  '0','0','1','0','0','1','1','0','0','1','1','0','0','1','0','0',
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'
};

char horse [256] = {
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
  '0','0','0','1','1','0','0','1','0','0','0','0','0','0','0','0',
  '0','0','0','1','0','1','1','1','1','0','0','0','0','0','0','0',
  '0','0','0','0','1','0','0','0','0','1','0','0','0','0','0','0',
  '0','0','0','1','0','0','0','0','0','0','1','0','0','0','0','0',
  '0','0','0','1','0','1','0','0','0','0','0','1','0','0','0','0',
  '0','0','0','1','0','0','0','0','1','0','0','0','1','0','0','0',
  '0','0','1','0','0','0','0','0','1','0','0','0','1','0','0','0',
  '0','1','1','0','0','0','1','1','0','0','0','0','0','1','0','0',
  '0','1','0','0','0','1','0','1','0','0','0','0','0','1','0','0',
  '0','0','1','1','1','0','1','0','0','0','0','0','0','1','0','0',
  '0','0','0','0','0','1','0','0','0','0','0','0','0','1','0','0',
  '0','0','0','0','1','0','0','0','0','0','0','0','0','1','0','0',
  '0','0','0','0','1','1','1','1','1','1','1','1','1','1','0','0',
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'
};

char queen [256] = {
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0',
  '0','0','0','0','0','0','1','1','1','1','0','0','0','0','0','0',
  '0','1','1','0','0','0','1','1','1','1','0','0','0','1','1','0',
  '0','1','1','0','0','0','0','1','1','0','0','0','0','1','1','0',
  '0','0','1','1','0','0','0','1','1','0','0','0','1','1','0','0',
  '0','0','1','1','1','0','1','0','0','1','0','1','1','1','0','0',
  '0','0','0','1','1','1','0','0','0','0','1','1','1','0','0','0',
  '0','0','0','1','0','0','1','0','0','1','0','0','1','0','0','0',
  '0','0','0','0','1','0','0','1','1','0','0','1','0','0','0','0',
  '0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0',
  '0','0','0','1','1','0','0','0','0','0','0','1','1','0','0','0',
  '0','0','0','1','0','0','0','0','0','0','0','0','1','0','0','0',
  '0','0','1','0','0','0','0','0','0','0','0','0','0','1','0','0',
  '0','0','0','1','1','1','1','1','1','1','1','1','1','0','0','0',
  '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'
};

char pawn [256]={
    '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
    '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','0','1','0','0','1','0','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0',
    '0','0','0','1','0','0','0','0','0','0','0','0','1','0','0','0',
    '0','0','0','1','0','0','0','0','0','0','0','0','1','0','0','0',
    '0','0','0','1','0','0','0','0','0','0','0','0','1','0','0','0',
    '0','0','0','0','1','1','1','1','1','1','1','1','0','0','0','0',
    '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
};

char tower [256]={
    '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
    '0','0','0','1','1','0','0','1','1','0','0','1','1','0','0','0',
    '0','0','0','1','0','1','1','0','0','1','1','0','1','0','0','0',
    '0','0','0','1','0','0','0','0','0','0','0','0','1','0','0','0',
    '0','0','0','0','1','1','1','1','1','1','1','1','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','0','0','1','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','1','1','1','1','1','1','1','1','1','1','0','0','0',
    '0','0','1','0','0','0','0','0','0','0','0','0','0','1','0','0',
    '0','0','1','1','1','1','1','1','1','1','1','1','1','1','0','0',
    '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'
};

char king [256]={
    '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','1','1','1','0','0','0','0','0','0','0',
    '0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0',
    '0','0','0','1','1','0','1','0','1','0','1','1','0','0','0','0',
    '0','0','1','0','0','1','1','0','1','1','0','0','1','0','0','0',
    '0','1','0','0','0','0','0','1','0','0','0','0','0','1','0','0',
    '0','1','0','0','0','0','0','1','0','0','0','0','0','1','0','0',
    '0','0','1','0','0','1','1','1','1','1','0','0','1','0','0','0',
    '0','0','0','1','1','0','0','0','0','0','1','1','0','0','0','0',
    '0','0','0','0','0','1','1','1','1','1','0','0','0','0','0','0',
    '0','0','0','0','1','0','0','0','0','0','1','0','0','0','0','0',
    '0','0','0','1','0','0','0','0','0','0','0','1','0','0','0','0',
    '0','0','0','1','0','0','0','0','0','0','0','1','0','0','0','0',
    '0','0','0','0','1','1','1','1','1','1','1','0','0','0','0','0',
    '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'
};



void draw_bishop(int x, int y, int color) {
    sys_draw_matrix(x, y, color, bishop, 16);
}

void draw_queen(int x, int y, int color) {
    sys_draw_matrix(x, y, color, queen, 16);
}

void draw_horse(int x, int y, int color) {
    sys_draw_matrix(x, y, color, horse, 16);
}

void draw_king(int x, int y, int color) {
    sys_draw_matrix(x, y, color, king, 16);
}

void draw_tower(int x, int y, int color) {
    sys_draw_matrix(x, y, color, tower, 16);
}

void draw_pawn(int x, int y, int color) {
    sys_draw_matrix(x, y, color, pawn, 16);
}
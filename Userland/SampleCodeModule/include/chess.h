#ifndef _CHESS_H
#define _CHESS_H
#include "chess_bitmap.h"
#include "stdio.h"
#include "colors.h"
#include "../include/console.h"
#include "math.h"
#define MAX_PRINTABLE_MOVES 33

enum chess_state {NOT_PLAYING = 0, PLAYING, PAUSED,ENDED};
typedef enum {PAWN = 0, TOWER, HORSE, BISHOP, QUEEN, KING, EMPTY} chess_id;
typedef enum {IDLE = 0, MOVING, PASO} state;

struct movement{
    int x;
    int y;
};
typedef struct movement* movements;

typedef struct {
    chess_id piece_name;
    movements move;
    enum colors color;
    state piece_state;
} chess_piece;

typedef struct {
    int author;
    char text[5];
} chess_move;

extern int last_printable_index;
extern int first_printable_index;
extern int number_of_moves;
extern int b_cursor_x;
extern int b_cursor_y;
extern chess_piece printeable_chess_table[8][8];
void join_chess();
void print_chess_table( chess_piece chess_table[][8]);
void parse_move(char* buffer,int* x1,int* y1,int* x2,int* y2);
int check_movement(int x1,int y1,int x2,int y2);
void player_two_timer();
void player_one_timer();
void move_piece(char* buffer);
void rotation_chess_table();
void load_printeable_chess_table(chess_piece chess_table[8][8]);
void close_chess();
int win_codition(int black_king,int white_king);
void print_winner(int player_win);
void print_plays();

#endif

#include "../include/chess.h"

chess_piece chess_table[8][8];
int player_turn = 0;
int backup_x;
int backup_y;
void join_chess(){
  	sys_get_cursor_pos(&backup_x,&backup_y);
    sys_set_cursor_status(_DISABLED);
		sys_set_cursor_pos(0, 720);
		in_chess=1;
    struct movement n; n.x=0; n.y=1;
    struct movement s; s.x=0; s.y=-1;
    struct movement w; w.x=-1; w.y=0;
    struct movement e; e.x=1; e.y=0;
    struct movement ne; ne.x=1; ne.y=1;
    struct movement nw; nw.x=-1; nw.y=1;
    struct movement se; se.x=1; se.y=-1;
    struct movement sw; sw.x=-1; sw.y=-1;

    chess_piece pawn_white=  {PAWN,  0,WHITE,IDLE};
    chess_piece king_white=  {KING,  0,WHITE,IDLE};
    chess_piece tower_white= {TOWER, 0,WHITE,IDLE};
    chess_piece horse_white= {HORSE, 0,WHITE,IDLE};
    chess_piece queen_white= {QUEEN, 0,WHITE,IDLE};
    chess_piece bishop_white={BISHOP,0,WHITE,IDLE};

    chess_piece pawn_black=  {PAWN,  0,BLACK,IDLE};
    chess_piece king_black=  {KING,  0,BLACK,IDLE};
    chess_piece tower_black= {TOWER, 0,BLACK,IDLE};
    chess_piece horse_black= {HORSE, 0,BLACK,IDLE};
    chess_piece queen_black= {QUEEN, 0,BLACK,IDLE};
    chess_piece bishop_black={BISHOP,0,BLACK,IDLE};
    chess_piece empty={EMPTY,0,0,0};

    for (int i = 0; i < 8; i++){
        chess_table[1][i]=pawn_black;
        chess_table[2][i]=empty;
        chess_table[3][i]=empty;
        chess_table[4][i]=empty;
        chess_table[5][i]=empty;
        chess_table[6][i]=pawn_white;
    }
    chess_table[0][0]=tower_black;
    chess_table[7][0]=tower_white;
    chess_table[0][1]=horse_black;
    chess_table[7][1]=horse_white;
    chess_table[0][2]=bishop_black;
    chess_table[7][2]=bishop_white;
    chess_table[0][3]=queen_black;
    chess_table[7][3]=queen_white;
    chess_table[0][4]=king_black;
    chess_table[7][4]=king_white;
    chess_table[0][5]=bishop_black;
    chess_table[7][5]=bishop_white;
    chess_table[0][6]=horse_black;
    chess_table[7][6]=horse_white;
    chess_table[0][7]=tower_black;
    chess_table[7][7]=tower_white;

    sys_clear_screen();

    sys_draw_character(650, 20, '8', 3, 0xFFFFFF);
	  sys_draw_character(650, 100, '7', 3, 0xFFFFFF);
	  sys_draw_character(650, 180, '6', 3, 0xFFFFFF);
	  sys_draw_character(650, 260, '5', 3, 0xFFFFFF);
	  sys_draw_character(650, 340, '4', 3, 0xFFFFFF);
	  sys_draw_character(650, 420, '3', 3, 0xFFFFFF);
	  sys_draw_character(650, 500, '2', 3, 0xFFFFFF);
	  sys_draw_character(650, 580, '1', 3, 0xFFFFFF);
	  sys_draw_character(20, 650, 'A', 3, 0xFFFFFF);
	  sys_draw_character(100, 650, 'B', 3, 0xFFFFFF);
	  sys_draw_character(180, 650, 'C', 3, 0xFFFFFF);
	  sys_draw_character(260, 650, 'D', 3, 0xFFFFFF);
	  sys_draw_character(340, 650, 'E', 3, 0xFFFFFF);
	  sys_draw_character(420, 650, 'F', 3, 0xFFFFFF);
	  sys_draw_character(500, 650, 'G', 3, 0xFFFFFF);
	  sys_draw_character(580, 650, 'H', 3, 0xFFFFFF);
	  
    //sys_register_timertick_function(player_one_timer, 18);
    
    print_chess_table(chess_table);
    sys_set_cursor_pos(0, 720);
    sys_set_cursor_status(_ENABLED);


	

}


void print_chess_table( chess_piece chess_table[][8]){

    for(int j = 0; j < 8; j+=2){
    		for(int i = 0; i < 8; i+=2) {
    			sys_draw_square(i*80, j * 80, 80, 0xb3a076);
    			sys_draw_square((i+1)*80, j * 80, 80, 0xdfdfd3);
    		}
    		for(int i = 0; i < 8; i+=2) {
    			sys_draw_square(i*80, (j+1) * 80, 80, 0xdfdfd3);
    			sys_draw_square((i+1)*80, (j+1) * 80, 80, 0xb3a076);
    		}
    	}
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            int color=chess_table[i][j].color;
            switch (chess_table[i][j].piece_name){
                case EMPTY:
                    break;
                case PAWN:
                    draw_pawn(j*80,i*80,color);
                    break;
                case TOWER:
                    draw_tower(j*80,i*80,color);
                    break;
                case HORSE:
                    draw_horse(j*80,i*80,color);
                    break;
                case BISHOP:
                    draw_bishop(j*80,i*80,color);
                    break;
                case QUEEN:
                    draw_queen(j*80,i*80,color);
                    break;
                case KING:
                    draw_king(j*80,i*80,color);
                    break;
            }

        }

    }

}

void move_chess_piece(int x1,int y1,int x2,int y2){
    chess_piece empty={EMPTY,0,0,0};
    chess_table[y2][x2]=chess_table[y1][x1];
    chess_table[y1][x1]=empty;
    print_chess_table(chess_table);
}

void parse_move(char* buffer,int* x1,int* y1,int* x2,int* y2){
    int index=0;
    while(*buffer == ' ')
        buffer++;
    while(*buffer != ' ')
		buffer++;
    while (*buffer!=0){
        char c =*buffer;
        if(c==' '){
            buffer++;
            continue;
        }
        if (c>='A' && c<='H'){
            if(index==0)
                *x1=c-'A';
            if(index==2)
                *x2=c-'A';
        }else if(c>='1' && c<='8'){
            if(index==1)
                *y1='8'-c;
            if(index==3)
                *y2='8'-c;
        }
        index++;
        buffer++;
    }
}

int current_player_one_seconds = 300;
int current_player_two_seconds = 300;
void player_one_timer() {
	print_string_by_pos(700, 500, itoa(current_player_one_seconds, 10), 0xFFFFFF, 2);
	current_player_one_seconds -= 1;
}

void player_two_timer() {
	print_string_by_pos(800, 500, itoa(current_player_two_seconds, 10), 0xFF0000, 2);
	current_player_two_seconds -= 1;
}

int check_movement(int x1,int y1,int x2,int y2){
  int aux1 = x1-x2;
  int aux2 = y1-y2;
  switch (chess_table[y1][x1].piece_name) {
    case EMPTY:
      return 0;
    case PAWN:
      switch (chess_table[y1][x1].color) {
        case WHITE:
          if (x2 == x1 && y2 == y1-1){
            if (chess_table[y2][x2].piece_name == EMPTY)
              return 1; // Base movement
          } else if ((x2 == x1-1 || x2 == x1+1) && y2 == y1-1 && chess_table[y2][x2].piece_name != EMPTY && chess_table[y2][x2].color != WHITE){
            return 1; // Take enemy piece
          }
          else
            return 0;
      }
      return 0;
    case TOWER:
      switch (chess_table[y1][x1].color) {
        case WHITE:
          if (x1==x2 && y1 != y2){ // Y movement
            if (y1 - y2 > 0){
              for (int i = y1-1; i>y2; i--){
                if (chess_table[i][x2].piece_name != EMPTY)
                  return 0;
              }
              if (chess_table[y2][x2].color != WHITE)
                return 1; // Base movement -> DOWN
            } else {
              for (int i = y1+1; i<y2; i++){
                if (chess_table[i][x2].piece_name != EMPTY)
                  return 0;
              }
              if (chess_table[y2][x2].color != WHITE)
                return 1; // Base movement -> UP
            }

          } else if (y1==y2 && x1 != x2){ // X movement
            if (x1 - x2 > 0){
              for (int i = x1-1; i>x2; i--){
                if (chess_table[y2][i].piece_name != EMPTY)
                  return 0;
              }
              if (chess_table[y2][x2].color != WHITE)
                return 1; // Base movement -> RIGHT

            } else {
              for (int i = x1+1; i<x2; i++){
                if (chess_table[y2][i].piece_name != EMPTY)
                  return 0;
              }
              if (chess_table[y2][x2].color != WHITE)
                return 1; // Base movement -> LEFT
            }
          }
          else
            return 0;
      }
    case HORSE:
      return 0;
    case BISHOP:
      switch (chess_table[y1][x1].color) {
        case WHITE:
          if (aux1 > 0 && aux2 > 0){
            // TOP-LEFT
            for (int i = x1-1, j = y1-1; i>x2; i--, j--){
              if (chess_table[j][i].piece_name != EMPTY)
                return 0;
            }
          } else if (aux1 < 0 && aux2 > 0){
            // TOP-RIGHT
            for (int i = x1+1, j = y1-1; j>y2; i++, j--){
              if (chess_table[j][i].piece_name != EMPTY)
                return 0;
            }
          } else if (aux1 > 0 && aux2 < 0){
            // BOTTOM-LEFT
            for (int i = x1-1, j = y1+1; j<y2; i--, j++){
              if (chess_table[j][i].piece_name != EMPTY)
                return 0;
            }
          } else if (aux1 < 0 && aux2 < 0){
            // BOTTOM-RIGHT
            for (int i = x1+1, j = y1+1; i<x2; i++, j++){
              if (chess_table[j][i].piece_name != EMPTY)
                return 0;
            }
          } else {
            return 0;
          }
          if (chess_table[y2][x2].color != WHITE)
            return 1;
        return 0;
      }
      return 0;
    case QUEEN:
      return 0;
    case KING:
      switch (chess_table[y1][x1].color) {
        case WHITE:
          if (aux1 < 0)
            aux1 = aux1 * -1;
          if (aux2 < 0)
            aux2 = aux2 * -1;
          if (aux1 > 1 || aux2 > 1 || (aux1==0 && aux2==0)){
            return 0; // Piece moved more than 1 square
          } else {
            if (chess_table[y2][x2].piece_name == EMPTY || chess_table[y2][x2].color != WHITE)
              return 1;
          }
        return 0;
      }
      return 0;
  }
}

void move_piece(char* buffer){
  int x1,x2,y1,y2;
  parse_move(buffer,&x1,&y1,&x2,&y2);//A2 A3
  if(player_turn == 0) {
  	player_turn = 1;
  	sys_unregister_timertick_function(player_one_timer);
  	sys_register_timertick_function(player_two_timer, 18);
  } else {
  	player_turn = 0;
  	sys_unregister_timertick_function(player_two_timer);
  	sys_register_timertick_function(player_one_timer, 18);
  }
  if (check_movement(x1,y1,x2,y2)){
  	move_chess_piece(x1,y1,x2,y2);
  } else {
  	puts("Error");
  }
  sys_clear_line();
}
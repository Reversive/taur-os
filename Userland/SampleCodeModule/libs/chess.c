#include "../include/chess.h"
int last_added_move = 0;
int number_of_moves = 0;
int last_printable_index = 0;
int first_printable_index = 0;
chess_move moves[100];
chess_piece chess_table[8][8];
chess_piece printeable_chess_table[8][8];
int player_turn = 0;
int b_cursor_x = 0;
int b_cursor_y = 0;
int player_win=0;

int current_player_one_seconds;
int current_player_two_seconds;
int timer_start_move;

void join_chess() {
    if(chess_state != PAUSED)  {
      player_turn = 0;
    }

    if(chess_state == PAUSED) {
      if(player_turn == 0) {
        timer_start_move = current_player_one_seconds;
        sys_register_timertick_function(player_one_timer, 18);
      } else {
        timer_start_move = current_player_two_seconds;
        sys_register_timertick_function(player_two_timer, 18);
      }

    } else {
      sys_register_timertick_function(player_one_timer, 18);
    }

    sys_get_cursor_pos(&b_cursor_x, &b_cursor_y);
    if(chess_state != PAUSED) current_player_one_seconds = current_player_two_seconds = timer_start_move =  300;
    sys_backup_kb_buffer();
		sys_backup_screen();
    sys_set_cursor_status(_DISABLED);
    int rotation = 0;

    chess_piece pawn_white =  {PAWN,  0, WHITE, IDLE};
    chess_piece king_white =  {KING,  0, WHITE, IDLE};
    chess_piece tower_white = {TOWER, 0, WHITE, IDLE};
    chess_piece horse_white = {HORSE, 0, WHITE, IDLE};
    chess_piece queen_white = {QUEEN, 0, WHITE, IDLE};
    chess_piece bishop_white = {BISHOP,0, WHITE, IDLE};

    chess_piece pawn_black =  {PAWN,  0, BLACK, IDLE};
    chess_piece king_black =  {KING,  0, BLACK, IDLE};
    chess_piece tower_black = {TOWER, 0, BLACK, IDLE};
    chess_piece horse_black = {HORSE, 0, BLACK, IDLE};
    chess_piece queen_black = {QUEEN, 0, BLACK, IDLE};
    chess_piece bishop_black = {BISHOP,0, BLACK, IDLE};
    chess_piece empty = {EMPTY, 0, 0, 0};
    if(chess_state != PAUSED) {
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

        /* Descomentar para escenario de enroque
        chess_table[0][1]=empty;
        chess_table[7][1]=empty;
        chess_table[0][2]=empty;
        chess_table[7][2]=empty;
        chess_table[0][3]=empty;
        chess_table[7][3]=empty;
        chess_table[0][5]=empty;
        chess_table[7][5]=empty;
        chess_table[0][6]=empty;
        chess_table[7][6]=empty;
        */

        /* Descomentar para escenario de captura al paso
        chess_table[4][2]=pawn_black;
        chess_table[3][5]=pawn_white;
        */
    }

    load_printeable_chess_table(chess_table);
    sys_clear_screen();
    print_string_by_pos(700, 10, "Negras  ", 0xFF0000, 1);
		print_string_by_pos(700, 26, "Blancas ", 0xFFFFFF, 1);
    print_string_by_pos(720, 68, "Jugadas", 0xFFFFFF, 2);
    if(chess_state != PAUSED) {
      print_string_by_pos(828, 10, "5:00", 0xFF0000, 1);
		  print_string_by_pos(828, 26, "5:00", 0xFFFFFF, 1);
    } else {
      player_two_timer();
      player_one_timer();
    }
    print_chess_table(chess_table);
    sys_set_cursor_pos(0, 720);
    sys_set_cursor_status(_ENABLED);
    if(chess_state == PAUSED)  print_plays();
    chess_state = 1;


}

print_winner(int player_win){
  unsigned int i=0xff0000;
  int j=0;
  int r,g,b;
  if (player_win!=0){

    for ( j = 0; j < 6; j++){
        draw_square(165+(j*39),245,120,0);
    }
    sys_set_cursor_pos(280,320);
    sys_draw_character(259, 280, 'G', 2, 0xFFFFFF);
	  sys_draw_character(274, 280, 'A', 2, 0xFFFFFF);
	  sys_draw_character(289, 280, 'N', 2, 0xFFFFFF);
	  sys_draw_character(304, 280, 'A', 2, 0xFFFFFF);
	  sys_draw_character(319, 280, 'D', 2, 0xFFFFFF);
	  sys_draw_character(334, 280, 'O', 2, 0xFFFFFF);
	  sys_draw_character(349, 280, 'R', 2, 0xFFFFFF);
	  sys_draw_character(364, 280, '!', 2, 0xFFFFFF);

    if ((player_win)==1){
      puts("Las Negras");
    }
    if (player_win==2){
      puts("Las Blancas");
    }

    for (j = 0; j < 320; j+=2){
      draw_square(j+160,240,5,0xff0000);
      draw_square(480-j,360,5,0xff0000);
    }
    for (j = 0; j < 120; j+=2){
      draw_square(160,360-j,5,0xff0000);
      draw_square(480,240+j,5,0xff0000);
    }
    sys_unregister_timertick_function(player_one_timer);
    sys_unregister_timertick_function(player_two_timer);
    chess_state=ENDED;
    sys_set_newline_scroll_state(1);
    sys_set_cursor_pos(64,720);
  }
}

int win_codition(int black_king,int white_king){
  if(black_king==white_king){
    return 0;
  }else if (black_king==1){
    return 1;
  }else{
    return 2;
  }
}

void load_printeable_chess_table(chess_piece chess_table[8][8]){
  int i,j;
  int white_king=0;
  int black_king=0;
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      printeable_chess_table[i][j]=chess_table[i][j];
      if (chess_table[i][j].piece_name==KING){
        if(chess_table[i][j].color==WHITE){
          white_king=1;
        }
        if(chess_table[i][j].color==BLACK){
          black_king=1;
        }
      }
    }
  }
  player_win = win_codition(black_king,white_king);
}

void rotation_chess_table(){
  int i,j,h;
  chess_piece aux[8][8];
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      aux[i][j]=printeable_chess_table[7-j][i];
    }
  }
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      printeable_chess_table[i][j]=aux[i][j];
    }
  }
}

void print_chess_table( chess_piece chess_table[][8]){

    for (int i = 0; i < 8; i++){
      if (rotation %2==0){
        sys_draw_character(650, 20+(80*i), (rotation==0) ? ('8'-i) : ('1'+i) , 2, 0xFFFFFF);
	      sys_draw_character(20+(80*i), 650, (rotation==0) ? ('A'+i) : ('H'-i), 2, 0xFFFFFF);
      }else{
        sys_draw_character(650, 20+(80*i), (rotation==1) ? ('A'+i) : ('H'-i) , 2, 0xFFFFFF);
	      sys_draw_character(20+(80*i), 650, (rotation==1) ? ('1'+i) : ('8'-i), 2, 0xFFFFFF);
      }
    }

    for(int j = 0; j < 8; j+=2){
    		for(int i = 0; i < 8; i+=2) {
    			draw_square(i*80, j * 80, 80, 0xb3a076);
    			draw_square((i+1)*80, j * 80, 80, 0xdfdfd3);
    		}
    		for(int i = 0; i < 8; i+=2) {
    			draw_square(i*80, (j+1) * 80, 80, 0xdfdfd3);
    			draw_square((i+1)*80, (j+1) * 80, 80, 0xb3a076);
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
    load_printeable_chess_table(chess_table);
    for (int i = 0; i < (rotation%4); i++){
      rotation_chess_table();
    }
    print_chess_table(printeable_chess_table);
    print_winner(player_win);
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

void player_two_timer() {
  sys_draw_character(876, 10, ' ', 1, 0x000000);
  unsigned int seconds = current_player_two_seconds % 60;
  unsigned int minutes = current_player_two_seconds / 60;
  char mins[4];
  char secs[4];
  char * f_m = itoa(minutes, mins, 10);
  char * f_s = itoa(seconds, secs, 10);
	print_string_by_pos(828, 10, f_m, 0xFF0000, 1);
  sys_draw_character(844, 10, ':', 1, 0xFF0000);
  print_string_by_pos(860, 10, f_s, 0xFF0000, 1);
  current_player_two_seconds -= 1;
  if(current_player_one_seconds - current_player_two_seconds == 61) {
    player_win=2;
    print_winner(player_win);
  }
}

void player_one_timer() {
  sys_draw_character(876, 26, ' ', 1, 0x000000);
  unsigned int seconds = current_player_one_seconds % 60;
  unsigned int minutes = current_player_one_seconds / 60;
  char mins[4];
  char secs[4];
  char * f_m = itoa(minutes, mins, 10);
  char * f_s = itoa(seconds, secs, 10);
	print_string_by_pos(828, 26, f_m, 0xFFFFFF, 1);
  sys_draw_character(844, 26, ':', 1, 0xFFFFFF);
  print_string_by_pos(860, 26, f_s, 0xFFFFFF, 1);
	current_player_one_seconds -= 1;
  if(current_player_two_seconds - current_player_one_seconds == 61) {
    player_win=1;
    print_winner(player_win);
  }
}




int check_movement(int x1,int y1,int x2,int y2) {
  int aux1 = x1-x2;
  int aux2 = y1-y2;

  enum colors color_player = WHITE;
  int factor = 1;

  if (player_turn == 1){
    color_player = BLACK;
    factor = -1;
  }

  if (chess_table[y1][x1].piece_name == EMPTY || chess_table[y1][x1].color != color_player)
    return 0;

  switch (chess_table[y1][x1].piece_name) {
    case PAWN:
      if ((chess_table[y1][x1].piece_state == IDLE && (x2 == x1 && y2 == y1-(2*factor))) // advance forward 2 positions
      || (x2 == x1 && y2 == y1-(1*factor))){                                             // advance forward 1 positions
         if (chess_table[y2][x2].piece_name == EMPTY)
          return 1; // Base movement
      } else if ((x2 == x1-1 || x2 == x1+1) && y2 == y1-(1*factor) && chess_table[y2][x2].piece_name != EMPTY && chess_table[y2][x2].color != color_player){
        return 1; // Take enemy piece
      } else if (x2 == x1-1 && y2 == y1-factor && chess_table[y1][x1-1].piece_name == PAWN && chess_table[y1][x1-1].piece_state == PASO){ // advance forward (captura al paso) LEFT
        if (chess_table[y1][x1-1].color != color_player){
          chess_piece empty={EMPTY,0,0,0};
          chess_table[y1][x1-1] = empty;
          return 1;
        }
      } else if (x2 == x1+1 && y2 == y1-factor && chess_table[y1][x1+1].piece_name == PAWN && chess_table[y1][x1+1].piece_state == PASO){ // advance forward (captura al paso) RIGHT
        if (chess_table[y1][x1+1].color != color_player){
          chess_piece empty={EMPTY,0,0,0};
          chess_table[y1][x1+1] = empty;
          return 1;
        }
      }
      return 0;
    case TOWER:
      if (x1==x2 && y1 != y2){ // Y movement
        if (aux2 > 0){
          for (int i = y1-1; i>y2; i--){ // Base movement -> UP
            if (chess_table[i][x2].piece_name != EMPTY)
              return 0;
          }
        } else {
          for (int i = y1+1; i<y2; i++){ // Base movement -> DOWN
            if (chess_table[i][x2].piece_name != EMPTY)
              return 0;
          }
        }
      } else if (y1==y2 && x1 != x2){ // X movement
        if (aux1 > 0){
          for (int i = x1-1; i>x2; i--){ // Base movement -> RIGHT
            if (chess_table[y2][i].piece_name != EMPTY)
              return 0;
          }
        } else {
          for (int i = x1+1; i<x2; i++){ // Base movement -> LEFT
            if (chess_table[y2][i].piece_name != EMPTY)
              return 0;
          }
        }
      } else {
        return 0;
      }
      if ((chess_table[y2][x2].piece_name == EMPTY || chess_table[y2][x2].color != color_player)
      || (chess_table[y2][x2].piece_name == KING && chess_table[y2][x2].color == color_player && chess_table[y1][x1].piece_state == IDLE && chess_table[y2][x2].piece_state == IDLE))
        return 1;
      return 0;
    case HORSE:
      if ((x2 == x1-2 && (y2 == y1+1 || y2 == y1-1)) || (x2 == x1+2 && (y2 == y1+1 || y2 == y1-1))
      || (y2 == y1-2 && (x2 == x1+1 || x2 == x1-1)) || (y2 == y1+2 && (x2 == x1+1 || x2 == x1-1))){
        if (chess_table[y2][x2].piece_name == EMPTY || chess_table[y2][x2].color != color_player)
          return 1;
      }
      return 0;
    case BISHOP:
    if (abs(aux1) == abs(aux2)){ // Diagonal movement
      if (aux1 > 0 && aux2 > 0){
        // TOP-LEFT
        for (int i = x1-1, j = y1-1; i>x2; i--, j--){
          if (chess_table[j][i].piece_name != EMPTY)
            return 0;
        }
      } else if (aux1 < 0 && aux2 > 0){
        // TOP-RIGHT
        for (int i = x1-1, j = y1+1; i>x2; i--, j++){
          if (chess_table[j][i].piece_name != EMPTY)
            return 0;
        }
      } else if (aux1 > 0 && aux2 < 0){
        // BOTTOM-LEFT
        for (int i = x1+1, j = y1-1; i<x2; i++, j--){
          if (chess_table[j][i].piece_name != EMPTY)
            return 0;
        }
      } else if (aux1 < 0 && aux2 < 0){
        // BOTTOM-RIGHT
        for (int i = x1+1, j = y1+1; i<x2; i++, j++){
          if (chess_table[j][i].piece_name != EMPTY)
            return 0;
        }
      } else
        return 0;
    }
    if (chess_table[y2][x2].piece_name == EMPTY || chess_table[y2][x2].color != color_player)
      return 1;
    return 0;
    case QUEEN:
      if (abs(aux1) == abs(aux2)){ // Diagonal movement
        if (aux1 > 0 && aux2 > 0){
          // TOP-LEFT
          for (int i = x1-1, j = y1-1; i>x2; i--, j--){
            if (chess_table[j][i].piece_name != EMPTY)
              return 0;
          }
        } else if (aux1 < 0 && aux2 > 0){
          // TOP-RIGHT
          for (int i = x1-1, j = y1+1; i>x2; i--, j++){
            if (chess_table[j][i].piece_name != EMPTY)
              return 0;
          }
        } else if (aux1 > 0 && aux2 < 0){
          // BOTTOM-LEFT
          for (int i = x1+1, j = y1-1; i<x2; i++, j--){
            if (chess_table[j][i].piece_name != EMPTY)
              return 0;
          }
        } else if (aux1 < 0 && aux2 < 0){
          // BOTTOM-RIGHT
          for (int i = x1+1, j = y1+1; i<x2; i++, j++){
            if (chess_table[j][i].piece_name != EMPTY)
              return 0;
          }
        } else
          return 0;
      } else {
        if (x1==x2 && y1 != y2){ // Y movement --> + Movement
          if (y1 - y2 > 0){
            for (int i = y1-1; i>y2; i--){
              if (chess_table[i][x2].piece_name != EMPTY)
                return 0;
            }
          } else {
            for (int i = y1+1; i<y2; i++){
              if (chess_table[i][x2].piece_name != EMPTY)
                return 0;
            }
          }
        } else if (y1==y2 && x1 != x2){ // X movement
          if (x1 - x2 > 0){
            for (int i = x1-1; i>x2; i--){
              if (chess_table[y2][i].piece_name != EMPTY)
                return 0;
            }
          } else {
            for (int i = x1+1; i<x2; i++){
              if (chess_table[y2][i].piece_name != EMPTY)
                return 0;
            }
          }
        } else {
          return 0;
        }
      }
      if (chess_table[y2][x2].piece_name == EMPTY || chess_table[y2][x2].color != color_player)
        return 1;
      return 0;
    case KING:
      aux1 = abs(aux1);
      aux2 = abs(aux2);
      if (chess_table[y2][x2].piece_name == TOWER && chess_table[y2][x2].color == color_player && chess_table[y1][x1].piece_state == IDLE && chess_table[y2][x2].piece_state == IDLE){
        //Validacion solo para enroque
        if (y1==y2 && x1 != x2){
          if (aux1 > 0){
            for (int i = x1-1; i>x2; i--){
              if (chess_table[y2][i].piece_name != EMPTY)
                return 0;
            }
          } else {
            for (int i = x1+1; i<x2; i++){
              if (chess_table[y2][i].piece_name != EMPTY)
                return 0;
            }
          }
        } else
          return 0;
        return 1;
      } else if (aux1 > 1 || aux2 > 1 || (aux1==0 && aux2==0)){
        return 0; // Piece moved more than 1 square
      } else {
        if (chess_table[y2][x2].piece_name == EMPTY || chess_table[y2][x2].color != color_player)
          return 1;
      }
      return 0;
  }
}

void move_piece(char* buffer) {
  int x1,x2,y1,y2;
  parse_move(buffer,&x1,&y1,&x2,&y2);
  if (check_movement(x1,y1,x2,y2) == 1) {
    if(last_printable_index - first_printable_index == MAX_PRINTABLE_MOVES) first_printable_index++;
    moves[number_of_moves].author = player_turn;
    strcpy(moves[number_of_moves].text, buffer+5);
    number_of_moves++;
    last_printable_index++;
    if(player_turn == 0) {
      if (chess_table[y1][x1].piece_name == PAWN && y2 == 0){ // Pawn Promotion / WHITE
        chess_piece queen_white = {QUEEN, 0, WHITE, IDLE};
        chess_table[y1][x1] = queen_white;
      } else if (chess_table[y2][x2].piece_name == KING || chess_table[y2][x2].piece_name == TOWER){
        chess_piece king_white = {KING, 0, WHITE, MOVING};
        chess_piece tower_white = {TOWER, 0, WHITE, MOVING};
        chess_piece empty = {EMPTY, 0, 0, 0};
        if (abs(x1-x2) == 3){
          chess_table[y2][7] = empty;
          chess_table[y2][6] = king_white;
          chess_table[y2][5] = tower_white;
        } else {
          chess_table[y2][0] = empty;
          chess_table[y2][2] = king_white;
          chess_table[y2][3] = tower_white;
        }
        chess_table[y2][4] = empty;
      }
    	player_turn = 1;
      timer_start_move = current_player_two_seconds;
    	sys_unregister_timertick_function(player_one_timer);
    	sys_register_timertick_function(player_two_timer, 18);
    } else {
      if (chess_table[y1][x1].piece_name == PAWN && y2 == 7){ // Pawn Promotion / BLACK
        chess_piece queen_black = {QUEEN, 0, BLACK, IDLE};
        chess_table[y1][x1] = queen_black;
      } else if (chess_table[y2][x2].piece_name == KING || chess_table[y2][x2].piece_name == TOWER){
        chess_piece king_black = {KING, 0, BLACK, MOVING};
        chess_piece tower_black = {TOWER, 0, BLACK, MOVING};
        chess_piece empty = {EMPTY, 0, 0, 0};
        if (abs(x1-x2) == 3){
          chess_table[y2][7] = empty;
          chess_table[y2][6] = king_black;
          chess_table[y2][5] = tower_black;
        } else {
          chess_table[y2][0] = empty;
          chess_table[y2][2] = king_black;
          chess_table[y2][3] = tower_black;
        }
        chess_table[y2][4] = empty;
      }
    	player_turn = 0;
      timer_start_move = current_player_one_seconds;
    	sys_unregister_timertick_function(player_two_timer);
    	sys_register_timertick_function(player_one_timer, 18);
    }
    if (chess_table[y1][x1].piece_name == PAWN && chess_table[y1][x1].piece_state == IDLE && abs(y1-y2) == 2){
      chess_table[y1][x1].piece_state = PASO; // If the piece is an idle pawn moving 2 positions, its state will now be PASO, otherwise MOVING
    } else
      chess_table[y1][x1].piece_state = MOVING;
  	  move_chess_piece(x1,y1,x2,y2);
  }
  sys_clear_line();
  print_plays();

}

void print_plays() {
  for(int i = 0; i < MAX_PRINTABLE_MOVES; i++) {
    if(i >= last_printable_index) continue;
    char move_buffer[4];
    char * move_number = itoa(i + 1 + first_printable_index, move_buffer, 10);
    int color = WHITE;
    if(moves[first_printable_index + i].author == 1) color = RED;
    print_string_by_pos(710, 105 + i * 16, move_number, color, 1);
    sys_draw_character(740, 105 + i * 16, '-', 1, color);
    print_string_by_pos(758, 105 + i * 16, moves[first_printable_index + i].text, color, 1);
    if(moves[first_printable_index + i].author == 0) {
      sys_draw_character(838, 105 + i * 16, '-', 1, color);
      print_string_by_pos(854, 105 + i * 16, "Blancas", color, 1);
    } else {
      sys_draw_character(838, 105 + i * 16, '-', 1, color);
      print_string_by_pos(854, 105 + i * 16, "Negras ", color, 1);
    }
  }
}


void close_chess(int status) {
  sys_set_cursor_status(_DISABLED);
  chess_state = status;
  sys_clear_screen();
  sys_unregister_timertick_function(player_one_timer);
  sys_unregister_timertick_function(player_two_timer);
  sys_restore_kb_buffer();
  sys_restore_screen();
  sys_set_newline_scroll_state(0);
  sys_set_cursor_pos(b_cursor_x,b_cursor_y);
  sys_set_cursor_status(_ENABLED);
}


void reset_moves_idx() {
  first_printable_index = last_printable_index = number_of_moves = 0;
}

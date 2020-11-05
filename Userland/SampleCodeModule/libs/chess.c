#include "../include/chess.h"


    chess_piece chess_table[8][8];

void join_chess(){
    
    struct movement n; n.x=0; n.y=1;
    struct movement s; s.x=0; s.y=-1;
    struct movement w; w.x=-1; w.y=0;
    struct movement e; e.x=1; e.y=0;
    struct movement ne; ne.x=1; ne.y=1;
    struct movement nw; nw.x=-1; nw.y=1;
    struct movement se; se.x=1; se.y=-1;
    struct movement sw; sw.x=-1; sw.y=-1;
    
    chess_piece pawn_white={PAWN,0,WHITE,IDLE};
    chess_piece tower_white={TOWER,0,WHITE,IDLE};
    chess_piece horse_white={HORSE,0,WHITE,IDLE};
    chess_piece bishop_white={BISHOP,0,WHITE,IDLE};
    chess_piece queen_white={QUEEN,0,WHITE,IDLE};
    chess_piece king_white={KING,0,WHITE,IDLE};

    chess_piece pawn_black={PAWN,0,BLACK,IDLE};
    chess_piece tower_black={TOWER,0,BLACK,IDLE};
    chess_piece horse_black={HORSE,0,BLACK,IDLE};
    chess_piece bishop_black={BISHOP,0,BLACK,IDLE};
    chess_piece queen_black={QUEEN,0,BLACK,IDLE};
    chess_piece king_black={KING,0,BLACK,IDLE};
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
        chess_table[0][7]=tower_black;
        chess_table[7][7]=tower_white;
        chess_table[0][1]=horse_black;
        chess_table[7][1]=horse_white;
        chess_table[0][2]=bishop_black;        
        chess_table[7][2]=bishop_white;
        chess_table[0][3]=queen_black;
        chess_table[7][3]=queen_white;
        chess_table[0][4]=king_black;
        chess_table[7][4]=king_white;
        chess_table[0][5]=horse_black;
        chess_table[7][5]=horse_white;
        chess_table[0][6]=bishop_black;        
        chess_table[7][6]=bishop_white;
    


    print_chess_table(chess_table);
    
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
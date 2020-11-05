#include "include/video_driver.h"

// https://wiki.osdev.org/Drawing_In_Protected_Mode
void paint_pixel(int x, int y, int color) {
    struct vbe_mode_info_structure * video_pointer = (struct vbe_mode_info_structure *)0x5C00;
    char * buffer = video_pointer->framebuffer;
    int offset = (x + y * WIDTH) * BPP;
    buffer[offset] = color & 255;              // BLUE
    buffer[offset + 1] = (color >> 8) & 255;   // GREEN
    buffer[offset + 2] = (color >> 16) & 255;  // RED
}

// https://wiki.osdev.org/Drawing_In_Protected_Mode
void paint_rectangle(int x, int y, int w, int h, int color) {
    int i,j;
    for(i = 0; i < w; i++)
        for(j = 0; j < h; j++)
            paint_pixel(x + i, y + j, color);
}

// Same a painting a rectangle with equal sides
void paint_square(int x, int y, int s, int color) {
    paint_rectangle(x, y, s, s, color);
}

// Check if bit on bitmap is active, if it is then paint a square of font_size
void paint_character(int x, int y, char character, int size, int color, int bg_color) {
    unsigned char * char_bitmap = charBitmap(character);
    int horizontal_slide = x;
    int vertical_slide = y;
    for(int i = 0; i < CHAR_HEIGHT; i++) {
        for(int j = 0; j < CHAR_WIDTH; j++) {
            // https://stackoverflow.com/a/523737
            if(CHECK_BIT(char_bitmap[i], CHAR_WIDTH - j)) {
                paint_square(horizontal_slide, vertical_slide, size, color);
            } else {
                paint_square(horizontal_slide, vertical_slide, size, bg_color);
            }
            horizontal_slide += size;
        }
        // reset horizontal idx
        horizontal_slide = x;
        vertical_slide += size;
    }
}

void scroll(int times) {
    struct vbe_mode_info_structure * video_pointer = (struct vbe_mode_info_structure *)0x5C00;
    char * buffer = video_pointer->framebuffer;
    int offseted_row = times * WIDTH * BPP;
    int last = HEIGHT * WIDTH * BPP;
    int to_remove = 0;
    while(offseted_row < last) {
        buffer[to_remove] = buffer[offseted_row];
        offseted_row++;
        to_remove++;
    }

    for(int i = HEIGHT - times; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH * BPP; j++) {
            paint_pixel(j, i, 0x00000000);
        }
    }
}

void paint_matrix(int x, int y, int color, int size, char * matrix) {
    int h_slide = x;
    int v_slide = y;
    int outline=0;
    if (color == 0x000000) {
        outline=0xFFFFFF;
    } else if(color==0xFFFFFF){
        outline=0x000000;
    }
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(matrix[i * 16 + j] == '2'){
             paint_square(h_slide , v_slide , 5, color);
            }  else if(matrix[i * 16 + j] == '1') {
                paint_square(h_slide , v_slide , 5, outline);
            }
            h_slide += 5;
        }
        h_slide = x;
        v_slide += 5;

    }
}

void clear_screen(int color) {
    paint_rectangle(0, 0, WIDTH, HEIGHT, color);
}
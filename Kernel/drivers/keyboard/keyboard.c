// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/keyboard.h"
static states key_state = NONE;
static ring kb_ring = {0, 0, 0, {0}};
static ring b_kb_ring = {0, 0, 0, {0}};
int exists_kb_backup = 0;
int caps = 0;

static unsigned char bloqCaps[] = {
NULL, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE,
TAB, 'Q', 'W',   'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',   '[', ']', ENTER, 0,
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0, 0, 0, ' ', 0,
KF1, KF2, KF3, KF4, KF5, KF6, KF7, KF8, KF9, KF10, 0, 0,
KHOME, KUP, KPGUP,'-', KLEFT, '5', KRIGHT, '+', KEND, KDOWN, KPGDN, KINS, KDEL, 0, 0, 0, KF11, KF12 };

static unsigned char asciiNonShift[] = {
NULL, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE,
TAB, 'q', 'w',   'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   '[', ']', ENTER, 0,
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0,
KF1, KF2, KF3, KF4, KF5, KF6, KF7, KF8, KF9, KF10, 0, 0,
KHOME, KUP, KPGUP,'-', KLEFT, '5', KRIGHT, '+', KEND, KDOWN, KPGDN, KINS, KDEL, 0, 0, 0, KF11, KF12 };

static unsigned char asciiShift[] = {
NULL, ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', BACKSPACE,
TAB, 'Q', 'W',   'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',   '{', '}', ENTER, 0,
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0, '|',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' ', 0,
KF1,   KF2, KF3, KF4, KF5, KF6, KF7, KF8, KF9, KF10, 0, 0,
KHOME, KUP, KPGUP, '-', KLEFT, '5',   KRIGHT, '+', KEND, KDOWN, KPGDN, KINS, KDEL, 0, 0, 0, KF11, KF12 };



void kb_trigger() {
    
    key current = _fetch_key();
    switch (current) {
    // https://www.henkessoft.de/OS_Dev/OS_Dev1.htm#mozTocId185043
    // Also got some from https://wiki.osdev.org/PS/2_Keyboard on Scan Code Set 1
    case KRLEFT_SHIFT:
        key_state = SHIFT;
        return;
        break;
    
    case KRRIGHT_SHIFT:
        key_state = SHIFT;
        return;
        break;

    case KRLEFT_SHIFT_RELEASE:
        key_state = NONE;
        return;
        break;

    case KRCAPS_LOCK:
        if(caps == 0) {
            caps = 1;
        } else {
            caps = 0;
        }
        return;
        break;
    
    default:
        break;
    }

    // https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html#ss1.1
    if(current >= OUT_OF_RANGE) return;

    key ascii = asciiNonShift[current];
    if(key_state == SHIFT) {
        if(caps == 0) {
            ascii = asciiShift[current];
        }
        
    } else {
        if(caps == 1) ascii = bloqCaps[current];
    }

    queue(ascii);


    return;
};

void queue(key current_key) {
    kb_ring.kb_buffer[kb_ring.queue_pos++] = current_key;
    if(kb_ring.queue_pos == KB_BUFFER_SIZE) kb_ring.queue_pos = 0;
    kb_ring.pending_read++;
    if(kb_ring.pending_read >= KB_BUFFER_OVERFLOW) kb_ring.pending_read = 0;
}

key getchar() {
    if(kb_ring.pending_read == 0) return 0xFF;
    key pop = kb_ring.kb_buffer[kb_ring.dequeue_pos++];
    if(kb_ring.dequeue_pos == KB_BUFFER_SIZE) kb_ring.dequeue_pos = 0;
    kb_ring.pending_read--;
    return pop;
}

void backup_kb_buffer() {
    exists_kb_backup = 1;
    b_kb_ring.dequeue_pos = kb_ring.dequeue_pos;
    b_kb_ring.pending_read = kb_ring.pending_read;
    b_kb_ring.queue_pos = kb_ring.queue_pos;
    for(int i = 0; i < KB_BUFFER_SIZE; i++) {
        b_kb_ring.kb_buffer[i] = kb_ring.kb_buffer[i];
    }
}

int restore_kb_buffer() {
    if(exists_kb_backup == 0) return -1;
    kb_ring.dequeue_pos = b_kb_ring.dequeue_pos;
    kb_ring.pending_read = b_kb_ring.pending_read;
    kb_ring.queue_pos = b_kb_ring.queue_pos;
    for(int i = 0; i < KB_BUFFER_SIZE; i++) {
        kb_ring.kb_buffer[i] = b_kb_ring.kb_buffer[i];
    }
    return 1;
}


void clean_kb_buffer() {
    kb_ring.dequeue_pos = 0;
    for(int i = 0; i < KB_BUFFER_SIZE; i++) {
        kb_ring.kb_buffer[i] = 0;
    }
    kb_ring.pending_read = 0;
    kb_ring.queue_pos = 0;
}

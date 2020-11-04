#include "include/kb_driver.h"
static state key_state = NONE;
static ring kb_ring = {0, 0, 0, {0}};

// Non-Shifted scan codes to ASCII:
static unsigned char asciiNonShift[] = {
NULL, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE,
TAB, 'q', 'w',   'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   '[', ']', ENTER, 0,
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0,
KF1, KF2, KF3, KF4, KF5, KF6, KF7, KF8, KF9, KF10, 0, 0,
KHOME, KUP, KPGUP,'-', KLEFT, '5', KRIGHT, '+', KEND, KDOWN, KPGDN, KINS, KDEL, 0, 0, 0, KF11, KF12 };

// Shifted scan codes to ASCII:
static unsigned char asciiShift[] = {
NULL, ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', BACKSPACE,
TAB, 'Q', 'W',   'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',   '{', '}', ENTER, 0,
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0, '|',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' ', 0,
KF1,   KF2, KF3, KF4, KF5, KF6, KF7, KF8, KF9, KF10, 0, 0,
KHOME, KUP, KPGUP, '-', KLEFT, '5',   KRIGHT, '+', KEND, KDOWN, KPGDN, KINS, KDEL, 0, 0, 0, KF11, KF12 };

void kb_trigger() {
    
    key current = _fetch_key();
    switch (current)
    {
    // https://www.henkessoft.de/OS_Dev/OS_Dev1.htm#mozTocId185043
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
    
    default:
        break;
    }

    // https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html#ss1.1
    if(current > OUT_OF_RANGE) return;

    key ascii = asciiNonShift[current];
    if(key_state == SHIFT) {
        ascii = asciiShift[current];
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
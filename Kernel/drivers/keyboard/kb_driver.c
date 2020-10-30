#include "include/kb_driver.h"
static state key_state = NONE;
static ring kb_ring = {0, 0, 0, {0}};

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
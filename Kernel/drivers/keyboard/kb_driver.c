#include "include/kb_driver.h"
static state key_state = NONE;
static bool in_caps = 0;

int is_letter(key input) {
    return (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z');
}

void kb_trigger() {
    
    key current = _fetch_key();
    switch (current)
    {
    case KRCAPS_LOCK:
        if(in_caps == 1) {
            in_caps = 0;
        } else {
            in_caps = 1;
        }
        return;
        break;

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

    case KRRIGHT_ALT:
        key_state = ALT;
        return;
        break;
    
    case KRALT_RELEASE:
        key_state = NONE;
        return;
        break;

    case KRRIGHT_CTRL:
        key_state = CTRL;
        return;
        break;
    
    case KRCTRL_RELEASE:
        key_state = NONE;
        return;
        break;
    
    default:
        break;
    }

    // https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html#ss1.1
    if(current > OUT_OF_RANGE) return;

    if(key_state == SHIFT) {
        key print = asciiShift[current];
        if(in_caps && is_letter(current)) {
            print = asciiNonShift[current];
        }
        ncPrintChar(asciiShift[current]);
    } else {
        key print = asciiNonShift[current];
        if(in_caps && is_letter(current)) {
            print = asciiShift[current];
        }
        ncPrintChar(print);
    }


    return;
};
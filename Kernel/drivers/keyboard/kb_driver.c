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

    if(key_state == SHIFT) {
        if(in_caps && is_letter(current)) {
            ncPrintChar(asciiNonShift[current]);
        }
        ncPrintChar(asciiShift[current]);
    } else {
        if(in_caps && is_letter(current)) {
            ncPrintChar(asciiShift[current]);
        }
        ncPrintChar(asciiNonShift[current]);
    }


    return;
};

#include "../drivers/screens.h"
#include "util.h"


void main() {
    clear_screen();

    /* Fill up the screen */
    int i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint_at(str, 0, i);
    }

    kprint_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
}

// void main() {
//     clear_screen();
//     kprint_at("X", 1, 6);
//     kprint_at("This text spans multiple lines", 75, 10);
//     kprint_at("There is a line\nbreak", 0, 20);
//     kprint("There is a line\nbreak");
//     kprint_at("What happens when we run out of space?", 45, 24);
// }





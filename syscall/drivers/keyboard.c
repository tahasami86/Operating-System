#include "keyboard.h"
#include "../drivers/screens.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../drivers/ports.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"


#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_handler(register_t *regs){
    /* The PIC gives us the scancode in port 0x60 */
    u32 scancode = port_word_in(0x60);
   
    if (scancode >= SC_MAX) return;
    if(scancode == ENTER){
        kprint("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
    }
    else if (scancode == BACKSPACE){
        backspace(key_buffer);
        kprint_backspace();
    }
    else{
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter,'\0'};;
        append(key_buffer,letter);
        kprint(str);
    }

    UNUSED(regs);


}

void keyboard_init(){
    register_interrupt_handler(IRQ1,keyboard_handler);
}

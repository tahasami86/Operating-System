
#include "../drivers/ports.h"


void main(){
    /*Read a byte from port 0x3d4 and store it in high byte*/
    port_byte_out(0x3d4,14);

    int position = port_byte_in(0x3d5);
    position = position << 8; // shift high byte to left by 8 bits

    /*Read a byte from port 0x3d4 and store it in low byte*/
    port_byte_out(0x3d4,15);

    position += port_byte_in(0x3d5); // add low byte to position

    /* VGA 'cells' consist of the character and its control data */
    int vga_offset = position * 2 ; //

    char *video_memory = (char *) 0xb8000;
    video_memory[vga_offset] = 'K'; // character
    video_memory[vga_offset + 1] = 0x05; // pink on black background

    video_memory[vga_offset+10] = 'M'; // character
    video_memory[vga_offset + 11] = 0x02; // Green on black  background


}



/*
void main() {
    char* video_memory = (char*) 0xb8000;
    // *video_memory = 'X'; privoulst it was overwiting the 'L' in the previous message
    video_memory[70] = 'X'; 
    video_memory[71] = 0x07; // light grey on black background

    video_memory[72] = '0';
    video_memory[73] = 0x07;
}
*/
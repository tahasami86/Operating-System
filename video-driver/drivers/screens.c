#include "screens.h"
#include "ports.h"
#include "../kernel/util.h"

/*Helper functions Declare*/
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void kprint_at(char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}


void kprint(char *message) {
    kprint_at(message, -1, -1);
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Prints a character to the screen at the given position
 * with the given attribute.
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 *
 * @param c The character to print
 * @param col The column position to print at
 * @param row The row position to print at
 * @param attr The attribute (color) to print with
 * @return 0 on success
 */
int print_char(char c, int col, int row, char attr)
{

    unsigned char *videomem = (unsigned char *) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if(col >=MAX_COLS || row >= MAX_ROWS){
        videomem[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
        videomem[2 * MAX_COLS * MAX_ROWS - 1 ] = RED_ON_WHITE;
        return get_offset(col,row);
    }

    int offset;
    if(row >=0 && col >=0) offset = get_offset(col,row);
    else offset = get_cursor_offset();

    if(c == '\n'){
        row = get_offset_row(offset);
        offset = get_offset(0,row + 1);
    }

    else {
        videomem[offset] = c;
        videomem[offset + 1] = attr;
        offset += 2;
    }

    if(offset >= 2 * MAX_COLS * MAX_ROWS){
        for (int i=1; i < MAX_ROWS ; i++){
            memory_copy((get_offset(0,i) + VIDEO_ADDRESS),(get_offset(0,i-1)+ VIDEO_ADDRESS), 2 * MAX_COLS);
        }

        char *last_line = get_offset(0,MAX_ROWS -1) + VIDEO_ADDRESS;
        for (int i =0; i < 2 * MAX_COLS;i++) last_line[i] = 0;
        offset -= 2* MAX_COLS;
    }
    set_cursor_offset(offset);
    return offset;

    
}



/*
 * Use the VGA ports to get the current cursor position
 * 1. Ask for high byte of the cursor offset (data 14)
 * 2. Ask for low byte (data 15) 
 * 
*/
int get_cursor_offset(){
    int offset;

    port_byte_out(REG_SCREEN_CTRL,14); // Read High Byte
    offset = port_byte_in(REG_SCREEN_DATA) ; 
    offset = offset << 8 ; // Shift to left by 8 bits

    port_byte_out(REG_SCREEN_CTRL,15); // Read Low Byte
    offset += port_byte_in(REG_SCREEN_DATA) ;

    return offset * 2 ; // each cell is 2 bytes    

}

void set_cursor_offset(int offset){


    /* Similar to get_cursor_offset, but instead of reading we write data */

    offset /=2; // convert from cell offset to char offset
    port_byte_out(REG_SCREEN_CTRL,14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL,15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));

}

void clear_screen(){
    int screen_size = MAX_ROWS * MAX_COLS;
    unsigned char *screen = (unsigned char *)VIDEO_ADDRESS;

    for(int i=0;i<screen_size;i++){
        screen[i*2 ] = ' ';
        screen[i*2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0,0));
}

int get_offset(int col,int row) {return 2 * (row * MAX_COLS + col) ;  }
int get_offset_row(int offset) { return (offset / (2 * MAX_COLS)); }
int get_offset_col(int offset) {  return (offset - (get_offset_row(offset) * 2 *MAX_COLS))/2 ;  }

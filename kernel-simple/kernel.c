/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
    char* video_memory = (char*) 0xb8000;
    // *video_memory = 'X'; privoulst it was overwiting the 'L' in the previous message
    video_memory[70] = 'X'; 
    video_memory[71] = 0x07; // light grey on black background

    video_memory[72] = '0';
    video_memory[73] = 0x07;
}
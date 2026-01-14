global _start;
[bits 32]
_start:
    [extern kernel_main] ; call the main api. the name should match the one in the C file
    call kernel_main     ; call the main function.
    jmp $ ; infinite loop to prevent falling off
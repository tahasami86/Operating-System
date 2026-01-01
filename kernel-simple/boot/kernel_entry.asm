[bits 32]
[extern main] ; call the main api. the name should match the one in the C file
call main     ; call the main function.
jmp $ ; infinite loop to prevent falling off
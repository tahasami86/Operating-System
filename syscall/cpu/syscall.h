#ifndef SYSCALL_H
#define SYSCALL_H



#include "types.h"
#include "isr.h"

// System call numbers
#define SYS_PRINT   0
#define SYS_READ    1
#define SYS_EXIT    2
#define SYS_YIELD   3


// System call handler
void (syscall_handler) (register_t *);

// User mode wrapper functions
void user_print(char *str);
void user_exit(int code);

// Switch to user mode function (defined in assembly)
extern void switch_to_user_mode();

#endif
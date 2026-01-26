
#include "../drivers/screens.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "syscall.h"
#include "../kernel/kernel.h"

// System call table
typedef void (*syscall_t)(register_t*);


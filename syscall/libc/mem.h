#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

#include <stdint.h>
#include <stddef.h>

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(u8 *dest, u8 val, u32 len);
uint32_t kmalloc(size_t size, uint8_t allign, uint32_t *phy_addr);

#endif
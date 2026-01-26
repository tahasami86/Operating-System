#include "mem.h"


void memory_copy(char *source, char *dest, int nbytes){

    for (int i=0;i < nbytes; i++){
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/* This should be computed at link time, but a hardcoded
 * value is fine for now. Remember that our kernel starts
 * at 0x1000 as defined on the Makefile */
uint32_t free_mem_addr = 0x10000;
/* Implementation is just a pointer to some free memory which
 * keeps growing */
uint32_t kmalloc(size_t size,uint8_t allign, uint32_t *phy_addr)
{

    /* Pages are aligned to 4K, or 0x1000 */
    if((allign == 1) && (free_mem_addr & 0xFFF)){
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    /* Save also the physical address */
    if (phy_addr) *phy_addr = free_mem_addr;

    int ret = free_mem_addr;
    free_mem_addr += size ;

    return ret;

}

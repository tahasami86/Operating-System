// tss.h
#ifndef TSS_H
#define TSS_H

#include "../cpu/types.h"
#include "gdt.h"

struct tss_entry {
    u32 prev_tss;   // (unused)
    u32 esp0;       // kernel stack pointer
    u32 ss0;        // kernel stack segment

    u32 esp1, ss1;  // unused
    u32 esp2, ss2;  // unused

    u32 cr3;        // unused (paging)
    u32 eip, eflags;
    u32 eax, ecx, edx, ebx;
    u32 esp, ebp, esi, edi;

    u32 es, cs, ss, ds, fs, gs;
    u32 ldt;

    u16 trap;
    u16 iomap_base;
} __attribute__((packed));

extern void tss_flush(u32 idx);

// Initialize TSS
void tss_init(u32 idx, u32 kernel_ss, u32 kernel_esp);

// Update kernel stack (for task switching later)
void tss_set_kernel_stack(u32 stack);

#endif
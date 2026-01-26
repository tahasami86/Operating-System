#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CS 0X08 

/*iNTERRUTP GATE hANDLER IS DEFINED*/

typedef struct {
    u16 low_offset;
    u16 sel; /*Kernel segment selector*/
    u8 always0;

    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" 
     */
    u8 flags;
    u16 high_offset;

}__attribute__((packed)) igdt_gate_t ;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */

typedef struct {

    u16 limit;
    u32 base;

}__attribute__((packed)) igdt_register_t;


#define IGDT_ENTRIES 256
//extern igdt_gate_t idt[IGDT_ENTRIES];
//extern igdt_register_t idt_reg;

/* Functions implemented in idt.c */
void set_idt_gate(int n, u32 handlers,u8 flags);
void set_idt();

#endif
#ifndef ISR_H
#define ISR_H

#include "types.h"

/* ISRs reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/*IRQ  Definations*/
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47


/* Struct which aggregates many registers will be filled by cpu using asm*/

typedef struct {
    
    u16 ds; /* Data segment selector */
    u32 edi, esi, ebp, useless, ebx, edx, ecx, eax; /* Pushed by pusha. 
                                                   edi will be last pushed and just before ds
                                                   eax will be pushed after int_no*/


    u32 int_no,error_code; /*Interrupt number and error code (if applicable)
                              we will push both using asm int_no will be last
                              and error_code will be first pushed on stack*/


    u32 eip, cs, eflags, esp, ss; /* Pushed by the processor automatically (eip ) 
                                        will be last pushed by cpu on stack whereas ss or eflags 
                                        will be the first*/

} register_t;

void isr_install();
void isr_handler(register_t *t);
void irq_install();

typedef void (*isr_t )(register_t*);
/*Interrupt register Handler*/
void register_interrupt_handler(u8 n, isr_t handler);


/*irq handler*/
void irq_handler(register_t *t);


#endif
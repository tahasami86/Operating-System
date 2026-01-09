
#include "../drivers/screens.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main(){
    isr_install();

    asm volatile("sti");
//    timer_init(100000000000000);
    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    keyboard_init();

   // /* Test the interrupts */
   // __asm__ __volatile__("int $1");
   // __asm__ __volatile__("int $3");
   // __asm__ __volatile__("int $2");
   // __asm__ __volatile__("int $4");
   // __asm__ __volatile__("int $5");
   
}





#include "timer.h"
#include "../drivers/screens.h"
#include "isr.h"
#include "../kernel/util.h"
#include "../drivers/ports.h"
#include "../libc/function.h"

u32 tick = 0;

static void timer_handler(register_t regs)
{

    tick++;
    // kprint("Tick: ");
    // char tick_ascii[256];
    // int_to_ascii(tick,tick_ascii);
    // kprint(tick_ascii);
    // kprint("\n");
    UNUSED(regs);

}


void timer_init(u32 freq){

    register_interrupt_handler(IRQ0, timer_handler);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisior = 1193180 / freq;
    u8 low =  (u8)(divisior & 0xFF);
    u8 high = (u8)((divisior >> 8) & 0xFF);

    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40,(low));
    port_byte_out(0x40,(high));
}
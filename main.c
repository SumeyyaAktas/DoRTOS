#include "uart/pl011.h"
#include "systick/systick.h"

void hcf(void)
{
    for (;;)
    {
        __asm__ volatile("wfi");
    }
}

void main(void)
{
    uart_init();
    uart_puts("\nHello from TinyAbyss!\n");

    systick_init();
    __asm__ volatile("cpsie i");

    uint32_t last_tick = 0;

    while (1)
    {
        if (global_tick_counter != last_tick)
        {
            last_tick = global_tick_counter;

            uart_puts("Tick: ");
            uart_putc('0' + (last_tick % 10)); 
            uart_puts("\n");
        }
    }

    hcf();
}
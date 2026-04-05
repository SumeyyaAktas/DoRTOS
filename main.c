#include "uart/pl011.h"
#include "systick/systick.h"
#include "task/task.h"

void task_a(void)
{
    while (1)
    {
        uart_puts("Task A\n");
    }
}

void task_b(void)
{
    while (1)
    {
        uart_puts("Task B\n");
    }
}

void main(void)
{
    uart_init();
    uart_puts("\nHello from DoRTOS!\n\n");

    systick_init();
    __asm__ volatile("cpsie i");

    // uint32_t last_tick = 0;

    // while (1)
    // {
    //     if (global_tick_counter != last_tick)
    //     {
    //         last_tick = global_tick_counter;

    //         uart_puts("Tick: ");
    //         print_uint32(last_tick); 
    //         uart_puts("\n");
    //     }
    // }

    TCB_t tcb_a;
    TCB_t tcb_b;

    task_create(&tcb_a, task_a, 1);
    task_create(&tcb_b, task_b, 2);

    task_register(&tcb_a); 
    task_register(&tcb_b); 

    uart_puts("tcb_a Stack Pointer: ");
    print_uint32((uint32_t)tcb_a.stack_pointer);
    uart_puts("\n");

    uart_puts("tcb_b Stack Pointer: ");
    print_uint32((uint32_t)tcb_b.stack_pointer);
    uart_puts("\n");

    for (;;)
    {
        __asm__ volatile("wfi");
    }
}
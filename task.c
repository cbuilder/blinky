#include <stdint.h>
#include <stdbool.h>
#include "cmsis_gcc.h"
#include "task.h"

static uint32_t mem_stack_reserve = 0x20000000;
static uint32_t task_count = 0;

void psp_init(uint32_t stack_top)
{
    __set_PSP(stack_top);
}

void switch_psp()
{
    uint32_t control;
    control = __get_CONTROL();
    control |= 0x2; // PSP is the current stack pointer.
    __set_CONTROL(control);
}

int register_task(void (*tskfunc)(), uint32_t stack_size)
{
	mem_stack_reserve += stack_size;
	task[task_count].sp = mem_stack_reserve;
	task_count += 1;
	/* fill stack frame with necessary registers PC, LR etc. */
	return 0;
}

void idle()
{
	;
}
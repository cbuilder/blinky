#ifndef TASK_H
#define TASK_H

#define MIN_TSK_STACK_SIZE	512

void idle();
void switch_psp();
void psp_init(uint32_t stack_top);
int register_task(void (*tskfunc)(), uint32_t stack_size);

typedef struct task_s {
	char name[4];
	uint32_t priority;
	uint32_t sp;
} task_t;

task_t task[3];

#endif
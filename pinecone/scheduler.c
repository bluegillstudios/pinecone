#include "include/kernel.h"
#include "include/arch/x86_64/x86_64.h" 
#include <stdint.h>
#include "include/task.h" 

#define MAX_PROCESSES 64

extern task_t task_table[MAX_PROCESSES]; // defined in process.c
extern task_t* current_task;

void schedule() {
    int current_idx = -1;

    // Find current task index
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (&task_table[i] == current_task) {
            current_idx = i;
            break;
        }
    }

    for (int offset = 1; offset < MAX_PROCESSES; offset++) {
        int next = (current_idx + offset) % MAX_PROCESSES;
        if (task_table[next].state == TASK_READY) {
            task_t* next_task = &task_table[next];

            if (current_task && current_task->state == TASK_RUNNING)
                current_task->state = TASK_READY;

            next_task->state = TASK_RUNNING;
            current_task = next_task;

            switch_to((context_t*)current_task->context);
        }
    }

    // If nothing to schedule, loop forever
    while (1) { __asm__ volatile("hlt"); }
}

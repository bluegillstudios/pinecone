#include "include/kernel.h"
#include "include/ipc.h"
#include "include/arch/x86_64/x86_64.h"  
#include <stdint.h>
#include <stddef.h>

#define MAX_PROCESSES 64

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_TERMINATED
} task_state_t;

typedef struct {
    uint64_t pid;
    task_state_t state;
    void* stack;
    void* context;  // arch-specific saved registers
} task_t;

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rsi, rdi, rbp, rdx, rcx, rbx, rax;
    uint64_t rip, rsp;
} context_t;

static task_t task_table[MAX_PROCESSES];
static uint64_t next_pid = 1;
static task_t* current_task = NULL;

task_t* create_process(void (*entry_point)(void)) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (task_table[i].state == TASK_TERMINATED || task_table[i].state == 0) {
            task_t* task = &task_table[i];
            task->pid = next_pid++;
            task->state = TASK_READY;

            // Allocate stack (just a simple bump for now)
            task->stack = alloc_stack(); // Implemented in memory.c
            task->context = setup_initial_context(entry_point, task->stack); // arch-specific

            return task;
        }
    }
    return NULL;
}

void schedule() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (task_table[i].state == TASK_READY) {
            if (current_task)
                current_task->state = TASK_READY;

            task_table[i].state = TASK_RUNNING;
            current_task = &task_table[i];
            switch_to(current_task->context); // arch-specific
            return;
        }
    }
}

task_t* get_current_task() {
    return current_task;
}

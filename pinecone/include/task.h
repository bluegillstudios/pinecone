#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define TASK_READY   0
#define TASK_RUNNING 1
#define TASK_BLOCKED 2
#define TASK_DEAD    3

typedef struct task {
    uint32_t id;
    uint32_t state;
    void*    context;     // Pointer to saved CPU context (arch-specific)
    void*    stack;       // Allocated stack base
} task_t;

#endif

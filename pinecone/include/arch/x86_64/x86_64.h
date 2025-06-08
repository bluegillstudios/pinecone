#ifndef ARCH_X86_64_H
#define ARCH_X86_64_H

#include <stdint.h>

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rsi, rdi, rbp, rdx, rcx, rbx, rax;
    uint64_t rip, rsp;
} context_t;

void switch_to(context_t* new_ctx);
void* setup_initial_context(void (*entry)(void), void* stack_top);

#endif

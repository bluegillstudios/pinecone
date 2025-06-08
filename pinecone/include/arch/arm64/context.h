#ifndef ARM64_CONTEXT_H
#define ARM64_CONTEXT_H

#include <stdint.h>

// ARM64 context structure for saving/restoring registers
typedef struct {
    uint64_t x[30];   // General-purpose registers x0-x29
    uint64_t lr;      // Link register (x30)
    uint64_t sp;      // Stack pointer
    uint64_t pc;      // Program counter
    uint64_t cpsr;    // Current program status register (optional, if needed)
} context_t;

#endif // ARM64_CONTEXT_H
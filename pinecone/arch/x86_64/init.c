#include "../../include/kernel.h"

void kernel_init(void) {
    // Simple placeholder init function

    // For now, just loop indefinitely
    while (1) {
        // Halt CPU to save power
        __asm__ volatile ("hlt");
    }
}
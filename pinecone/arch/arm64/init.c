void kernel_init(void) {
    while (1) {
        __asm__ volatile ("wfe");
    }
}
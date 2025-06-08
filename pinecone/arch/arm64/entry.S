    .section .text
    .global _start
    .extern kernel_init

_start:
    msr daifset, #0xf
    ldr x0, =stack_top
    mov sp, x0
    bl kernel_init

hang:
    wfe
    b hang

    .bss
    .align 3
stack:
    .skip 4096
stack_top:

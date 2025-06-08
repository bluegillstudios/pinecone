    .section .text
    .global _start
    .align  7

_start:
    msr daifset, #0xf

    mrs x0, CurrentEL
    lsr x0, x0, #2
    and x0, x0, #0x3

    cmp x0, #3
    b.eq _from_el3

    cmp x0, #2
    b.eq _from_el2

    b _kernel_entry

_from_el3:
    mrs x1, scr_el3
    bic x1, x1, #(1 << 10)
    msr scr_el3, x1

    mov x2, #(0b1001) << 0
    msr spsr_el3, x2

    adrp x3, _from_el3_next
    add x3, x3, :lo12:_from_el3_next
    msr elr_el3, x3

    eret

_from_el3_next:

_from_el2:
    mov x1, #0
    msr hcr_el2, x1

    mov x2, #(0b0101) << 0
    msr spsr_el2, x2

    adrp x3, _kernel_entry
    add x3, x3, :lo12:_kernel_entry
    msr elr_el2, x3

    eret

_kernel_entry:
    ldr x0, =0x80000
    mov sp, x0
    mov x29, #0

    ldr x1, =0x80000
    br x1

1:
    wfe
    b 1b

.section .text
.global _start
.extern kernel_init

_start:
    cli                         # Disable interrupts

    # Load a minimal GDT (defined in assembly or C)
    lgdt [gdt_descriptor]

    # Enable long mode via control registers (if needed)
    mov eax, cr0
    or eax, 1                   # Set PE bit
    mov cr0, eax

    mov ecx, cr4
    or ecx, 0x20                # Enable PAE
    mov cr4, ecx

    mov eax, 0xc0000080         # MSR for EFER
    rdmsr
    or eax, 0x100               # Enable LME (Long Mode Enable)
    wrmsr

    # Enable paging
    mov eax, cr0
    or eax, 0x80000000          # Set PG bit
    mov cr0, eax

    # Set stack pointer 
    mov rsp, stack_top

    call kernel_init

hang:
    hlt
    jmp hang

.section .data
gdt_descriptor:
    .word gdt_end - gdt - 1
    .quad gdt

.section .bss
    .lcomm stack, 4096
stack_top:
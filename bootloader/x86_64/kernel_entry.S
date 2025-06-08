; Copyright 2025 Bluegill Studios
; All rights reserved under the GNU GPLv2 License.

[bits 64]
[global _start]         

_start:
    ; -----------------------------
    ; Setup segment registers for 64-bit mode
    ; -----------------------------

    mov ax, 0x10         
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; -----------------------------
    ; Setup stack pointer
    ; -----------------------------

    ; 8 MiB stack
    mov rsp, 0x800000

    ; -----------------------------
    ; Clear the base pointer (optional, good practice)
    ; -----------------------------

    xor rbp, rbp

    ; -----------------------------
    ; Call the kernel.
    ; -----------------------------

    extern kernel_main   

    call kernel_main

    ; -----------------------------
    ; If kernel_main returns, halt CPU
    ; -----------------------------

.halt_loop:
    cli                  ; Clear interrupts
    hlt                  ; Halt CPU until next interrupt
    jmp .halt_loop       ; Loop forever
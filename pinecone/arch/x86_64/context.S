.global switch_to
.type switch_to, @function

// rdi = pointer to new context
switch_to:
    // Save current registers to current stack (optional, if preemption is supported)
    mov    0x00(%rdi), %r15
    mov    0x08(%rdi), %r14
    mov    0x10(%rdi), %r13
    mov    0x18(%rdi), %r12
    mov    0x20(%rdi), %r11
    mov    0x28(%rdi), %r10
    mov    0x30(%rdi), %r9
    mov    0x38(%rdi), %r8
    mov    0x40(%rdi), %rsi
    mov    0x48(%rdi), %rdi
    mov    0x50(%rdi), %rbp
    mov    0x58(%rdi), %rdx
    mov    0x60(%rdi), %rcx
    mov    0x68(%rdi), %rbx
    mov    0x70(%rdi), %rax

    mov    0x80(%rdi), %rsp
    jmp    *0x78(%rdi)  // jump to rip

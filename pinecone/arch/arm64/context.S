.global switch_to
.type switch_to, %function

// x0 = pointer to new context
switch_to:
    ldr x19, [x0, #0x00]
    ldr x20, [x0, #0x08]
    ldr x21, [x0, #0x10]
    ldr x22, [x0, #0x18]
    ldr x23, [x0, #0x20]
    ldr x24, [x0, #0x28]
    ldr x25, [x0, #0x30]
    ldr x26, [x0, #0x38]
    ldr x27, [x0, #0x40]
    ldr x28, [x0, #0x48]
    ldr x29, [x0, #0x50]     // frame pointer
    ldr x30, [x0, #0x58]     // return address
    ldr x1,  [x0, #0x60]     // SP
    mov sp, x1
    br x30                   // branch to saved PC

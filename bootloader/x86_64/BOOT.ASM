; Copyright 2025 Bluegill Studios
; All rights reserved under the GNU GPLv2 License.

[bits 16]
[org 0x7c00]

start:
    cli                     ; Disable interrupts

    ; Set up stack
    xor ax, ax
    mov ss, ax
    mov sp, 0x7c00

    ; BIOS loads bootloader at 0x7c00

    mov bx, 0x0000          ; Offset in ES segment
    mov es, 0x1000          ; ES:BX = 0x100000 segment:offset
    mov ah, 0x02            ; BIOS read sectors function
    mov al, 10              ; Number of sectors to read (adjust as needed)
    mov ch, 0               ; Cylinder
    mov cl, 2               ; Start sector (sector 2, since sector 1 is bootloader)
    mov dh, 0               ; Head
    mov dl, [BOOT_DRIVE]    ; Boot drive passed by BIOS in DL

read_kernel:
    int 0x13                ; BIOS disk interrupt
    jc disk_error           ; Jump if carry flag set (error)

    ; Success, proceed to protected mode setup
    jmp setup_pm

disk_error:
    ; Print error and hang
    mov si, disk_error_msg
    call print_string
    jmp $

; ---------------------------
; Protected Mode Setup
; ---------------------------

setup_pm:
    ; Disable interrupts
    cli

    ; Load the GDT.
    lgdt [gdt_descriptor]

    ; Enable A20 line (to access memory > 1MB)
    call enable_a20

    ; Enter protected mode
    mov eax, cr0
    or eax, 1               ; Set PE bit in CR0
    mov cr0, eax

    ; Far jump to clear prefetch queue and load CS selector
    jmp 0x08:protected_mode_entry

; ---------------------------
; Protected Mode code segment
; ---------------------------

[bits 32]
protected_mode_entry:
    ; Set up segment registers
    mov ax, 0x10            ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Setup stack pointer for protected mode
    mov esp, 0x90000

    ; Setup paging for long mode
    call setup_paging

    ; Enable long mode and switch to 64-bit mode
    call enter_long_mode

; ---------------------------
; 64-bit mode entry
; ---------------------------

[bits 64]
long_mode_entry:
    ; Jump to kernel entry point at 0x100000
    mov rsp, 0x80000            ; Set stack pointer in 64-bit mode
    jmp 0x0000000000100000      ; Jump to kernel entry

; ---------------------------------
; Helper functions & data
; ---------------------------------

enable_a20:
    ; Enable A20 line via keyboard controller
    in al, 0x64
.wait_input_ready:
    test al, 0x02
    jnz .wait_input_ready
    mov al, 0xd1
    out 0x64, al
.wait_input2:
    in al, 0x64
    test al, 0x02
    jnz .wait_input2
    mov al, 0xdf
    out 0x60, al
    ret

print_string:
    mov ah, 0x0e
.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char
.done:
    ret

setup_paging:
    ; We will create page tables in memory at 0x9000 - arbitrary free space
    ; Page size 2 MiB for simplicity (using large pages)
    
    ; Addresses
    ; PML4 at 0x9000
    ; PDPT at 0xA000
    ; PD at 0xB000

    ; Clear PML4 (512 entries)
    mov edi, 0x9000
    mov ecx, 512 * 8 / 4       ; Number of DWORDs (512 entries * 8 bytes / 4 bytes per dword)
    xor eax, eax
    rep stosd

    ; Clear PDPT
    mov edi, 0xA000
    mov ecx, 512 * 8 / 4
    xor eax, eax
    rep stosd

    ; Clear PD
    mov edi, 0xB000
    mov ecx, 512 * 8 / 4
    xor eax, eax
    rep stosd

    ; Set PD entry with 2MB page (bit 7 = PS for page size)
    ; Map 0x0 - 1GB identity mapped with 2MB pages (512 * 2MB = 1GB)
    mov eax, 0x00000083       ; Present=1, RW=1, PS=1
    mov edi, 0xB000           ; PD base

    mov ecx, 512              ; 512 entries
    mov ebx, 0                ; page frame address base
    
.pg_loop:
    mov dword [edi], eax      ; entry
    add dword [edi], ebx      ; add address bits (low 21 bits zeroed by PS)
    add edi, 8                ; next entry (64-bit entry, 8 bytes)
    add ebx, 0x200000         ; next 2MB page
    loop .pg_loop

    ; Setup PDPT entry pointing to PD at 0xB000
    mov dword [0xA000], 0xB000 | 0x03    ; Present + RW, address aligned
    mov dword [0xA004], 0x0               ; upper 32 bits zero

    ; Setup PML4 entry pointing to PDPT at 0xA000
    mov dword [0x9000], 0xA000 | 0x03    ; Present + RW
    mov dword [0x9004], 0x0               ; upper 32 bits zero

    ; Load CR3 with PML4 physical address (0x9000)
    mov eax, 0x9000
    mov cr3, eax


enter_long_mode:
    mov eax, cr4
    or eax, 1 << 5       ; Set PAE bit
    mov cr4, eax
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1            
    wrmsr
    mov eax, cr0
    or eax, 1 << 31      ; Set PG bit
    or eax, 1            ; Set PE bit (protected mode already enabled)
    mov cr0, eax

    ; Far jump to 64-bit code segment (selector 0x08)

    ret
; ---------------------------
; Data
; ---------------------------

gdt_start:
    ; Null descriptor
    dq 0x0000000000000000

    ; Code segment descriptor (kernel, executable, readable)
    dq 0x00af9a000000ffff

    ; Data segment descriptor (kernel, writable)
    dq 0x00af92000000ffff

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

disk_error_msg db "Disk read error! Halting...", 0

BOOT_DRIVE db 0       

; ---------------------------
; Boot sector padding and signature
; ---------------------------

times 510 - ($ - $$) db 0
dw 0xAA55
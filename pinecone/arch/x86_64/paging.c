#include "../../include/arch/x86_64.h"
#include <stdint.h>

#define PAGE_PRESENT   (1ULL << 0)
#define PAGE_RW        (1ULL << 1)
#define PAGE_PS        (1ULL << 7)
#define PAGE_SIZE      0x1000

// 4-level paging: PML4 -> PDPT -> PD (with 2MB pages)

__attribute__((aligned(4096))) static uint64_t pml4[512] = {0};
__attribute__((aligned(4096))) static uint64_t pdpt[512] = {0};
__attribute__((aligned(4096))) static uint64_t pd[512] = {0};

void init_paging() {
    // Identity map first 2MB using a single 2MB page
    pd[0] = 0x00000000 | PAGE_PS | PAGE_RW | PAGE_PRESENT;

    pdpt[0] = (uint64_t)pd | PAGE_RW | PAGE_PRESENT;
    pml4[0] = (uint64_t)pdpt | PAGE_RW | PAGE_PRESENT;

    // Load page tables into CR3 to activate them
    asm volatile("mov %0, %%cr3" :: "r"(pml4));

    // Enable paging: this is typically done in assembly (before this function is reached),
    // but if needed here:
    uint64_t cr0, cr4, efer;
    
    asm volatile("mov %%cr4, %0" : "=r"(cr4));
    cr4 |= (1 << 5); // Enable PAE
    asm volatile("mov %0, %%cr4" :: "r"(cr4));

    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= (1 << 31); // Enable paging
    asm volatile("mov %0, %%cr0" :: "r"(cr0));

    // Enable long mode (if not already done by bootloader)
    asm volatile("rdmsr" : "=A"(efer) : "c"(0xC0000080)); // IA32_EFER
    efer |= (1 << 8); // LME
    asm volatile("wrmsr" :: "c"(0xC0000080), "A"(efer));
}

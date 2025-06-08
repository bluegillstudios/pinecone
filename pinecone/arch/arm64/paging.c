#include "../../include/arch/arm64.h"
#include <stdint.h>

#define PAGE_PRESENT    (0b11)      // valid + table
#define BLOCK_DESC      (0b01)      // block descriptor
#define PAGE_DESC       (0b11)      // page descriptor
#define AF              (1 << 10)   // Access flag
#define SH_INNER        (3 << 8)
#define AP_RW           (0 << 6)
#define UXN             (1 << 54)
#define PXN             (1 << 53)

#define PAGE_SIZE       4096
#define MAIR_ATTR       0xFF        // Normal memory
#define TTBR0_EL1_BASE  0x80000     // Kernel load addr

__attribute__((aligned(4096))) static uint64_t l0[512] = {0}; // Level 0 table
__attribute__((aligned(4096))) static uint64_t l1[512] = {0}; // Level 1 table
__attribute__((aligned(4096))) static uint64_t l2[512] = {0}; // Optional L2

void init_paging() {
    // L0: Point to L1
    l0[0] = ((uint64_t)&l1) | PAGE_PRESENT;

    // L1: 1GB block for kernel (flat mapping at TTBR0_EL1_BASE)
    l1[0] = TTBR0_EL1_BASE | AF | SH_INNER | AP_RW | UXN | PXN | BLOCK_DESC;

    // Load translation base into TTBR0_EL1
    asm volatile("dsb ish");
    asm volatile("msr ttbr0_el1, %0" :: "r"(l0));
    asm volatile("msr mair_el1, %0" :: "r"(MAIR_ATTR));
    asm volatile("msr tcr_el1, %0" :: "r"(0x00000000B500352)); // 48-bit VA, 4KB pages
    asm volatile("msr sctlr_el1, %0" :: "r"(0x30D)); // Enable MMU, caches, alignment checks
    asm volatile("isb");
}

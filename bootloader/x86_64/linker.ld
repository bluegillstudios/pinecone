ENTRY(start)
SECTIONS
{
  . = 0x7c00;
  .text :
  {
    *(.text.boot)
    *(.text*)
  }
  .rodata :
  {
    *(.rodata*)
  }
  .data :
  {
    *(.data*)
  }
  .bss :
  {
    *(.bss*)
    *(COMMON)
  }
  . = 0x7dfe;
  SHORT(0xAA55);
}

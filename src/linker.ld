ENTRY(start)

PHDRS
{
    text PT_LOAD FLAGS(5);   /* R + X */
    data PT_LOAD FLAGS(6);   /* R + W */
}

SECTIONS
{
    . = 1M;

    .text : {
        *(.multiboot_header)
        *(.text*)
        *(.rodata*)
    } :text

    .data : {
        *(.data*)
    } :data

    .bss : {
        *(COMMON)
        *(.bss*)
    } :data
}
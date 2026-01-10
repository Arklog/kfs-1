bits 32
default rel

section .multiboot_header
align 4

multiboot_header:
    dd 0x1BADB002            ; magic number
    dd 0x00                  ; flags
    dd - (0x1BADB002 + 0x00) ; checksum (should be 0)


section .text

global start
extern k_main

start:
    cli
    mov esp, stack_top
    call k_main
    hlt

section .bss
align 16

stack_bottom:
    resb 1000000
stack_top:
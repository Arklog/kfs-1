//
// Created by alice on 09/01/2026.
//

#include "port.hpp"

uint8_t inb(uint16_t port) {
#ifdef KFS_HOST_TEST
    return 0;
#else
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
#endif
}

void outb(uint16_t port, uint8_t val) {
#ifdef KFS_HOST_TEST
    return ;
#else
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
#endif
}

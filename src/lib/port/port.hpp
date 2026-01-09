//
// Created by alice on 09/01/2026.
//

#ifndef KFS_1_PORT_HPP
#define KFS_1_PORT_HPP

#include "include/stdint.hpp"

uint8_t inb(uint16_t port);

void outb(uint16_t port, uint8_t val);

#endif // KFS_1_PORT_HPP

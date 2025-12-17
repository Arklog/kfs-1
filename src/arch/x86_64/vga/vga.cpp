//
// Created by pierre on 12/17/25.
//
#include "vga.hpp"

kernel::vga::t_vga_char kernel::vga::vga_get_color(uint8_t character, color::vga_color fg, color::vga_color bg) {
    t_vga_char vga_char;

    vga_char.data.ascii = character;
    vga_char.data.color = (bg << 4) | (fg & 0x0F);

    return vga_char;
}

void kernel::vga::vga_print_char(t_vga_char character) {

}

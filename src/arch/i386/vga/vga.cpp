//
// Created by pierre on 12/17/25.
//
#include "vga.hpp"

uint8_t vga::t_vga_char::get_foreground() const {
    return data.color & 0x0F;
}

uint8_t vga::t_vga_char::get_background() const {
    return (data.color >> 4) & 0x0F;
}

void vga::t_vga_char::set_foreground(color::t_vga_color color) {
    data.color = (data.color & 0xF0) | (color & 0x0F);
}

void vga::t_vga_char::set_background(color::t_vga_color color) {
    data.color = (color << 4) | (data.color & 0x0F);
}

void vga::t_vga_char::set_color(color::t_vga_color foreground, color::t_vga_color background) {
    data.color = (background << 4) | (foreground & 0x0F);
}

vga::t_vga_char vga::vga_get_color(uint8_t character, color::vga_color fg, color::vga_color bg) {
    t_vga_char vga_char;

    vga_char.data.ascii = character;
    vga_char.data.color = (bg << 4) | (fg & 0x0F);

    return vga_char;
}

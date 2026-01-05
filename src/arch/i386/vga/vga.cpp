//
// Created by pierre on 12/17/25.
//
#include "vga.hpp"

vga::t_vga_char vga::make_vga_char(const uint8_t character, const color::vga_color fg, const color::vga_color bg) {
    const t_vga_char vga_char{
            .raw = static_cast<uint16_t>(character | bg << 12 | (fg & 0x0F) << 8),
    };

    return vga_char;
}
vga::color::t_vga_color vga::t_vga_char::get_foreground() const {
    return static_cast<color::t_vga_color>(data.color & 0x0F);
}

vga::color::t_vga_color vga::t_vga_char::get_background() const {
    return static_cast<color::t_vga_color>((data.color >> 4) & 0x0F);
}

void vga::t_vga_char::set_foreground(const color::t_vga_color color) {
    data.color = (data.color & 0xF0) | (color & 0x0F);
}

void vga::t_vga_char::set_background(const color::t_vga_color color) {
    data.color = (color << 4) | (data.color & 0x0F);
}

void vga::t_vga_char::set_color(const color::t_vga_color foreground, const color::t_vga_color background) {
    data.color = (background << 4) | (foreground & 0x0F);
}

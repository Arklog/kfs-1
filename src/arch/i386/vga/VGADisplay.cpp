//
// Created by alice on 21/12/2025.
//

#include "VGADisplay.hpp"

namespace vga {
    bool VGADisplay::testing = false;
    volatile t_vga_char *VGADisplay::vga = reinterpret_cast<volatile t_vga_char *>(0xB8000);

    void VGADisplay::clear() {
        for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
            vga[i].raw = vga::t_vga_char(' ', vga::color::WHITE).raw;
        }
    }

    void VGADisplay::render(const ScrollbackBuffer &buffer, uint32_t view_line) {
        uint8_t color = color::color_set::WHITE_ON_BLACK;
        for (uint32_t row = 0; row < VGA_HEIGHT; ++row) {
            uint32_t src_line = view_line + row;

            uint16_t len = 0;
            if (src_line < buffer.line_count())
                len = buffer.line_length(src_line);

            for (uint16_t col = 0; col < VGA_WIDTH; ++col) {
                if (src_line < buffer.line_count() && col < len) {
                    vga[row * VGA_WIDTH + col].raw = buffer.line(src_line)[col].raw;
                    color = buffer.line(src_line)[col].get_color();
                } else {
                    vga[row * VGA_WIDTH + col].raw = vga::t_vga_char(' ', color).raw;
                }
            }
        }
    }


    void VGADisplay::update_hw_cursor(const VGACursor &cursor, uint32_t view_line) {
        if (testing == true)
            return;

        if (cursor.line < view_line || cursor.line >= view_line + VGA_HEIGHT)
            return;

        uint16_t pos = (cursor.line - view_line) * VGA_WIDTH + cursor.column;

        outb(0x3D4, 0x0F);
        outb(0x3D5, pos & 0xFF);
        outb(0x3D4, 0x0E);
        outb(0x3D5, (pos >> 8) & 0xFF);
    }

}

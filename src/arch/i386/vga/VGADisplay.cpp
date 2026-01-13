//
// Created by alice on 21/12/2025.
//

#include "VGADisplay.hpp"

#include "lib/container/range.hpp"
#include "lib/math/math.hpp"

namespace vga {
    bool VGADisplay::testing = false;
    volatile t_vga_char *VGADisplay::vga = reinterpret_cast<volatile t_vga_char *>(0xB8000);

    void VGADisplay::clear() {
        for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
            vga[i].raw = vga::t_vga_char(' ', vga::color::color_set::WHITE_ON_BLACK).raw;
        }
    }

    void VGADisplay::render(const ScrollbackBuffer &buffer, uint32_t view_line) {
        auto &raw_buff = buffer.get_buffer();
        auto begin_iter = raw_buff.begin() + view_line - 1;
        auto end_iter = math::min(raw_buff.end(), begin_iter + VGA_HEIGHT);

        if (begin_iter >= end_iter)
            return ;

        int line_idx = 0;
        for (const auto &line: container::range{begin_iter, end_iter}) {
            auto cpy_size = line.size() * sizeof(t_vga_char);
            auto dest = vga + line_idx * VGA_WIDTH;
            kstring::memcpy((void *) dest, line.data(), cpy_size);
            ++line_idx;
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

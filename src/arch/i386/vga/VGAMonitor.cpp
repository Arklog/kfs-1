//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "vga.hpp"

# define VGA_ADDRESS 0xB8000
# define VGA_WIDTH 80
# define VGA_HEIGHT 25

namespace vga {
    VGAMonitor::VGAMonitor() = default;

    VGAMonitor & VGAMonitor::operator<<(const char *data) {
        auto cur = cursor.pos();

        while (*data) {
            auto character = vga_get_color(*(data++));
            auto [raw_char, raw_color] = character.data;

            if (raw_char == '\n') {
                cur += VGA_WIDTH - (cursor.ipos() % VGA_WIDTH);
            } else {
                *(cur++) = character;
            }
        }
        return *this;
    }
}

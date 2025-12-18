//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "vga.hpp"
#include "VGAStreamModifier.hpp"

# define VGA_ADDRESS 0xB8000

namespace vga {
    void VGAMonitor::print_char(const t_vga_char &c) {
        auto cur = cursor.pos();
        auto [raw_char, raw_color] = c.data;

        // process the character
        if (raw_char == '\n') {
            cursor.next_line();
        } else {
            cursor.set_char(c);
            ++(*cur);
        }
    }

    VGAMonitor::VGAMonitor() = default;

    VGAMonitor & VGAMonitor::operator<<(const char *data) {
        while (*data) {
            // Get the VGA character with the current color and print
            auto character = vga_get_color(*(data++));
            print_char(character);
        }

        return *this;
    }

    VGAMonitor & VGAMonitor::operator<<(const VGAStreamModifier &modifier) {
        modifier(cursor);
        return *this;
    }
}

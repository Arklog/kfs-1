//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "vga.hpp"

# define VGA_ADDRESS 0xB8000

namespace vga {
    void VGAMonitor::_print_char(const t_vga_char &c) {
        auto cur = cursor.pos();

        auto [raw_char, raw_color] = c.data;
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
            auto character = vga_get_color(*(data++));
            _print_char(character);
        }

        return *this;
    }

    VGAMonitor & VGAMonitor::operator<<(const t_vga_char c) {
        _print_char(c);

        return *this;
    }
}

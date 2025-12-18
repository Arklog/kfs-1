//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "vga.hpp"

# define VGA_ADDRESS 0xB8000

namespace vga {
    const uint16_t *VGAMonitor::_beg = reinterpret_cast<const uint16_t *>(VGA_ADDRESS);
    uint16_t *VGAMonitor::_pos = reinterpret_cast<uint16_t *>(VGA_ADDRESS);

    VGAMonitor::VGAMonitor() = default;

    VGAMonitor & VGAMonitor::operator<<(const char *data) {
        while (*data) {
            auto character = vga_get_color(*(data++));
            *_pos++ = character.raw;
        }
        return *this;
    }
}

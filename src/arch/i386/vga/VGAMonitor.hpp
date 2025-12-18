//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGAMONITOR_HPP
#define KFS_1_VGAMONITOR_HPP

#include "include/stdint.hpp"
#include "VGACursor.hpp"

namespace vga {
    class VGAStreamModifier;

    class VGAMonitor {
    private:
        VGACursor cursor;

        void _print_char(const t_vga_char& c);

    public:
        VGAMonitor();

        VGAMonitor& operator<<(const char *data);

        VGAMonitor& operator<<(const VGAStreamModifier& modifier);
    };
}

#endif //KFS_1_VGAMONITOR_HPP

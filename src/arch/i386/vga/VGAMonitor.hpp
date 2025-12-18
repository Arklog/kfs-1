//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGAMONITOR_HPP
#define KFS_1_VGAMONITOR_HPP

#include "include/stdint.hpp"
#include "VGACursor.hpp"

namespace vga {
    class VGAMonitor {
    private:
        VGACursor cursor;

    public:
        VGAMonitor();

        VGAMonitor& operator<<(const char *data);
    };
}

#endif //KFS_1_VGAMONITOR_HPP

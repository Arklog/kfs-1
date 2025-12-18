//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGAMONITOR_HPP
#define KFS_1_VGAMONITOR_HPP

#include "include/stdint.hpp"

namespace vga {
    class VGAMonitor {
    private:
        static const uint16_t *_beg;
        static uint16_t *_pos;

    public:
        VGAMonitor();

        VGAMonitor& operator<<(const char *data);
    };
}

#endif //KFS_1_VGAMONITOR_HPP

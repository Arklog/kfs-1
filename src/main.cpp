//
// Created by pierre on 12/17/25.
//

#include "arch/i386/vga/VGAMonitor.hpp"

extern "C" void k_main() {
    vga::VGAMonitor monitor{};

    monitor << "Hello, World!\n" << "t\n\n ttt";

    while (true) {
    }
}

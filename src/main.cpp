//
// Created by pierre on 12/17/25.
//

#include "arch/x86_64/vga/VGAMonitor.hpp"

extern "C" void k_main() {
    kernel::vga::VGAMonitor monitor{};

    monitor << "Hello, World!";

    while (true) {
    }
}

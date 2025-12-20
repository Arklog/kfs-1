//
// Created by pierre on 12/17/25.
//

#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGAStreamModifier.hpp"

extern "C" void k_main() {
    vga::VGAMonitor monitor{};

    monitor << "Hello, World!" << vga::endl;
    monitor << "test" << vga::endl;

    while (true) {}

    monitor << vga::modifier::VGASetLineModifier{10}
            << vga::modifier::VGAStreamColorModifier{vga::color::GREEN, vga::color::RED}
            << "This text is on line 10" << vga::endl;

    while (true) {
    }
}

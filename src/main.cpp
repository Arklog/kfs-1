//
// Created by pierre on 12/17/25.
//


#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/keyboard/keyboardHandler.hpp"
#include "lib/logging/logging.hpp"

extern "C" void k_main() {
    vga::VGAMonitor  monitor{};
    g_monitor = &monitor;

    monitor.init();

    char first_line[81] = "first first first first first first first first first first first first first   ";

    char test_line[81] = "test test test test test test test test test test test test test test test test ";

    monitor << first_line << test_line;
    while (true) {
        kbd::handler();
    }
}

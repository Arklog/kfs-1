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
    monitor << "test";


    logging::set_logger(monitor);
    logging::info("logging initialized");

    while (true) {
        kbd::handler();
    }
}

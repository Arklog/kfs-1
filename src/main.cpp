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
    logging::set_logger(monitor);
    logging::info("logging initialized");
    monitor << "test" << vga::color::color_set::BLACK_ON_WHITE << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << "test" << vga::endl;
    monitor << vga::endl << vga::endl << vga::endl<< vga::endl;

    while (true) {
        kbd::handler();
    }
}

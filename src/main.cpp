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

    monitor << "test0" << "test1" << "test2" << "test3" << "test4" << "test5" << "test6" << "test7" << "test8" << "test9" << "tes10" << "tes11" << "tes12" << "tes13" << "tes14" << "tes15" << "tes16" << "tes17";
    monitor << "test2" << vga::endl;
    monitor << "test3" << vga::endl;
    monitor << "test4" << vga::endl;
    monitor << "test5" << vga::endl;
    monitor << "test6" << vga::endl;
    monitor << "test7" << vga::endl;
    monitor << "test8" << vga::endl;
    monitor << "test9" << vga::endl;
    monitor << "test10" << vga::endl;
    monitor << "test11" << vga::endl;
    monitor << "test12" << vga::endl;
    monitor << "test13" << vga::endl;
    monitor << "test14" << vga::endl;
    monitor << "test15" << vga::endl;
    monitor << "test16" << vga::endl;
    monitor << "test17" << vga::endl;
    monitor << "test18" << vga::endl;
    monitor << "test19" << vga::endl;
    monitor << "test20" << vga::endl;
    monitor << "test21" << vga::endl;
    monitor << "test22" << vga::endl;
    monitor << "test23" << vga::endl;
    monitor << "test24" << vga::endl;

    while (true) {
        kbd::handler();
    }
}

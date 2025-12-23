//
// Created by pierre on 12/17/25.
//

#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGAStreamModifier.hpp"
#include "lib/logging/logging.hpp"

extern "C" void k_main() {
    vga::VGAMonitor monitor{};

    const char *bpad = "                         ";
    const char *apad = "                          ";
    monitor << vga::modifier::VGAStreamColorModifier(vga::color::BLACK_ON_WHITE)
            << bpad << " /$$   /$$ /$$$$$$$$ /$$$$$$ " << apad
            << bpad << "| $$  /$$/| $$_____//$$__  $$" << apad
            << bpad << "| $$ /$$/ | $$     | $$  \\__/" << apad
            << bpad << "| $$$$$/  | $$$$$  |  $$$$$$ " << apad
            << bpad << "| $$  $$  | $$__/   \\____  $$" << apad
            << bpad << "| $$\\  $$ | $$      /$$  \\ $$" << apad
            << bpad << "| $$ \\  $$| $$     |  $$$$$$/" << apad
            << bpad << "|__/  \\__/|__/      \\______/ " << apad;

    // reset default color
    monitor << vga::modifier::VGAStreamColorModifier(vga::color::WHITE_ON_BLACK);

    monitor << vga::endl
            << "CHECKING COLORS"
            << vga::endl;

    for (int i = vga::color::BLACK; i <= vga::color::WHITE; i++) {
        monitor << vga::modifier::VGAStreamBackgroundModifier(i) << " ";
    }

    monitor << vga::modifier::VGAStreamColorModifier(vga::color::WHITE_ON_BLACK) << vga::endl;

    logging::set_logger(monitor);
    logging::info("logging initialized");

    while (true) {
    }
}

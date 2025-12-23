//
// Created by pierre on 12/17/25.
//


#include "arch/i386/vga/vga.hpp"
#include "arch/i386/vga/VGAMonitor.hpp"
#include "arch/i386/vga/VGAStreamModifier.hpp"
#include "arch/i386/keyboard/keyboardHandler.hpp"

vga::VGAMonitor g_monitor;


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
    g_monitor << "Hello, World! Hello 42!" << vga::endl;
    g_monitor << "Hello, World! Hello 1!" << vga::endl;
    g_monitor << "Hello, World! Hello 2!" << vga::endl;
    g_monitor << "Hello, World! Hello 3!" << vga::endl;
    g_monitor << "Hello, World! Hello 4!" << vga::endl;
    g_monitor << "Hello, World! Hello 5!" << vga::endl;
    g_monitor << "Hello, World! Hello 6!" << vga::endl;
    g_monitor << "Hello, World! Hello 7!" << vga::endl;
    g_monitor << "Hello, World! Hello 8!" << vga::endl;
    g_monitor << "Hello, World! Hello 9!" << vga::endl;
    g_monitor << "Hello, World! Hello 10!" << vga::endl;
    g_monitor << "Hello, World! Hello 11!" << vga::endl;
    g_monitor << "Hello, World! Hello 12!" << vga::endl;
    g_monitor << "Hello, World! Hello 13!" << vga::endl;
    g_monitor << "Hello, World! Hello 14!" << vga::endl;
    g_monitor << "Hello, World! Hello 15!" << vga::endl;
    g_monitor << "Hello, World! Hello 16!" << vga::endl;
    g_monitor << "Hello, World! Hello 17!" << vga::endl;
    g_monitor << "Hello, World! Hello 18!" << vga::endl;
    g_monitor << "Hello, World! Hello 19!" << vga::endl;
    g_monitor << "Hello, World! Hello 21!" << vga::endl;
    g_monitor << "Hello, World! Hello 22!" << vga::endl;
    g_monitor << "Hello, World! Hello 23!" << vga::endl;
    g_monitor << "Hello, World! Hello 24!" << vga::endl;
    g_monitor << "Hello, World! Hello 25!" << vga::endl;
    g_monitor << "Hello, World! Hello 26!" << vga::endl;
    g_monitor << "Hello, World! Hello 27!" << vga::endl;
    g_monitor << "Hello, World! Hello 28!" << vga::endl;
    g_monitor << "Hello, World! Hello 29!" << vga::endl;
    g_monitor << "Hello, World! Hello 30!" << vga::endl;
    g_monitor << "Hello, World! Hello 31!" << vga::endl;
    g_monitor << "Hello, World! Hello 32!" << vga::endl;
    g_monitor << "Hello, World! Hello 33!" << vga::endl;
    g_monitor << "Hello, World! Hello 34!" << vga::endl;
    g_monitor << "Hello, World! Hello 35!" << vga::endl;
    g_monitor << "Hello, World! Hello 36!" << vga::endl;
    g_monitor << "Hello, World! Hello 37!" << vga::endl;
    g_monitor << "Hello, World! Hello 38!" << vga::endl;
    g_monitor << "Hello, World! Hello 39!" << vga::endl;
    g_monitor << "Hello, World! Hello 40!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;
    g_monitor << "Hello, World!" << vga::endl;

    while (true) {
        kbd::handler();
    }
}

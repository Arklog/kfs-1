//
// Created by alice on 21/12/2025.
//

#ifndef KFS_1_KEYBOARDHANDLER_HPP
#define KFS_1_KEYBOARDHANDLER_HPP

#include "include/stdint.hpp"
#include "../vga/VGAMonitor.hpp"

extern vga::VGAMonitor g_monitor;

namespace kbd {
    static constexpr uint16_t keyboard_data_port = 0x60;

    struct KeyMapping {
        uint8_t scancode;
        uint8_t normal;
        uint8_t shifted;
    };

    constexpr uint8_t up        = 128;
    constexpr uint8_t down      = 129;
    constexpr uint8_t left      = 130;
    constexpr uint8_t right     = 131;
    constexpr uint8_t ctrl      = 132;
    constexpr uint8_t alt       = 133;
    constexpr uint8_t lshift    = 134;
    constexpr uint8_t rshift    = 135;
    constexpr uint8_t capslock  = 136;
    constexpr uint8_t backspace = 137;


    constexpr KeyMapping keymap[] = {
        {0x01, 27, 27},
        {0x02, '1', '!'},
        {0x03, '2', '@'},
        {0x04, '3', '#'},
        {0x05, '4', '$'},
        {0x06, '5', '%'},
        {0x07, '6', '^'},
        {0x08, '7', '&'},
        {0x09, '8', '*'},
        {0x0A, '9', '('},
        {0x0B, '0', ')'},
        {0x0C, '-', '_'},
        {0x0D, '=', '+'},
        {0x0E, '\b', '\b'},
        {0x0F, '\t', '\t'},
        {0x10, 'q', 'Q'},
        {0x11, 'w', 'W'},
        {0x12, 'e', 'E'},
        {0x13, 'r', 'R'},
        {0x14, 't', 'T'},
        {0x15, 'y', 'Y'},
        {0x16, 'u', 'U'},
        {0x17, 'i', 'I'},
        {0x18, 'o', 'O'},
        {0x19, 'p', 'P'},
        {0x1A, '[', '{'},
        {0x1B, ']', '}'},
        {0x1C, '\n', '\n'},
        {0x1E, 'a', 'A'},
        {0x1F, 's', 'S'},
        {0x20, 'd', 'D'},
        {0x21, 'f', 'F'},
        {0x22, 'g', 'G'},
        {0x23, 'h', 'H'},
        {0x24, 'j', 'J'},
        {0x25, 'k', 'K'},
        {0x26, 'l', 'L'},
        {0x27, ';', ':'},
        {0x28, '\'', '"'},
        {0x29, '`', '~'},
        {0x2B, '\\', '|'},
        {0x2C, 'z', 'Z'},
        {0x2D, 'x', 'X'},
        {0x2E, 'c', 'C'},
        {0x2F, 'v', 'V'},
        {0x30, 'b', 'B'},
        {0x31, 'n', 'N'},
        {0x32, 'm', 'M'},
        {0x33, ',', '<'},
        {0x34, '.', '>'},
        {0x35, '/', '?'},
        {0x39, ' ', ' '},
        // Arrow
        {0x48, up, up},              // Up arrow
        {0x50, down, down},          // Down arrow
        {0x4B, left, left},          // Left arrow
        {0x4D, right, right},        // Right arrow
        // Ctrl, alt, shift...
        {0x3A, capslock, capslock},  // CapsLock
        {0x1D, ctrl, ctrl},          // LCtrl
        {0x38, alt, alt},            // LAlt
        {0x36, rshift, rshift},      // RShift
        {0x2A, lshift, lshift},      // LShift
    };

    inline bool keyboard[138] = {false};
    void handler();
};


#endif //KFS_1_KEYBOARDHANDLER_HPP
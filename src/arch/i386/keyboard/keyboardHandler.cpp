//
// Created by alice on 21/12/2025.
//

#include "keyboardHandler.hpp"

namespace kbd {

    void handler() {
        uint8_t scancode = inb(keyboard_data_port);
        bool released = scancode & 0x80;
        uint8_t code = scancode & 0x7F;
        for (const KeyMapping& k : keymap) {
            if (k.scancode != code)
                continue;

            uint8_t value = keyboard[lshift] ? k.shifted : k.normal;

            if (value == lshift || value == rshift) {
                keyboard[value] = !released;
                return;
            }

            if (released) {
                keyboard[value] = false;
                return;
            }

            if (value == up && !keyboard[up]) {
                g_monitor.scroll_up();
                keyboard[up] = true;
                return;
            }

            if (value == down && !keyboard[down]) {
                g_monitor.scroll_down();
                keyboard[down] = true;
                return;
            }

            if (value == left && !keyboard[left]) {
                g_monitor.move_left();
                keyboard[left] = true;
                return;
            }

            if (value == right && !keyboard[right]) {
                g_monitor.move_right();
                keyboard[right] = true;
                return;
            }

            if (((value >= 32 && value <= 126) || value == '\n') && !keyboard[value]) {
                g_monitor << (char)value;
                keyboard[value] = true;
                return;
            }

            if (value == '\b' && !keyboard['\b']) {
                g_monitor.backspace();
                keyboard['\b'] = true;
            }
        }
    }
}
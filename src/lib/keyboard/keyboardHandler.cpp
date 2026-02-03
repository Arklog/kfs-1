//
// Created by alice on 21/12/2025.
//

#include "keyboardHandler.hpp"
#include "lib/logging/logging.hpp"

inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

vga::VGAMonitor *g_monitor = nullptr;

namespace kbd {

    void handler(screen_container_type &monitors, screen_container_iterator_type &current_screen_iter) {
        auto &monitor = *g_monitor;

        uint8_t scancode = inb(keyboard_data_port);    // PS/2 code
        bool    released = scancode & 0x80;                 // is the key released
        uint8_t code     = scancode & 0x7F;                 // code value

        for (const KeyMapping &k: keymap) {
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
                monitor.scroll_up();
                keyboard[up] = true;
                return;
            }

            if (value == down && !keyboard[down]) {
                monitor.scroll_down();
                keyboard[down] = true;
                return;
            }

            if (value == left && !keyboard[left]) {
                monitor.move_left();
                keyboard[left] = true;
                return;
            }

            if (value == right && !keyboard[right]) {
                monitor.move_right();
                keyboard[right] = true;
                return;
            }

            if (((value >= 32 && value <= 126) || value == '\n') && !keyboard[value]) {
                monitor.handle_user_input((char) value);
                keyboard[value] = true;
                return;
            }

            if (value == '\b' && !keyboard['\b']) {
                monitor.handle_user_input('\b');
                keyboard['\b'] = true;
            }

            // if ctrl pressed we rotate monitor
            if (value == ctrl && !keyboard[ctrl]) {
                keyboard[ctrl] = true;
                ++current_screen_iter;
                if (current_screen_iter == monitors.end())
                    current_screen_iter = monitors.begin();
                g_monitor = &(*current_screen_iter);
                logging::set_logger(*current_screen_iter);
                logging::debug("switched to screen {}", current_screen_iter - monitors.begin());
                vga::VGADisplay::render_page(g_monitor->get_page());
            }
        }
    }
}
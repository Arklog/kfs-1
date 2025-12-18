//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGAMONITOR_HPP
#define KFS_1_VGAMONITOR_HPP

#include "include/stdint.hpp"
#include "VGACursor.hpp"

namespace vga {
    class VGAStreamModifier;

    /**
     * Stream like interface to the VGA text mode monitor.
     */
    class VGAMonitor {
    private:
        VGACursor cursor;

        /**
         * Print a character at the current cursor position, and advance the cursor.
         * @param c The character to print.
         */
        void print_char(const t_vga_char& c);

    public:
        VGAMonitor();

        /**
         * Print a null-terminated string at the current cursor position. The cursor is advanced accordingly.
         *
         * @param data
         * @return
         */
        VGAMonitor& operator<<(const char *data);

        /**
         * Process a stream modifier (like newline, color change, etc.)
         *
         * @param modifier A functor that modifies the cursor state.
         * @return
         */
        VGAMonitor& operator<<(const VGAStreamModifier& modifier);
    };
}

#endif //KFS_1_VGAMONITOR_HPP

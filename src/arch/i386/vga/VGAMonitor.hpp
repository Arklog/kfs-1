//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGAMONITOR_HPP
#define KFS_1_VGAMONITOR_HPP

#include "vga.hpp"
#include "include/stdint.hpp"
#include "VGACursor.hpp"
#include "ScrollbackBuffer.hpp"
#include "VGADisplay.hpp"

namespace vga {
    /**
     * High-level terminal interface. Coordinates the buffer, cursor and display logics.
     */
    class VGAMonitor {
    public:
        VGAMonitor();

        /**
         * clears the screen and the buffer.
         */
        void clear();

        /**
         * writes a single character on the terminal.
         * @param c
         */
        void put_char(const char c);

        /**
         * writes a string on the terminal.
         * @param str
         */
        void write(const char* str);

        /**
         * scrolls the visible window up by one line.
         */
        void scroll_up();

        /**
         * scrolls the visible window down by one line.
         */
        void scroll_down();

        /**
         * moves the cursor of 1 column to the left.
         */
        void move_left();

        /**
         * moves the cursor of 1 column to the right.
         */
        void move_right();

        /**
         * performs a backspace operation.
         */
        void backspace();

        /**
         * Stream insertion operator for a string.
         * @param str
         */
        VGAMonitor &operator<<(const char *str);

        /**
         * Stream insertion operator for a single character.
         * @param str
         */
        VGAMonitor &operator<<(const char str);

    private:
        ScrollbackBuffer _buffer;
        VGACursor        _cursor;

        uint32_t _view_line;

        /**
         * refreshes the VGA display and cursor.
         */
        void _refresh();
    };

}

#endif //KFS_1_VGAMONITOR_HPP

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
        VGAMonitor(const VGAMonitor&) = default;
        VGAMonitor& operator=(const VGAMonitor&) = default;

        /**
         * clears the screen and the buffer.
         */
        void clear();

        /**
         * ensure the good global monitor initialization.
         */
        void init(uint8_t id);

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
         * changes foreground color.
         */
        void set_fg_color(color::vga_color fg);

        /**
         * changes background color.
         */
        void set_bg_color(color::vga_color bg);

        /**
         * changes both foreground and background colors.
         */
        void set_colors(color::vga_color fg, color::vga_color bg);

        /**
         * Get the vga page number this monitor displays on
         * @return
         */
        unsigned int get_page() const;

        /**
         * Sets the user imput limit at the given position.
         */
        void set_user_input_limit();

        /**
         * checks if the user changes are in the allowed area. Perfoms them if yes, do nothing else.
         */
        void handle_user_input(char inp);

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

        /**
         * Stream foreground color modifier operator.
         */
        VGAMonitor &operator<<(const color::vga_color fg);

        /**
         * Stream colors modifier operator.
         */
        VGAMonitor &operator<<(const VGAColorChange changer);

        /**
         * Stream colors modifier operator via t_color_set.
         */
        VGAMonitor &operator<<(const uint8_t changer);

        ScrollbackBuffer       _buffer;
        VGACursor              _cursor_write;
        VGACursor              _user_cursor;


    private:
        uint8_t                _color;
        uint32_t               _view_line;
        uint32_t               _lim_line;
        uint32_t               _lim_column;
        uint8_t                _page_idx;

        /**
         * refreshes the VGA display and cursor.
         */
        void       _refresh();
        /**
        * syncronizes user cursor and writting cursor. 
         */
        void sync_cursors();


    };

}

#endif //KFS_1_VGAMONITOR_HPP

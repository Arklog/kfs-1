//
// Created by alice on 21/12/2025.
//

#ifndef KFS_1_SCROLLBACKBUFFER_HPP
#define KFS_1_SCROLLBACKBUFFER_HPP

#include "lib/container/StackVector.hpp"
#include "VGACursor.hpp"
#include "vga.hpp"
#include "include/stdint.hpp"
#include "lib/str/KString.hpp"

namespace vga {
    /**
     * Logical buffer storing all written lines, currently visible or not. Lines has here a
     * logical length which can be different of this actual displayed length.
     * This class is responsible for all text modifications.
     */
    class ScrollbackBuffer {
    public:
        static constexpr uint32_t MAX_LINES = 300;
        static constexpr t_vga_char default_char{' ', color::color_set::WHITE_ON_BLACK};

        using line_type = container::StackVector<t_vga_char, vga::VGA_WIDTH>;
        using buffer_type = container::StackVector<line_type, MAX_LINES>;

        ScrollbackBuffer();

        /**
         * clears the entire buffer.
         */
        void clear();

        /**
         * writes a character at the current cursor position.
         * @param cursor
         * @param c
         */
        void write(const VGACursor &cursor, const t_vga_char &c);

        /**
         * erases the character present at the current cursor position.
         * @param cursor
         */
        void erase(const VGACursor &cursor);

        /**
         * Create a new line below the given line, characters after column are moved to the new line.
         *
         * @param line index of the new line.
         * @param column index of the column where to split the line.
        */
        void newline(uint32_t line, uint16_t column);

        /**
         * merges lines when backspace is pressed at column 0.
         * @param dst destination index line.
         * @param src source index line (can be removed).
         */
        void merge_lines(uint32_t dst, uint32_t src);

        /**
         * removes the character at the current cursor position.
         * @param line_idx current line of the cursor
         * @param col current col of the cursor
         */
        void backspace(uint32_t line_idx, uint16_t col);

        /**
         * returns a pointer to the first line's character of the given index.
         * @param index
         */
        const line_type& line(uint32_t index) const;

        /**
         * returns the logical length of the given line.
         * @param index
         */
        uint16_t line_length(uint32_t index) const;

        /**
         * returns the number of logical lines within the buffer.
         */
        uint32_t line_count() const;

        /**
         * scrolls the buffer up when the maximum line is reached (erasing the first one).
         */
        void scroll_up();

        const buffer_type &get_buffer() const {
            return _buffer;
        }

    private:
        /** Character storage for each line. */
        buffer_type _buffer;
    };

}


#endif //KFS_1_SCROLLBACKBUFFER_HPP
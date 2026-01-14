//
// Created by pierre on 12/18/25.
//

#ifndef KFS_1_VGACURSOR_HPP
#define KFS_1_VGACURSOR_HPP
#include "include/stdint.hpp"

namespace vga {
    /**
     * Purely logical cursor defined by its position (line and column index within the ScrollbackBuffer).
     */
    class VGACursor {
    public:
        uint32_t line;
        uint16_t column;

        VGACursor();

        /**
         * advance the cursor of exactly one column within the current line if it's not at end of line, or moves it forward on the next line otherwise.
         */
        void advance(int line_len, int last_line);

        /**
         * get the cursor back of exactly one column within the current line if it's not at beginning of line, or moves it backward on the prevline line otherwise.
         */
        void back(int prev_line_len);

        /**
         * get the cursor up of exactly one line. If the current column index is superior of the previous line length, it takes its length as new value.
         */
        void up(int prev_line_len);

        /**
         * get the cursor down of exactly one line. If the current column index is superior of the next line length, it takes its length as new value.
         */
        void down(int next_line_len, int last_line);


        /**
         * get down the cursor at the beginning of the next line.
         */
        void newline();

        /**
         * set the cursor position at the precise specified indexes.
         * @param l line index
         * @param c column index
         */
        void set(uint32_t l, uint16_t c);
    };

}
#endif //KFS_1_VGACURSOR_HPP
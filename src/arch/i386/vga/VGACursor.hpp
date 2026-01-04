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
         * advance the cursor of exactly one column within the current line.
         */
        void advance();

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
//
// Created by pierre on 12/18/25.
//

#include "VGACursor.hpp"
#include "vga.hpp"

namespace vga {

    VGACursor::VGACursor(): line(0), column(0) {}

    void VGACursor::advance(int line_len) {
        ++column;
        if (column >= VGA_WIDTH || (line_len > 0 && column > line_len)) {
            column = 0;
            ++line;
        }
    }

    void VGACursor::back(int prev_line_len) {
        if (column > 0) {
            --column;
        } else if (line > 0) {
            --line;
            column = prev_line_len;
        }
    }

    void VGACursor::up(int prev_line_len) {
        if (line == 0)
            return;
        --line;
        if (column > prev_line_len)
            column = prev_line_len;
    }

    void VGACursor::down(int next_line_len) {
        ++line;
        if (column > next_line_len)
            column = next_line_len;
    }

    void VGACursor::newline() {
        column = 0;
        ++line;
    }

    void VGACursor::set(uint32_t l, uint16_t c) {
        line = l;
        column = c;
    }

}
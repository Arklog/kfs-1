//
// Created by pierre on 12/18/25.
//

#include "VGACursor.hpp"
#include "vga.hpp"

namespace vga {

    VGACursor::VGACursor(): line(0), column(0) {}

    void VGACursor::advance() {
        ++column;
        if (column >= VGA_WIDTH) {
            column = 0;
            ++line;
        }
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
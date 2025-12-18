//
// Created by pierre on 12/18/25.
//

#include "VGAStreamModifier.hpp"

#include "VGACursor.hpp"

void operator delete(void *) {
}

void operator delete(void *, long unsigned int) {
}

namespace vga {
    VGASetLineModifier::VGASetLineModifier(uint16_t line): VGAStreamModifier(), _line{line} {
    }

    void VGASetLineModifier::operator()(VGACursor &cursor) const {
        cursor.set_line(_line);
    }
} // vga
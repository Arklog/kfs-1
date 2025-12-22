//
// Created by pierre on 12/18/25.
//

#include "VGAStreamModifier.hpp"
#include "VGACursor.hpp"

void operator delete(void *) {
}

void operator delete(void *, unsigned int) {
}

void operator delete(void *, long unsigned int) {
}

namespace vga::modifier {
    //
    // VGAStreamColorModifier
    //
    VGAStreamColorModifier::VGAStreamColorModifier(uint8_t color) :
        VGAStreamModifier(), _color{color} {
    }

    VGAStreamColorModifier::VGAStreamColorModifier(color::vga_color foreground, color::vga_color background) :
        VGAStreamModifier(),
        _color{static_cast<uint8_t>(background << 4 | (foreground & 0x0F))} {
    }

    void VGAStreamColorModifier::operator()(uint8_t &color) const {
        // change both background and foreground bits
        color = _color;
    }

    //
    // VGAStreamBackgroundModifier
    //
    VGAStreamBackgroundModifier::VGAStreamBackgroundModifier(uint8_t bg_color) :
        VGAStreamColorModifier(bg_color) {
    }

    VGAStreamBackgroundModifier::VGAStreamBackgroundModifier(color::t_vga_color bg_color) :
        VGAStreamColorModifier(bg_color) {
    }

    void VGAStreamBackgroundModifier::operator()(uint8_t &color_byte) const {
        // change the backround bits and keep the foreground ones
        color_byte = static_cast<uint8_t>(_color << 4 | (color_byte & 0x0F));
    }

    //
    // VGAStreamForegroundModifier
    //
    VGAStreamForegroundModifier::VGAStreamForegroundModifier(uint8_t foreground) :
        VGAStreamColorModifier(foreground) {
    }

    VGAStreamForegroundModifier::VGAStreamForegroundModifier(color::vga_color foreground) :
        VGAStreamColorModifier(foreground) {
    }

    void VGAStreamForegroundModifier::operator()(uint8_t &color_byte) const {
        // change the foreground bits and keep the background ones
        color_byte = static_cast<uint8_t>((color_byte & 0xF0) | (_color & 0x0F));
    }

    //
    // VGASetLineModifier
    //
    VGASetLineModifier::VGASetLineModifier(uint16_t line) :
        VGAStreamCursorModifier(), _line{line} {
    }

    void VGASetLineModifier::operator()(VGACursor &cursor) const {
        cursor.set_line(_line);
    }
} // vga

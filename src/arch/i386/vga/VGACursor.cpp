//
// Created by pierre on 12/18/25.
//

#include "VGACursor.hpp"
#include "vga.hpp"

namespace vga {
    VGACursor::VGACursor(): _pos(const_cast<iterator>(_cbegin)) {}

    VGACursor::iterator VGACursor::begin() {
        return const_cast<iterator>(_cbegin);
    }

    VGACursor::iterator VGACursor::end() {
        return const_cast<iterator>(_cend);
    }

    VGACursor::const_iterator VGACursor::cbegin() const {
        return _cbegin;
    }

    VGACursor::const_iterator VGACursor::cend() const {
        return _cend;
    }

    VGACursor::iterator* VGACursor::pos() {
        return &_pos;
    }

    VGACursor::size_type VGACursor::ipos() const {
        return static_cast<size_type>(_pos - const_cast<iterator>(_cbegin));
    }

    void VGACursor::set_char(const t_vga_char& c) const {
        *_pos = c;
    }

    void VGACursor::next_line() {
        _pos += VGA_WIDTH - (ipos() % VGA_WIDTH);
    }

    void VGACursor::set_line(const uint16_t line) {
        _pos = const_cast<iterator>(_cbegin) + line * VGA_WIDTH;
    }

    volatile const VGACursor::const_iterator VGACursor::_cbegin{reinterpret_cast<const_iterator>(0xB8000)};
    volatile const VGACursor::const_iterator VGACursor::_cend{reinterpret_cast<const_iterator>(0xB8000 + 80 * 25 * sizeof(t_vga_char))};
} // vga
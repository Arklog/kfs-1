//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "vga.hpp"

namespace vga {

    VGAMonitor::VGAMonitor(): _buffer{}, _cursor{}, _color(vga::color::color_set::WHITE_ON_BLACK), _view_line(0) {
        clear();
    }

    void VGAMonitor::clear() {
        _buffer.clear();
        _cursor.set(0, 0);
        _view_line = 0;

        VGADisplay::clear();
        _refresh();
    }

    void VGAMonitor::init() {
        _color = vga::color::color_set::WHITE_ON_BLACK;
        _view_line = 0;
        this->clear();
    }

    void VGAMonitor::put_char(const char c) {
        if (c == '\n') {
            _buffer.newline(_cursor.line, _cursor.column);
            _cursor.newline();
        } else if (c == '\t') {
            for (int i = 0; i < 4; ++i) {
                put_char(' ');
                _cursor.advance(_buffer.line_length(_cursor.line), _buffer.line_count());
            }
        } else {
            _buffer.write(_cursor,vga::t_vga_char(c, _color));
            _cursor.advance(_buffer.line_length(_cursor.line), _buffer.line_count(), 1);
        }

        if (_cursor.line >= ScrollbackBuffer::MAX_LINES) {
            _buffer.scroll_up();
            _cursor.line = ScrollbackBuffer::MAX_LINES - 1;
        }

        if (_cursor.line >= _view_line + VGA_HEIGHT)
            ++_view_line;
    }

    void VGAMonitor::write(const char *str) {
        while (*str)
            put_char(*str++);
        _refresh();
    }

    void VGAMonitor::scroll_up() {
        if (_view_line > 0) {
            --_view_line;
        }
        _cursor.up(_buffer.line_length(_cursor.line - 1));
        _refresh();
    }

    void VGAMonitor::scroll_down() {
        if (_view_line + VGA_HEIGHT < _buffer.line_count()) {
            ++_view_line;
        }
        _cursor.down(_buffer.line_length(_cursor.line + 1), _buffer.line_count());
        _refresh();
    }

    void VGAMonitor::move_left() {
        _cursor.back(_buffer.line_length(_cursor.line - 1));
        _refresh();
    }

    void VGAMonitor::move_right() {
        _cursor.advance(_buffer.line_length(_cursor.line), _buffer.line_count());
        _refresh();
    }

    void VGAMonitor::backspace() {
        if (_cursor.line == 0 && _cursor.column == 0)
            return;
        _buffer.backspace(_cursor.line, _cursor.column);
        _cursor.back(_buffer.line_length(_cursor.line - 1));
        _refresh();
    }

    void VGAMonitor::set_fg_color(color::vga_color fg) {
        uint8_t bg = (_color >> 4) & 0x0F;
        _color = (bg << 4) | (fg & 0x0F);
    }

    void VGAMonitor::set_bg_color(color::vga_color bg) {
        uint8_t fg = _color & 0x0F;
        _color = (bg << 4) | (fg & 0x0F);
    }

    void VGAMonitor::set_colors(color::vga_color fg, color::vga_color bg) {
        _color = (bg << 4) | (fg & 0x0F);
    }

    void VGAMonitor::_refresh() {
        VGADisplay::render(_buffer, _view_line);
        VGADisplay::update_hw_cursor(_cursor, _view_line);
    }

    VGAMonitor &VGAMonitor::operator<<(const char *str) {
        write(str);
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const char str) {
        put_char(str);
        _refresh();
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const color::vga_color fg) {
        uint8_t bg = (_color >> 4) & 0x0F;
        _color = (bg << 4) | (fg & 0x0F);
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const VGAColorChange changer) {
        _color = (changer.bg << 4) | (changer.fg & 0x0F);
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const uint8_t changer) {
        _color = changer;
        return *this;
    }

}

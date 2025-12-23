//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "VGAStreamModifier.hpp"
#include "vga.hpp"

namespace vga {

    VGAMonitor::VGAMonitor() :
        _view_line(0) {
        clear();
    }

    void VGAMonitor::clear() {
        _buffer.clear();
        _cursor.set(0, 0);
        _view_line = 0;

        VGADisplay::clear();
        _refresh();
    }

    void VGAMonitor::put_char(unsigned char c) {
        if (c == '\n') {
            _cursor.newline();
            _buffer.newline(_cursor.line, _cursor.column);
        } else if (c == '\r') {
            _cursor.set(_cursor.line, 0);
        } else if (c == '\t') {
            for (int i = 0; i < 4; ++i)
                put_char(' ');
            return;
        } else {
            _buffer.write(_cursor, t_vga_char{c, _color});
            _cursor.advance();
        }

        if (_cursor.line >= ScrollbackBuffer::MAX_LINES) {
            _buffer.scroll_up();
            _cursor.line = ScrollbackBuffer::MAX_LINES - 1;
        }

        if (_cursor.line >= _view_line + VGA_HEIGHT)
            ++_view_line;

        _refresh();
    }

    void VGAMonitor::write(const char *str) {
        while (*str)
            put_char(*str++);
    }

    void VGAMonitor::scroll_up() {
        if (_view_line > 0) {
            --_view_line;
        }
        if (_cursor.line > 0) {
            --_cursor.line;
        }
        _refresh();
    }

    void VGAMonitor::scroll_down() {
        if (_view_line + VGA_HEIGHT < _buffer.line_count()) {
            ++_view_line;
        }
        if (_cursor.line + 1 < _buffer.line_count()) {
            ++_cursor.line;
        }
        _refresh();
    }

    void VGAMonitor::move_left() {
        if (_cursor.column > 0) {
            --_cursor.column;
        } else if (_cursor.line > 0) {
            --_cursor.line;
            _cursor.column = _buffer.line_length(_cursor.line);
        }
        _refresh();
    }

    void VGAMonitor::move_right() {
        uint16_t len = _buffer.line_length(_cursor.line);
        if (_cursor.column < len) {
            ++_cursor.column;
        } else if (_cursor.line + 1 < _buffer.line_count()) {
            ++_cursor.line;
            _cursor.column = 0;
        }
        _refresh();
    }

    void VGAMonitor::backspace() {
        if (_cursor.line == 0 && _cursor.column == 0)
            return;
        _buffer.backspace(_cursor.line, _cursor.column);
        if (_cursor.column > 0) {
            --_cursor.column;
        } else if (_cursor.line > 0) {
            --_cursor.line;
            _cursor.column = _buffer.line_length(_cursor.line);
        }
        _refresh();
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
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const modifier::VGAStreamColorModifier &modifier) {
        modifier(_color);
        return *this;
    }
}

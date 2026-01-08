//
// Created by pierre on 12/17/25.
//

#include "VGAMonitor.hpp"
#include "vga.hpp"

namespace vga {

    VGAMonitor::VGAMonitor(): _fg(color::vga_color::WHITE), _bg(color::vga_color::BLACK), _view_line(0) {
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
        _fg = color::vga_color::WHITE;
        _bg = color::vga_color::BLACK;
        _view_line = 0;
        clear();
    }

    void VGAMonitor::put_char(const char c) {
        if (c == '\n') {
            _buffer.newline(_cursor.line, _cursor.column);
            _cursor.newline();
        } else if (c == '\t') {
            for (int i = 0; i < 4; ++i)
                put_char(' ');
        } else {
            _buffer.write(_cursor,vga::t_vga_char(c, _fg, _bg));
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
            if (_cursor.column > _buffer.line_length(_cursor.line))
                _cursor.column = _buffer.line_length(_cursor.line);
        }
        _refresh();
    }

    void VGAMonitor::scroll_down() {
        if (_view_line + VGA_HEIGHT < _buffer.line_count()) {
            ++_view_line;
        }
        if (_cursor.line + 1 < _buffer.line_count()) {
            ++_cursor.line;
            if (_cursor.column > _buffer.line_length(_cursor.line))
                _cursor.column = _buffer.line_length(_cursor.line);
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

    void VGAMonitor::set_fg_color(color::vga_color fg) {
        _fg = fg;
    }

    void VGAMonitor::set_bg_color(color::vga_color bg) {
        _bg = bg;
    }

    void VGAMonitor::set_colors(color::vga_color fg, color::vga_color bg) {
        _fg = fg;
        _bg = bg;
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

    VGAMonitor &VGAMonitor::operator<<(const color::vga_color fg) {
        _fg = fg;
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const VGAColorChange changer) {
        _fg = changer.fg;
        _bg = changer.bg;
        return *this;
    }


}

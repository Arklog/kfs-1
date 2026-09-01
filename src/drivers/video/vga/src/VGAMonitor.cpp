//
// Created by pierre on 12/17/25.
//

#include "drivers/video/vga/VGAMonitor.hpp"
#include "logging/logging.hpp"
#include "drivers/video/vga/vga.hpp"

namespace vga {

    VGAMonitor::VGAMonitor(): _buffer{}, _cursor_write{}, _user_cursor{}, _color(vga::color::color_set::WHITE_ON_BLACK), _view_line(0), _lim_line(0), _lim_column(0), _page_idx(0) {
        _user_cursor.set(0, 0);
        _cursor_write.set(0, 0);
        clear();
    }

    void VGAMonitor::clear() {
        _buffer.clear();
        _user_cursor.set(0, 0);
        _cursor_write.set(0, 0);
        _view_line = 0;

        VGADisplay::clear(_page_idx);
        _refresh();
    }

    void VGAMonitor::init(uint8_t id) {
        _color = vga::color::color_set::WHITE_ON_BLACK;
        _view_line = 0;
        _page_idx = id;
        this->clear();
    }

    void VGAMonitor::put_char(const char c, bool user_inp) {

        if (c == '\n') {
            if (user_inp) {
                _buffer.newline(_user_cursor.line, _user_cursor.column);
                _user_cursor.newline();

            } else {
               _buffer.newline(_cursor_write.line, _cursor_write.column);
               _cursor_write.newline();
            }
        } else {
            if (user_inp) {
                _buffer.write(_user_cursor,vga::t_vga_char(c, _color));
                _user_cursor.advance(_buffer.line_length(_user_cursor.line), _buffer.line_count(), 1);
            } else {
                _buffer.write(_cursor_write,vga::t_vga_char(c, _color));
                _cursor_write.advance(_buffer.line_length(_cursor_write.line), _buffer.line_count(), 1);
            }
        }

        if (_cursor_write.line >= ScrollbackBuffer::MAX_LINES) {
            _buffer.scroll_up();
            _cursor_write.line = ScrollbackBuffer::MAX_LINES - 1;
        }

        if (_cursor_write.line >= _view_line + VGA_HEIGHT)
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
        _user_cursor.up(_buffer.line_length(_user_cursor.line - 1));
        _refresh();
    }

    void VGAMonitor::scroll_down() {
        if (_view_line + VGA_HEIGHT < _buffer.line_count()) {
            ++_view_line;
        }
        _user_cursor.down(_buffer.line_length(_user_cursor.line + 1), _buffer.line_count());
        _refresh();
    }

    void VGAMonitor::move_left() {
        _user_cursor.back(_buffer.line_length(_user_cursor.line - 1));
        _refresh();
    }

    void VGAMonitor::move_right() {
        _user_cursor.advance(_buffer.line_length(_user_cursor.line), _buffer.line_count(), 0);
        _refresh();
    }

    void VGAMonitor::backspace() {
        if (_user_cursor.line == 0 && _user_cursor.column == 0)
            return;
        _user_cursor.back(_buffer.line_length(_user_cursor.line - 1));
        _buffer.backspace(_user_cursor.line, _user_cursor.column);
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
        VGADisplay::render(_buffer, _view_line, _page_idx);
        VGADisplay::update_hw_cursor(_user_cursor, _view_line, _page_idx);
    }

    void VGAMonitor::handle_user_input(char inp) {

        if (_user_cursor.line < _lim_line)
            return;
        if (_user_cursor.line == _lim_line) {
            if (_user_cursor.column < _lim_column)
                return;
            if (_user_cursor.column == _lim_column && inp == '\b') {
                if ( _user_cursor.column == 0)
                    return;
                _buffer.backspace(_user_cursor.line, _user_cursor.column);
                _refresh();
                return;
            } else if (_user_cursor.column == _lim_column && inp == '\n') {
                put_char('\n', true);
                _refresh();
                return;
            }
        }
        if (inp == '\b') {
            backspace();
        }
        else
            put_char(inp, true);
        _cursor_write.set(_user_cursor.line, _user_cursor.column);
        _refresh();
    }

    VGAMonitor &VGAMonitor::operator<<(const char *str) {
        write(str);
        _sync_cursors();
        _lim_line = _cursor_write.line;
        _lim_column = _cursor_write.column;
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

    unsigned int VGAMonitor::get_page() const {
        return _page_idx;
    }

    void VGAMonitor::_sync_cursors() {
        _user_cursor.set(_cursor_write.line + 1, 0);
    }
}

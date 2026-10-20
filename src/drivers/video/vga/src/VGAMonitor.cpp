//
// Created by pierre on 12/17/25.
//

#include "drivers/video/vga/VGAMonitor.hpp"
#include "logging/logging.hpp"
#include "drivers/video/vga/vga.hpp"

namespace vga {

    VGAMonitor::VGAMonitor(): _buffer_rd{}, _buffer_wr{}, _cursor_rd{}, _cursor_wr{}, _color(vga::color::color_set::WHITE_ON_BLACK), _view_line(0), _page_idx(0) {
        _cursor_wr.set(0, 0);
        _cursor_wr.set(0, 0);
        clear();
    }

    void VGAMonitor::clear() {
        _buffer_wr.clear();
        _buffer_rd.clear();
        _cursor_rd.set(0, 0);
        _cursor_wr.set(0, 0);
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

     void VGAMonitor::scroll_up() {
        if (_view_line > 0) {
            --_view_line;
        }
        _cursor_wr.up(_buffer_wr.line_length(_cursor_wr.line - 1));
        _refresh();
    }

    void VGAMonitor::scroll_down() {
        if (_view_line + VGA_HEIGHT < _buffer_wr.line_count()) {
            ++_view_line;
        }
        _cursor_wr.down(_buffer_wr.line_length(_cursor_wr.line + 1), _buffer_wr.line_count());
        _refresh();
    }

    void VGAMonitor::move_left() {
        _cursor_wr.back(_buffer_wr.line_length(_cursor_wr.line - 1));
        _refresh();
    }

    void VGAMonitor::move_right() {
        _cursor_wr.advance(_buffer_wr.line_length(_cursor_wr.line), _buffer_wr.line_count(), 0);
        _refresh();
    }

    void VGAMonitor::backspace(ScrollbackBuffer &buff, VGACursor &curs) {
        int prev_line_len = buff.line_length(curs.line - 1);
        buff.backspace(curs.line, curs.column);

        curs.back(prev_line_len);
        _refresh();
    }

    void VGAMonitor::put_char(ScrollbackBuffer &buff, VGACursor &curs, const char c) {
        if (c == '\n') {
            buff.newline(curs.line, curs.column);
            curs.newline();
        } else if (c == '\t') {
            for (int i = 0; i < 4; ++i) {
            put_char(buff, curs, ' ');
            curs.advance(buff.line_length(curs.line), buff.line_count());
        }
        } else {
            buff.write(curs,vga::t_vga_char(c, _color));
            curs.advance(buff.line_length(curs.line), buff.line_count(), 1);
        }

        if (curs.line >= ScrollbackBuffer::MAX_LINES) {
            buff.scroll_up();
            curs.line = ScrollbackBuffer::MAX_LINES - 1;
        }
    }

    void VGAMonitor::put_char(ScrollbackBuffer &buff, VGACursor &curs, const vga::t_vga_char c) {
        buff.write(curs,c);
        curs.advance(buff.line_length(curs.line), buff.line_count(), 1);

        if (curs.line >= ScrollbackBuffer::MAX_LINES) {
            buff.scroll_up();
            curs.line = ScrollbackBuffer::MAX_LINES - 1;
        }

        while (curs.line >= _view_line + VGA_HEIGHT)
            ++_view_line;
    }

    void VGAMonitor::write(ScrollbackBuffer &buff, VGACursor &curs, const char *str) {
        while (*str)
            put_char(buff, curs, *str++);
        _refresh();
    }

    void VGAMonitor::write(ScrollbackBuffer &dest, VGACursor &curs, const ScrollbackBuffer &src) {
        for (uint32_t row = 0; row < src.line_count(); ++row) {
            if (row != 0 && src.line_length(row - 1) < VGA_WIDTH)
                put_char(dest, curs, '\n');
            for (uint16_t col = 0; col < src.line_length(row); ++col) {
                put_char(dest, curs, src.line(row)[col]);
            }
        }
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
        ScrollbackBuffer display{};
        VGACursor display_curs{};

        display_curs.set(0,0);
        write(display, display_curs, _buffer_rd);
        write(display, display_curs, _buffer_wr);
        VGADisplay::render(display, _view_line, _page_idx);
        display_curs.set(_cursor_rd.line + _cursor_wr.line, _cursor_rd.column + _cursor_wr.column);
        VGADisplay::update_hw_cursor(display_curs, _view_line, _page_idx);
    }

    VGAMonitor &VGAMonitor::operator<<(const char *str) {
        handle_user_input('a', true);
        write(_buffer_rd, _cursor_rd, str);
        _refresh();
        return *this;
    }

    VGAMonitor &VGAMonitor::operator<<(const char str) {
        put_char(_buffer_rd, _cursor_rd, str);
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

    void VGAMonitor::handle_user_input(char inp, bool reset) {
        if (reset == true) {
            if (_cursor_wr.line == 0 && _cursor_wr.column == 0) {
                return;
            }
            write(_buffer_rd, _cursor_rd, _buffer_wr);
            _buffer_wr.clear();
            _cursor_wr.set(0,0);
            return;
        }
        if (inp == '\b') {
            backspace(_buffer_wr, _cursor_wr);
            _refresh();
            return;
        }
        put_char(_buffer_wr, _cursor_wr, inp);
        _refresh();
    }

    void VGAMonitor::handle_user_move(int inp) {
        if (inp == 0) {
            scroll_up();
        } else if (inp == 1) {
            scroll_down();
        } else if (inp == 2) {
            move_left();
        } else if (inp == 3) {
            move_right();
        }
        return;
        }
}
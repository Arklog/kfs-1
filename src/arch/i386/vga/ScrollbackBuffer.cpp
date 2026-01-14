//
// Created by alice on 21/12/2025.
//

#include "ScrollbackBuffer.hpp"
#include "lib/math/math.hpp"

namespace vga {
    ScrollbackBuffer::ScrollbackBuffer() :_buffer{} {
        clear();
    }

    void ScrollbackBuffer::clear() {
        for (auto& line: _buffer) {
            line.clear();
        }
        _buffer.clear();
    }

    void ScrollbackBuffer::write(const VGACursor &cursor, const t_vga_char &c) {
        if (cursor.line >= MAX_LINES || cursor.column >= VGA_WIDTH)
            return;

        while (_buffer.size() <= cursor.line) {
            _buffer.push_bash({});
        }
        _buffer[cursor.line].insert(cursor.column, c);
    }

    void ScrollbackBuffer::erase(const VGACursor &cursor) {
        if (cursor.line >= MAX_LINES || cursor.column >= VGA_WIDTH)
            return;

        _buffer[cursor.line].erase(cursor.column);
    }

    void ScrollbackBuffer::newline(uint32_t line, uint16_t column) {
        if (_buffer.size() >= MAX_LINES)
            return;

        auto new_line = _buffer.insert(_buffer.begin() + line + 1, {});
        if (new_line == _buffer.end()) {
            return ;
        }

        auto previous_line = new_line - 1;
        new_line->insert(new_line->begin(), previous_line->begin() + column, previous_line->end());
        previous_line->erase(previous_line->begin() + column, previous_line->end());

        // uint16_t old_len = _line_len[line];
        // uint16_t new_len = (column < old_len) ? (old_len - column) : 0;
        //
        // if (new_len > 0)
        //     kstring::memcpy(_buffer[line + 1], &_buffer[line][column], new_len * sizeof(t_vga_char));
        //
        // for (uint16_t i = column; i < old_len; ++i)
        //     _buffer[line][i] = vga::t_vga_char(' ', vga::color::WHITE);
        //
        // _line_len[line]     = column;
        // _line_len[line + 1] = new_len;
        // ++_lines;
    }

    void ScrollbackBuffer::merge_lines(uint32_t dst, uint32_t src) {
        auto &dst_line = _buffer[dst];
        auto &src_line = _buffer[src];

        auto to_move = math::min(dst_line.available_space(), src_line.size());
        dst_line.insert(dst_line.end(), src_line.begin(), src_line.begin() + to_move);
        src_line.erase(src_line.begin(), src_line.begin() + to_move);

        if (src_line.size() == 0)
            _buffer.erase(src);
    }

    void ScrollbackBuffer::backspace(uint32_t line_idx, uint16_t col) {
        if (line_idx == 0 && col == 0)
            return;

        if (col > 0) {
            auto &line = _buffer[line_idx];
            line.erase(line.begin() + col);
            return;
        }

        uint32_t prev = line_idx - 1;
        merge_lines(prev, line_idx);
//        _buffer.erase(_buffer.end() - 1);
        //
        // for (uint32_t i = line_idx; i + 1 < _lines; ++i) {
        //     kstring::memcpy(
        //             _buffer[i],
        //             _buffer[i + 1],
        //             _line_len[i + 1] * sizeof(t_vga_char)
        //             );
        //     _line_len[i] = _line_len[i + 1];
        // }
        //
        // _line_len[_lines - 1] = 0;
    }

    const ScrollbackBuffer::line_type &ScrollbackBuffer::line(uint32_t index) const {
        return _buffer[index];
    }

    uint16_t ScrollbackBuffer::line_length(uint32_t index) const {
        if (index >= _buffer.size())
            return 0;
        return _buffer[index].size();
    }

    uint32_t ScrollbackBuffer::line_count() const {
        return _buffer.size();
    }

    void ScrollbackBuffer::scroll_up() {
        _buffer.erase(_buffer.begin());
    }

    const ScrollbackBuffer::buffer_type &ScrollbackBuffer::get_buffer() const {
        return _buffer;
    }

    ScrollbackBuffer::buffer_type &ScrollbackBuffer::get_buffer() {
        return _buffer;
    }
}

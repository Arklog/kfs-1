//
// Created by alice on 21/12/2025.
//

#include "ScrollbackBuffer.hpp"

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

        _buffer[cursor.line].push_bash(c);
    }

    void ScrollbackBuffer::erase(const VGACursor &cursor) {
        if (cursor.line >= MAX_LINES || cursor.column >= VGA_WIDTH)
            return;

        _buffer[cursor.line][cursor.column] = vga::t_vga_char(' ', vga::color::WHITE);

        if (_line_len[cursor.line] > 0 && cursor.column == _line_len[cursor.line] - 1)
            --_line_len[cursor.line];
    }

    void ScrollbackBuffer::newline(uint32_t line, uint16_t column) {
        if (_buffer.size() >= MAX_LINES)
            return;

        auto new_line = _buffer.insert(_buffer.begin() + line, {});
        if (new_line == _buffer.end()) {
            return ;
        }

        auto next_line = new_line + 1;
        new_line->insert(new_line->begin(), next_line->begin(), next_line->begin() + column);

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
        uint16_t dst_len = _line_len[dst];
        uint16_t src_len = _line_len[src];

        uint16_t copy_len =
                (dst_len + src_len > VGA_WIDTH)
                    ? (VGA_WIDTH - dst_len)
                    : src_len;

        for (uint16_t i = 0; i < copy_len; ++i) {
            _buffer[dst][dst_len + i] = _buffer[src][i];
        }

        _line_len[dst] = dst_len + copy_len;
    }

    void ScrollbackBuffer::backspace(uint32_t line_idx, uint16_t col) {
        if (line_idx == 0 && col == 0)
            return;

        if (col > 0) {
            auto &line = _buffer[line_idx];
            line.erase(line.begin() + col);

            line[_line_len[line_idx] - 1] = vga::t_vga_char(' ', vga::color::WHITE);
            return;
        }

        uint32_t prev = line_idx - 1;

        merge_lines(prev, line_idx);

        for (uint32_t i = line_idx; i + 1 < _lines; ++i) {
            kstring::memcpy(
                    _buffer[i],
                    _buffer[i + 1],
                    _line_len[i + 1] * sizeof(t_vga_char)
                    );
            _line_len[i] = _line_len[i + 1];
        }

        _line_len[_lines - 1] = 0;
    }

    const ScrollbackBuffer::line_type *ScrollbackBuffer::line(uint32_t index) const {
        if (index >= _buffer.size())
            return nullptr;
        return &_buffer[index];
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


}

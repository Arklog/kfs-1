//
// Created by alice on 21/12/2025.
//

#include "ScrollbackBuffer.hpp"

namespace vga {
    ScrollbackBuffer::ScrollbackBuffer(): _lines(0) {
        clear();
    }

    void ScrollbackBuffer::clear() {
        _lines = 1;
        for (uint32_t i = 0; i < MAX_LINES; ++i)
            _line_len[i] = 0;
    }

    void ScrollbackBuffer::write(const VGACursor& cursor, const t_vga_char &c)
    {
        if (cursor.line >= MAX_LINES || cursor.column >= VGA_WIDTH)
            return;

        _buffer[cursor.line][cursor.column] = c;

        if (cursor.column >= _line_len[cursor.line])
            _line_len[cursor.line] = cursor.column + 1;

        if (cursor.line >= _lines)
            _lines = cursor.line + 1;
    }

    void ScrollbackBuffer::erase(const VGACursor &cursor) {
        if (cursor.line >= MAX_LINES || cursor.column >= VGA_WIDTH)
            return;

        _buffer[cursor.line][cursor.column] = vga_get_color(' ');

        if (_line_len[cursor.line] > 0 && cursor.column == _line_len[cursor.line] - 1)
            --_line_len[cursor.line];
    }

    void ScrollbackBuffer::newline(uint32_t line, uint16_t column) {
        if (_lines >= MAX_LINES)
            return;

        for (uint32_t i = _lines; i > line + 1; --i) {
            kstring::memcpy(_buffer[i], _buffer[i - 1], sizeof(_buffer[i]));
            _line_len[i] = _line_len[i - 1];
        }

        uint16_t old_len = _line_len[line];
        uint16_t new_len = (column < old_len) ? (old_len - column) : 0;

        if (new_len > 0)
            kstring::memcpy(_buffer[line + 1], &_buffer[line][column], new_len * sizeof(t_vga_char));

        for (uint16_t i = column; i < old_len; ++i)
            _buffer[line][i] = vga_get_color(' ');

        _line_len[line]     = column;
        _line_len[line + 1] = new_len;
        ++_lines;
    }

    void ScrollbackBuffer::merge_lines(uint32_t dst, uint32_t src)
    {
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

    void ScrollbackBuffer::backspace(uint32_t line, uint16_t col)
    {
        if (line == 0 && col == 0)
            return;

        if (col > 0) {
            for (uint16_t i = col - 1; i + 1 < _line_len[line]; ++i)
                _buffer[line][i] = _buffer[line][i + 1];

            _buffer[line][_line_len[line] - 1] = vga_get_color(' ');
            --_line_len[line];
            return;
        }

        uint32_t prev = line - 1;

        merge_lines(prev, line);

        for (uint32_t i = line; i + 1 < _lines; ++i) {
            kstring::memcpy(
                _buffer[i],
                _buffer[i + 1],
                _line_len[i + 1] * sizeof(t_vga_char)
            );
            _line_len[i] = _line_len[i + 1];
        }

        _line_len[_lines - 1] = 0;
    }

    const t_vga_char *ScrollbackBuffer::line(uint32_t index) const {
        if (index >= _lines)
            return nullptr;
        return _buffer[index];
    }

    uint16_t ScrollbackBuffer::line_length(uint32_t index) const {
        if (index >= _lines)
            return 0;
        return _line_len[index];
    }

    uint32_t ScrollbackBuffer::line_count() const {
        return _lines;
    }

    void ScrollbackBuffer::scroll_up() {
        for (uint32_t l = 1; l < MAX_LINES; ++l) {
            for (uint16_t c = 0; c < VGA_WIDTH; ++c) {
                _buffer[l - 1][c] = _buffer[l][c];
            }
        }

        for (uint16_t c = 0; c < VGA_WIDTH; ++c) {
            _buffer[MAX_LINES - 1][c] = vga_get_color(' ');
        }

        if (_lines > 0)
            --_lines;
    }


}

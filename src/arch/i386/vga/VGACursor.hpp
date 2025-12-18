//
// Created by pierre on 12/18/25.
//

#ifndef KFS_1_VGACURSOR_HPP
#define KFS_1_VGACURSOR_HPP
#include "include/stdint.hpp"

namespace vga {
    union t_vga_char;

    class VGACursor {
    public:
        using iterator = t_vga_char*;
        using const_iterator = t_vga_char const *;
        using size_type = uint32_t;

        VGACursor();

        /**
         * Get an iterator to the beginning of the VGA text buffer
         * @return
         */
        iterator begin();

        /**
         * Get an iterator to the end of the VGA text buffer
         * @return
         */
        iterator end();

        /**
         * Get a const iterator to the beginning of the VGA text buffer
         * @return
         */
        const_iterator cbegin() const;

        /**
         * Get a const iterator to the end of the VGA text buffer
         * @return
         */
        const_iterator cend() const;

        /**
         * Get the current position of the cursor
         * @return
         */
        iterator* pos();

        /**
         * Get the current position of the cursor as an index
         * @return
         */
        size_type ipos() const;

        /**
         * Set the character at the current cursor position
         *
         * @param c VGA character to set
         */
        void set_char(const t_vga_char& c) const;

        /**
         * Move the cursor to the beginning of the next line
         */
        void next_line();

        /**
         * Set the cursor to the specified line
         *
         * @param line Line number (0-based)
         */
        void set_line(uint16_t line);

        /**
         * Set the cursor to the specified column
         *
         * @param column Column number (0-based)
         */
        void set_column(uint16_t column);

        /**
         * Set the cursor to the specified line and column
         *
         * @param line Line number (0-based)
         * @param column Column number (0-based)
         */
        void set_pos(uint16_t line, uint16_t column);

    private:
        static volatile const const_iterator _cbegin;
        static volatile const const_iterator _cend;

        iterator _pos;
    };
} // vga

#endif //KFS_1_VGACURSOR_HPP
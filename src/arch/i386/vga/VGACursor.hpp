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
        iterator pos();

        size_type ipos() const;

    private:
        static volatile const const_iterator _cbegin;
        static volatile const const_iterator _cend;

        iterator _pos;
    };
} // vga

#endif //KFS_1_VGACURSOR_HPP
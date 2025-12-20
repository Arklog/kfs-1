//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGA_HPP
#define KFS_1_VGA_HPP

#include "include/stdint.hpp"

namespace vga {
    constexpr uint16_t VGA_WIDTH = 80;
    constexpr uint16_t VGA_HEIGHT = 25;

    namespace color {
        /**
         * VGA color codes
         */
        using t_vga_color = enum vga_color {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            CYAN = 3,
            RED = 4,
            MAGENTA = 5,
            BROWN = 6,
            LIGHT_GREY = 7,
            DARK_GREY = 8,
            LIGHT_BLUE = 9,
            LIGHT_GREEN = 10,
            LIGHT_CYAN = 11,
            LIGHT_RED = 12,
            LIGHT_MAGENTA = 13,
            LIGHT_BROWN = 14,
            WHITE = 15,
        };
    }

    /**
     * Represents a VGA character (ASCII + color)
     */
    union t_vga_char {
        struct [[gnu::packed]] {
            uint8_t ascii;
            uint8_t color;
        } data;
        uint16_t raw;

        uint8_t get_foreground() const;
        uint8_t get_background() const;

        void set_foreground(color::t_vga_color color);
        void set_background(color::t_vga_color color);
        void set_color(color::t_vga_color foreground, color::t_vga_color background);
    };

    /**
     * Create a VGA character with specified ASCII and colors
     *
     * @param character ASCII character
     * @param fg Foreground color
     * @param bg Background color
     *
     * @return VGA character
     */
    t_vga_char vga_get_color(uint8_t character, color::vga_color fg = color::WHITE, color::vga_color bg = color::BLACK);

    inline const char * endl = "\n";
}

#endif //KFS_1_VGA_HPP
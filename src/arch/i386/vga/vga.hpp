//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_VGA_HPP
#define KFS_1_VGA_HPP

#include "include/stdint.hpp"

namespace vga {
    constexpr uint16_t VGA_WIDTH  = 80;
    constexpr uint16_t VGA_HEIGHT = 25;

    namespace color {
        /**
         * VGA color codes
         */
        using t_vga_color = enum vga_color {
            BLACK         = 0,
            BLUE          = 1,
            GREEN         = 2,
            CYAN          = 3,
            RED           = 4,
            MAGENTA       = 5,
            BROWN         = 6,
            LIGHT_GREY    = 7,
            DARK_GREY     = 8,
            LIGHT_BLUE    = 9,
            LIGHT_GREEN   = 10,
            LIGHT_CYAN    = 11,
            LIGHT_RED     = 12,
            LIGHT_MAGENTA = 13,
            LIGHT_BROWN   = 14,
            WHITE         = 15,
        };

        using t_color_set = enum color_set {
            BLACK_ON_WHITE = WHITE << 4 | BLACK,
            CYAN_ON_BLACK  = BLACK << 4 | CYAN,
            GREEN_ON_BLACK = BLACK << 4 | GREEN,
            RED_ON_BLACK   = BLACK << 4 | RED,
            WHITE_ON_BLACK = BLACK << 4 | WHITE,
            BROWN_ON_BLACK = BLACK << 4 | BROWN,
            DEFAULT        = WHITE_ON_BLACK
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

        t_vga_char() = default;

        t_vga_char(uint8_t ascii, uint8_t color);

        t_vga_char(uint8_t ascii, uint8_t foreground, uint8_t background);

        /**
         * Get the foreground color
         * @return
         */
        color::t_vga_color get_foreground() const;

        /**
         * Get the background color
         *
         * @return
         */
        color::t_vga_color get_background() const;

        /**
         * Set the foreground color
         * @param color
         */
        void set_foreground(color::t_vga_color color);

        /**
         * Set the background color
         * @param color
         */
        void set_background(color::t_vga_color color);

        /**
         * Set both background and foreground color
         * @param foreground
         * @param background
         */
        void set_color(color::t_vga_color foreground, color::t_vga_color background);
    };

    /**
     * Helper to change both foreground and background displayed colors.
     */
    struct VGAColorChange {
        VGAColorChange(color::t_vga_color foreground, color::t_vga_color background);
        VGAColorChange(color::t_color_set colorset);

        color::t_vga_color fg;
        color::t_vga_color bg;
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
    [[deprecated]] t_vga_char make_vga_char(uint8_t          character, color::vga_color fg = color::WHITE,
                                            color::vga_color bg                             = color::BLACK);

    inline const char *endl = "\n";
}

#endif //KFS_1_VGA_HPP

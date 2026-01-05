//
// Created by pierre on 12/18/25.
//

#ifndef KFS_1_VGASTREAMMODIFIER_HPP
#define KFS_1_VGASTREAMMODIFIER_HPP

#include "arch/i386/vga/vga.hpp"
#include "include/stdint.hpp"

namespace vga {
    class VGACursor;
}

namespace vga::modifier {
    /**
     * Base class for VGA stream modifiers (like setting the cursor line, changing color, etc.)
     */
    class VGAStreamModifier {
    public:
        VGAStreamModifier() = default;

        virtual ~VGAStreamModifier() = default;
    };

    /**
     * Base class for VGA stream cursor modifiers
     */
    class VGAStreamCursorModifier : public VGAStreamModifier {
    public:
        VGAStreamCursorModifier() = default;

        ~VGAStreamCursorModifier() override = default;

        virtual void operator()(VGACursor &cursor) const = 0;
    };

    /**
     * Allow for VGA color output modifications
     */
    class VGAStreamColorModifier : public VGAStreamModifier {
    protected:
        const uint8_t _color;

    public:
        VGAStreamColorModifier(uint8_t color);

        VGAStreamColorModifier(color::vga_color foreground, color::vga_color background);

        ~VGAStreamColorModifier() override = default;

        virtual void operator()(uint8_t &) const;
    };

    /**
     * Allow for VGA background color output modifications
     */
    class VGAStreamBackgroundModifier : public VGAStreamColorModifier {
    public:
        explicit VGAStreamBackgroundModifier(uint8_t bg_color);

        explicit VGAStreamBackgroundModifier(color::t_vga_color bg_color);

        ~VGAStreamBackgroundModifier() override = default;

        void operator()(uint8_t &color_byte) const override;
    };

    /**
     * Allow for VGA foreground color output modifications
     */
    class VGAStreamForegroundModifier : public VGAStreamColorModifier {
    public:
        explicit VGAStreamForegroundModifier(uint8_t foreground);

        explicit VGAStreamForegroundModifier(color::vga_color foreground);

        void operator()(uint8_t &color_byte) const override;
    };
} // vga

#endif //KFS_1_VGASTREAMMODIFIER_HPP

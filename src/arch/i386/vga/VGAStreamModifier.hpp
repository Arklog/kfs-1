//
// Created by pierre on 12/18/25.
//

#ifndef KFS_1_VGASTREAMMODIFIER_HPP
#define KFS_1_VGASTREAMMODIFIER_HPP

#include "include/stdint.hpp"

namespace vga {
    class VGACursor;

    class VGAStreamModifier {
    public:
        VGAStreamModifier() = default;
        virtual ~VGAStreamModifier() = default;

        virtual void operator()(VGACursor &cursor) const = 0;
    };

    class VGASetLineModifier : public VGAStreamModifier {
    public:
        explicit VGASetLineModifier(uint16_t line);
        ~VGASetLineModifier() override = default;

        void operator()(VGACursor &cursor) const override;

    private:
        uint16_t _line;
    };
} // vga

#endif //KFS_1_VGASTREAMMODIFIER_HPP
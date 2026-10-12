//
// Created by pierre on 9/15/26.
//

#ifndef KFS_1_SRC_CORE_GDT_GDT_HPP
#define KFS_1_SRC_CORE_GDT_GDT_HPP

#include <include/stdint.hpp>

namespace GDT {
    struct SegmentDescriptor {
        uint16_t limit;
        uint16_t base_low;
        uint8_t base_mid;
        uint8_t access;
        uint8_t limit_and_flags;
        uint8_t base_high;

        uint32_t get_limit() const;
        uint32_t get_base() const;
        uint8_t get_access() const;
        uint8_t get_flags() const;

        void set_limit(uint32_t limit);
        void set_base(uint32_t base);
        void set_access(uint8_t access);
        void set_flags(uint8_t flags);
    };

    template<unsigned int N>
    struct GDT {
        SegmentDescriptor entries[N + 1];
    };

    struct GDTDescriptor {
        unsigned int   offset;
        unsigned short size;

        template<unsigned int T>
        GDTDescriptor(GDT<T> &gdt) {
            offset = &gdt;
            size = sizeof(GDT<T>);
        }
    };

    extern const GDT<4> GDT_v;
}

#endif //KFS_1_SRC_CORE_GDT_GDT_HPP

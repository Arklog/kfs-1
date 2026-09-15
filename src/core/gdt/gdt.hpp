//
// Created by pierre on 9/15/26.
//

#ifndef KFS_1_SRC_CORE_GDT_GDT_HPP
#define KFS_1_SRC_CORE_GDT_GDT_HPP

namespace GDT {
    struct GDTDescriptor {
        unsigned int   offset;
        unsigned short size;
    };

    template<unsigned int N>
    struct GDT {
        GDTDescriptor null_descriptor;
        GDTDescriptor entries[N];
    };
}

#endif //KFS_1_SRC_CORE_GDT_GDT_HPP

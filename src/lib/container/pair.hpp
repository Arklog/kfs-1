//
// Created by pierre on 1/9/26.
//

#ifndef KFS_1__PAIR_HPP
#define KFS_1__PAIR_HPP

namespace container {
    template<typename T1, typename T2>
    struct pair {
        using first_type = T1;
        using second_type = T2;

        T1 first;
        T2 second;

        pair() = default;

        pair(const T1 &first, const T2 &second) : first(first), second(second) {}
    };
}

#endif //KFS_1__PAIR_HPP
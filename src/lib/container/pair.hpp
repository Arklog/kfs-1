//
// Created by pierre on 1/9/26.
//

#ifndef KFS_1__PAIR_HPP
#define KFS_1__PAIR_HPP

namespace container {
    /**
     * A combination of two elements.
     *
     * @tparam T1 type of the first element
     * @tparam T2 type of the second element
     */
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
//
// Created by pierre on 1/2/26.
//

#ifndef KFS_1_MATH_HPP
#define KFS_1_MATH_HPP

namespace math {
    template<typename T>
    T min(const T &&a, const T &&b) {
        return a < b ? a : b;
    }

    template<typename T>
    T max(const T &&a, const T &&b) {
        return a > b ? a : b;
    }
}

#endif //KFS_1_MATH_HPP

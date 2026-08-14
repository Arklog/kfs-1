//
// Created by pierre on 1/2/26.
//

#ifndef KFS_1_MATH_HPP
#define KFS_1_MATH_HPP

namespace math {
    /**
     * Return the minimum of a and b
     *
     * @tparam T
     * @param a
     * @param b
     *
     * @return The minimum value between a and b
     *
     * @snippet math.cpp math min
     */
    template<typename T>
    constexpr T min(const T &&a, const T &&b) {
        return a < b ? a : b;
    }

    /**
     * Return the maximum of a and b
     *
     * @tparam T
     * @param a
     * @param b
     *
     * @return The maximum value between a and b
     *
     * @snippet math.cpp math max
     */
    template<typename T>
    constexpr T max(const T &&a, const T &&b) {
        return a > b ? a : b;
    }
}

#endif //KFS_1_MATH_HPP

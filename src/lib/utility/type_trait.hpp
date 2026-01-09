//
// Created by pierre on 1/8/26.
//

#ifndef KFS_1__TYPE_TRAIT_HPP
#define KFS_1__TYPE_TRAIT_HPP

namespace utility {
    /**
     * Check if T and U are of the same type
     * @tparam T
     * @tparam U
     */
    template<typename T, typename U>
    struct is_same {
        static constexpr bool value = false;
    };

    /**
     * Check if T and T are of the same type, surprise YES THEY ARE !!
     * @tparam T
     * @tparam U
     */
    template<typename T>
    struct is_same<T, T> {
        static constexpr bool value = true;
    };

    /**
     * Check if T and U are of the same type
     *
     * @tparam T
     * @tparam U
     */
    template<typename T, typename U>
    concept same_as = is_same<T, U>::value && is_same<U, T>::value;

    /**
     * Check if type T is convertible to type U
     *
     * @tparam T The type to convert
     * @tparam U The type to convert to
     */
    template<typename T, typename U>
    concept convertible_to = requires(T a)
    {
        { U{a} };
    };
}

#endif // KFS_1__TYPE_TRAIT_HPP

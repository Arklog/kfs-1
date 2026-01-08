//
// Created by pierre on 1/8/26.
//

#ifndef KFS_1__TYPE_TRAIT_HPP
#define KFS_1__TYPE_TRAIT_HPP

namespace utility {
    template<typename T, typename U>
    struct is_same {
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_same<T, T> {
        static constexpr bool value = true;
    };

    template<typename T, typename U>
    concept same_as = is_same<T, U>::value && is_same<U, T>::value;
}

#endif // KFS_1__TYPE_TRAIT_HPP

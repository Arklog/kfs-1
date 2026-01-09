//
// Created by pierre on 1/9/26.
//

#ifndef KFS_1__CONCEPT_HPP
#define KFS_1__CONCEPT_HPP

#include "lib/utility/type_trait.hpp"

namespace container {

    /**
     * Concept to check if a type is iterable
     * @tparam T The type to check
     */
    template <typename T>
    concept is_iterable = requires(T a) {
        { a.begin() } -> utility::same_as<decltype(a.end())>;
        { a.end() };
    };

    template<typename T>
    concept is_iterator = requires(T a, T b)
    {
        { ++a } -> utility::same_as<T&>;
        { a++ } -> utility::same_as<T>;
        { --a } -> utility::same_as<T&>;
        { a-- } -> utility::same_as<T>;

        { *a } -> utility::same_as<typename T::reference_type&>;

        { a == b } -> utility::same_as<bool>;
        { a != b } -> utility::same_as<bool>;
        { a > b } -> utility::same_as<bool>;
        { a < b } -> utility::same_as<bool>;
        { a >= b } -> utility::same_as<bool>;
        { a <= b } -> utility::same_as<bool>;

        { a + 1 } -> utility::same_as<T>;
        { a - 1 } -> utility::same_as<T>;
        { a - b } -> utility::same_as<int>;

        {static_cast<typename T::pointer_type>(a)} -> utility::same_as<typename T::pointer_type>;
    };
}

#endif //KFS_1__CONCEPT_HPP
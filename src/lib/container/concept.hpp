//
// Created by pierre on 1/9/26.
//

#ifndef KFS_1__CONCEPT_HPP
#define KFS_1__CONCEPT_HPP

#include "lib/utility/type_trait.hpp"

namespace container {

    /**
     * Check if a type is iterable, eg: have begin() and end() methods
     *
     * @tparam T The type to check
     */
    template <typename T>
    concept is_iterable = requires(T a) {
        { a.begin() } -> utility::same_as<decltype(a.end())>;
        { a.end() };
    };

    /**
     * Check if a type is a valid iterator
     *
     * @tparam T The type to check
     */
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

    /**
     * Check if a type is a valid pair
     *
     * @tparam T The type to check
     */
    template<typename T>
    concept is_pair = requires(T a)
    {
        { a.first } -> utility::same_as<typename T::first_type&>;
        { a.second } -> utility::same_as<typename T::second_type&>;
    };

    /**
     * Check if a type is both a valid iterator and a valid pair
     */
    template<typename T>
    concept is_pair_iterator = is_pair<T> && is_iterator<T>;
}

#endif //KFS_1__CONCEPT_HPP
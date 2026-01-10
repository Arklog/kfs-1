//
// Created by pierre on 1/8/26.
//

#ifndef KFS_1__STATIC_CHECK_HPP
#define KFS_1__STATIC_CHECK_HPP
#include "lib/utility/type_trait.hpp"
#include "lib/utility/utility.hpp"

template<typename T>
concept is_basic_container = requires (T t, const T ct)
{
    // check iterator
    {t.begin()} -> utility::same_as<typename T::iterator>;
    {ct.begin()} -> utility::same_as<typename T::const_iterator>;
    {ct.cbegin()} -> utility::same_as<typename T::const_iterator>;
    {t.end()} -> utility::same_as<typename T::iterator>;
    {ct.end()} -> utility::same_as<typename T::const_iterator>;
    {ct.cend()} -> utility::same_as<typename T::const_iterator>;
};

#endif // KFS_1__STATIC_CHECK_HPP

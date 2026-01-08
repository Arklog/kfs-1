//
// Created by pierre on 1/8/26.
//

#ifndef KFS_1__STATIC_CHECK_HPP
#define KFS_1__STATIC_CHECK_HPP

template<typename T>
concept is_basic_container_c = requires (T t, const T ct)
{
    // check iterator
    {t.begin()};
    {ct.begin()};
    {ct.cbegin()};
    {t.end()};
    {ct.end()};
    {ct.cend()};
};

#endif // KFS_1__STATIC_CHECK_HPP

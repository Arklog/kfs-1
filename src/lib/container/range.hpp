//
// Created by pierre on 1/6/26.
//

#ifndef KFS_1_RANGE_HPP
#define KFS_1_RANGE_HPP

#include "concept.hpp"
#include "iterator/PairIterator.hpp"

namespace container {
    /**
     * A range of values, is used in conjunction with range based for loop.
     *
     * @tparam T The type of iterator being iterated
     *
     * @snippet example.cpp container_range_example
     */
    template<is_iterator T>
    struct range {
        using value_type = T;

        range(const T& begin,const  T& end): _begin{begin}, _end{end} {}

        T begin() const {
            return _begin;
        }

        T end() const {
            return _end;
        }

    private:
        T _begin;
        T _end;
    };

    template<is_iterator T, is_iterator U>
    struct dual_range {
        using iterator_type = typename container::PairIterator<pair<T, U>>;
        using value_type = iterator_type::value_type;

        dual_range(value_type item, unsigned int len): _begin{item}, _end{_begin + len} {}

        iterator_type begin() const {
            return _begin;
        }

        iterator_type end() const {
            return _end;
        }

    private:
        iterator_type _begin;
        iterator_type _end;

    };
}

#endif //KFS_1_RANGE_HPP

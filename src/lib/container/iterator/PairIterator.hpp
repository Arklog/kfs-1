//
// Created by pierre on 1/9/26.
//

#ifndef KFS_1__PAIRITERATOR_HPP
#define KFS_1__PAIRITERATOR_HPP

#include "pair.hpp"
#include "concept.hpp"
#include "iterator/Iterator.hpp"

namespace container::iterator {
    template<is_pair T>
    class PairIterator: public IteratorBase<PairIterator<T>, T, T *, T&>{
        static_assert(is_iterator<typename T::first_type> && is_iterator<typename T::second_type>, "pair elements should be iterators");

    public:
        using first_type = typename T::first_type;
        using second_type = typename T::second_type;
        using value_type = typename IteratorBase<PairIterator<T>, T, T *, T&>::value_type;
        using pointer_type = typename IteratorBase<PairIterator<T>, T, T *, T&>::pointer_type;
        using reference_type = typename IteratorBase<PairIterator<T>, T, T *, T&>::reference_type;

        T pair;
        first_type& first;
        second_type& second;

        PairIterator(): pair{}, first{pair.first}, second{pair.second} {}
        // explicit PairIterator(const value_type& pair): pair{pair}, first{pair.first}, second{pair.second} {}
        PairIterator(const first_type& first,const second_type& second): pair{first, second}, first{pair.first}, second{pair.second} {}
        PairIterator(const PairIterator& other): pair{other.pair}, first{pair.first}, second {pair.second} {}

        PairIterator& operator=(const PairIterator& other) override {
            pair = other.pair;
            return *this;
        }

        bool operator==(const PairIterator &other) const override {
            return first == other.first && second == other.second;
        }

        bool operator!=(const PairIterator &other) const override {
            return !(*this == other);
        }

        bool operator==(pointer_type other) const override {
            return first == other->first && second == other->second;
        };

        bool operator!=(pointer_type other) const override {
            return !(*this == other);
        };

        bool operator>(const PairIterator &other) const override {
            return first > other.first && second > other.second;
        }

        bool operator<(const PairIterator &other) const override {
            return first < other.first && second < other.second;
        }

        bool operator>=(const PairIterator &other) const override {
            return first >= other.first && second >= other.second;
        }

        bool operator<=(const PairIterator &other) const override {
            return first <= other.first && second <= other.second;
        }

        PairIterator& operator++() override {
            ++first;
            ++second;
            return *this;
        }

        PairIterator operator++(int) override {
            auto tmp = *this;
            ++first;
            ++second;
            return tmp;
        }

        PairIterator& operator--() override {
            --first;
            --second;
            return *this;
        }

        PairIterator operator--(int) override {
            auto tmp = *this;
            --first;
            --second;
            return tmp;
        }

        PairIterator operator+(int v) const override {
            auto tmp = *this;
            tmp.first += v;
            tmp.second += v;
            return tmp;
        }

        PairIterator operator+(unsigned v) const {
            auto tmp = *this;
            tmp.first += v;
            tmp.second += v;
            return tmp;
        }

        PairIterator operator-(int v) const override {
            auto tmp  = *this;
            tmp.first -= v;
            tmp.second -= v;
            return tmp;
        }

        int operator-(const PairIterator &other) const override {
            auto a = first - other.first;
            auto b = second - other.second;

            return a > b ? a : b;
        };

        PairIterator& operator+=(int v) override {
            first += v;
            second += v;
            return *this;
        }

        PairIterator& operator-=(int v) override {
            first -= v;
            second -= v;
            return *this;
        }

        reference_type operator*() const override {
            return const_cast<reference_type>(pair);
        }

        explicit operator pointer_type() const override {
            return const_cast<pointer_type>(&pair);
        }
    };
}

#endif //KFS_1__PAIRITERATOR_HPP
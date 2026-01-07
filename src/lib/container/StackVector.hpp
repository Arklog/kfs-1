//
// Created by pierre on 1/4/26.
//

#ifndef KFS_1_STACKVECTOR_HPP
#define KFS_1_STACKVECTOR_HPP

#include "Array.hpp"
#include "range.hpp"

namespace container {
    template<typename T, unsigned int N>
    class StackVector : public Array<T, N> {
    public:
        using iterator       = Array<T, N>::iterator;
        using const_iterator = Array<T, N>::const_iterator;
        using size_type      = Array<T, N>::size_type;

        StackVector() :
            Array<T, N>(), _size{0} {
        }

        iterator end() override {
            return this->begin() + _size;
        }

        iterator cend() const override {
            return this->cbegin() + _size;
        }

        const size_type size() const override {
            return _size;
        }

        /**
         * Add an element to the end of the vector and adjust the size accordingly.
         *
         * @param item
         *
         * @return An iterator to the newly inserted element or end() on failure.
         */
        iterator push_bash(T &&item) {
            if (_size == N)
                return end();
            *(this->begin() + _size) = item;
            return this->begin() + _size++;
        }

        /**
         * Emplace an element at the end of the vector and adjust the size accordingly.
         *
         * @tparam Args
         * @param args
         *
         * @return An iterator to the newly emplaced element or end() on failure.
         */
        template<typename... Args>
        iterator emplace_back(Args... args) {
            static_assert(T(args...), "No constructor matching argument list");

            if (_size == N)
                return end();
            new(static_cast<T *>(this->begin() + _size)) T(args...);
            return this->begin() + _size++;
        }

        /**
         * Erase the element at the given position.
         *
         * @param position
         *
         * @return begin() on success, end() on failure
         */
        iterator erase(iterator position) {
            if (position < this->begin() || position > this->end())
                return end();

            for (auto &it: container::range{position, end() - 1}) {
                *it = utility::move(*(it + 1));
            }
            --_size;

            return this->begin();
        }

        /**
         * Erase the range [_begin, _end[ from the container.
         *
         * @param _begin
         * @param _end
         *
         * @return begin() on success or end() on failure
         */
        iterator erase(iterator _begin, iterator _end) {
            if (_begin > _end)
                return end();

            auto length = _end - _begin;
            for (auto i: container::range{_begin, _end}) {
                *i = utility::move(*(i + length));
            }

            _size -= length;
            return this->begin();
        }

    private:
        unsigned int _size;
    };
} // container

#endif //KFS_1_STACKVECTOR_HPP

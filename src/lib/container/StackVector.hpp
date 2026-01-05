//
// Created by pierre on 1/4/26.
//

#ifndef KFS_1_STACKVECTOR_HPP
#define KFS_1_STACKVECTOR_HPP

#include "Array.hpp"

namespace container {
    template<typename T, unsigned int N>
    class StackVector : public Array<T, N> {
    public:
        using iterator       = Array<T, N>::iterator;
        using const_iterator = Array<T, N>::const_iterator;
        using size_type      = Array<T, N>::size_type;

        StackVector() : Array<T, N>(), _size{0} {
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

        iterator erase(iterator position) {
            if (position < this->begin() || position > this->end())
                return end();

            if constexpr (!__is_trivially_constructible(T)) {
                *(position).~T();

                auto iter = position;
                while (iter != this->end()) {
                }
            } else {
                memmove(static_cast<T *>(position), static_cast<T *>(position + 1), end() - position);
            }

            return position;
        }

    private:
        unsigned int _size;
    };
} // container

#endif //KFS_1_STACKVECTOR_HPP

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

        const_iterator cend() const override {
            return this->cbegin() + _size;
        }

        const size_type size() const override {
            return _size;
        }

        /**
         * Insert value at position. If the vector is full the last element will be removed.
         *
         * @param position The position at which to insert the element
         * @param value The value to insert
         *
         * @return The position of the inserted element or
         */
        iterator insert(iterator position, T &&value) override {
            if (!_validate_position(position) || _size == N)
                return end();

            for (auto iter = end(); iter >= position; ++iter) {
                *iter = utility::move(*(iter - 1));
            }

            *position = utility::move(value);
            ++_size;

            return position;
        }

        iterator insert(iterator position, iterator _begin, iterator _end) override {
            auto length = _end - _begin;

            if (length > N - _size)
                return end();

            if (_own_iterator(_begin) && _own_iterator(_end))
                _insert_overlap(position, _begin, _end);

            // displace elements
            auto iter = end() - length -1;
            while (iter >= position) {
                *(iter + length) = utility::move(*iter);
                --iter;
            }

            // copy elements from range
            iter = position;
            for (const auto &i: container::range{_begin, _end}) {
                *(iter++) = i;
            }

            return position;
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
         * @return An iterator to the newly emplaced element or end() if the StackVector is full.
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
            if (!_validate_position(position))
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
            if (_begin > _end || !_own_iterator(_begin) || !_own_iterator(_end))
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

        /**
         * Check if the given iterator belong to this StackVector
         *
         * @param iter The iterator to check
         *
         * @return true if iter is in range [begin(), end()], false otherwise
         */
        bool _own_iterator(iterator iter) const {
            return iter >= this->begin() && iter <= this->end();
        }

        /**
         * Check if the given iterator is a valid read/write iterator.
         *
         * @param iter The iterator to validate
         *
         * @return true if iter is in [begin(), end()[, false otherwise
         */
        bool _validate_position(iterator iter) const {
            return iter >= this->begin() && iter < this->end();
        }

        /**
         * Insert this vector into itself
         *
         * @param position
         * @param _begin
         * @param _end
         * @return
         */
        iterator _insert_overlap(iterator position, iterator _begin, iterator _end) {
            auto length = _end - _begin;
            auto distance = _begin - position;

            if (!distance)
                return position;

            auto iter = position;
            for (const auto& i: container::range{_begin, _end}) {
                utility::swap(*iter, i);
                ++iter;
            }

            return position;
        }
    };
} // container

#endif //KFS_1_STACKVECTOR_HPP

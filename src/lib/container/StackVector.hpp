//
// Created by pierre on 1/4/26.
//

#ifndef KFS_1_STACKVECTOR_HPP
#define KFS_1_STACKVECTOR_HPP

#include "Array.hpp"
#include "lib/utility/type_trait.hpp"
#include "range.hpp"

namespace container {
    template<typename T, unsigned int N>
    class StackVector : public Array<T, N> {
    public:
        using iterator       = Array<T, N>::iterator;
        using const_iterator = Array<T, N>::const_iterator;
        using size_type      = Array<T, N>::size_type;

        constexpr StackVector() :
            Array<T, N>(), _size{0} {
        }

        template<typename ...Args>
        constexpr StackVector(Args ...args): Array<T, N>(utility::forward<Args>(args)...), _size(sizeof...(args)) {
            static_assert(sizeof...(args) <= N, "To many arguments");
            static_assert((utility::convertible_to<decltype(args), T> && ...), "Invalid type");
        }

        StackVector(iterator begin, iterator end) : Array<T, N>(), _size{0} {
            int idx = 0;
            for (const auto &i: container::range{begin, end}) {
                this->_data[idx++] = i;
                if (idx == N) {
                    _size = N;
                    return ;
                }
            }

            _size = end - begin;
        }

        ~StackVector() = default;

        StackVector(const StackVector& other) : Array<T, N>(), _size{other._size} {
            int idx = 0;

            for (const auto &i: other) {
                this->_data[idx++] = i;
            }
        }

        StackVector(StackVector &&other) noexcept : Array<T, N>(), _size{utility::move(other._size)} {
            int idx = 0;

            for (auto &i: other) {
                this->_data[idx++] = utility::move(i);
            }
        }

        StackVector& operator=(const StackVector& other) {
            if (this == &other)
                return *this;

            _size = other._size;

            int idx = 0;
            for (const auto &i: other) {
                this->_data[idx++] = i;
            }

            return *this;
        }

        iterator begin() override {
            return Array<T, N>::begin();
        }

        const_iterator begin() const override {
            return Array<T, N>::begin();
        }

        iterator end() override {
            return this->begin() + _size;
        }

        const_iterator end() const override {
            return cend();
        }

        const_iterator cend() const override {
            return this->cbegin() + _size;
        }

        size_type size() const override {
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
        iterator insert(iterator position, T &value) override {
            if (!_own_iterator(position) || _size == N)
                return end();

            for (auto iter = end(); iter > position; --iter) {
                *iter = utility::move(*(iter - 1));
            }

            *position = value;
            ++_size;

            return position;
        }

        /**
         * Insert value at position. If the vector is full the last element will be removed.
         *
         * @param position The position at which to insert the element
         * @param value The value to insert
         *
         * @return The position of the inserted element or end() if insertion failed.
         *
         * @warning Insertion will fail if:
         * - position does not belong to this StackVector
         * - the StackVector is full
         */
        iterator insert(iterator position, T &&value) override {
            if (!_own_iterator(position) || _size == N)
                return end();

            for (auto iter = end(); iter > position; --iter) {
                *iter = utility::move(*(iter - 1));
            }

            *position = utility::move(value);
            ++_size;

            return position;
        }

        /**
         * Insert a range of elements at the given position.
         * If the vector does not have enough space to accommodate all new elements, the insertion fails.
         *
         * @param position
         * @param _begin
         * @param _end
         *
         * @return an iterator to the newly inserted item or end() on failure
         *
         * @warning Will fail if:
         * - position does not belong to this StackVector
         * - the StackVector does not have enougth place to accomodate the elements
         */
        iterator insert(iterator position, iterator _begin, iterator _end) override {
            auto length = _end - _begin;
            if (!_own_iterator(position) || length + size() > N)
                return end();

            if (_own_iterator(_begin) && _own_iterator(_end))
                return _insert_overlap(position, _begin, _end);

            // displace elements
            for (auto iter = end() + length - 1; iter > position; --iter) {
                *iter = utility::move(*(iter - length));
            }

            // copy elements from range
            auto iter = position;
            for (const auto &i: container::range{_begin, _end}) {
                *(iter++) = i;
            }

            _size += length;
            return position;
        }

        /**
         * Add an element to the end of the vector and adjust the size accordingly.
         *
         * @param item
         *
         * @return An iterator to the newly inserted element or end() on failure.
         *
         * @warning Will fail if the StackVector is full
         */
        iterator push_bash(T &&item) {
            if (_size == N)
                return end();

            *(this->begin() + _size) = item;
            return this->begin() + _size++;
        }

        iterator push_bash(const T& item) {
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
         * @param position The position of the element to erase
         *
         * @return begin() on success, end() on failure.
         */
        iterator erase(iterator position) {
            if (!_validate_position(position) || size() == 0)
                return end();

            auto iter = position;
            while (iter < end() - 1) {
                *iter = utility::move(*(iter + 1));
                ++iter;
            }

            *(end() - 1) = T{};
            --_size;

            return this->begin();
        }

        iterator erase(unsigned position) {
            return erase(this->begin() + position);
        }

        /**
         * Erase the range [_begin, _end[ from the container.
         *
         * @param _begin The position of the first element to erase
         * @param _end The position after the last element to erase
         *
         * @return begin() on success or end() on failure
         */
        iterator erase(iterator _begin, iterator _end) {
            if (_begin > _end || !_validate_position(_begin) || !_own_iterator(_end))
                return end();

            auto length = _end - _begin;
            auto iter = _begin;
            while (iter + length < end()) {
                *iter = utility::move(*(iter + length));
                ++iter;
            }

            _size -= length;
            return this->begin();
        }

        void clear() {
            for (auto& item: *this) {
                item = T{};
            }
            _size = 0;
        }

        /**
         * Get the maximum capacity of the StackVector
         *
         * @return The maximum number of elements the StackVector can hold
         */
        constexpr unsigned capacity() const {
            return N;
        }

        /**
         * Get the available space in the StackVector
         *
         * @return The number of elements that can still be added to the StackVector
         */
        unsigned available_space() const {
            return N - _size;
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
        bool _own_iterator(const_iterator iter) const {
            return iter >= this->begin() && iter <= this->end();
        }

        /**
         * Check if the given iterator is a valid read/write iterator.
         *
         * @param iter The iterator to validate
         *
         * @return true if iter is in [begin(), end()[, false otherwise
         */
        bool _validate_position(const_iterator iter) const {
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
            auto distance = _begin - position;

            if (!distance)
                return position;

            auto iter = position;
            for (auto& i: container::range{_begin, _end}) {
                utility::swap(*iter, i);
                ++iter;
            }

            return position;
        }
    };
} // container

#endif //KFS_1_STACKVECTOR_HPP

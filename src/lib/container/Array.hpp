//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_KARRAY_HPP
#define KFS_1_KARRAY_HPP

#include "Container.hpp"
#include "iterator/ContiguousIterator.hpp"
#include "lib/utility/utility.hpp"

namespace container {
    template<typename T, unsigned int N>
    class Array : public Container<T, ContiguousIterator<T>, ContiguousConstIterator<T> > {
    public:
        using iterator       = ContiguousIterator<T>;
        using const_iterator = ContiguousConstIterator<T>;
        using size_type      = Container<T, iterator, const_iterator>::size_type;
        using value_type     = Container<T, iterator, const_iterator>::value_type;

        Array() = default;

        /**
         * Create array with elements
         *
         * @tparam Args
         * @param args
         */
        template<typename... Args>
        Array(Args... args) :
            _data{utility::forward<Args>(args)...} {
            static_assert(sizeof...(Args) <= N, "Too many elements");
        }

        /**
         * Create array with elements from _begin to _end at the beginning
         *
         * @param _begin
         * @param _end
         */
        explicit Array(iterator _begin, iterator _end) {
            auto i = 0;
            while (_begin < _end && i < N) {
                _data[i++] = *(_begin++);
            }
        }

        /**
         * Copy constructor
         * @param other
         */
        Array(const Array &other) {
            auto idx = 0;
            for (const auto &i: other) {
                _data[idx++] = i;
            }
        }

        /**
         * Move constructor
         * @param other
         */
        Array(Array &&other) noexcept {
            auto idx = 0;

            for (auto &i: other) {
                _data[idx++] = utility::move(i);
            }
        }

        Array& operator=(const Array &other) {
            auto iter = this->begin();
            for (const auto& i: other) {
                *iter = i;
                ++iter;
            }

            return *this;
        }

        Array &operator=(Array &&other) noexcept {
            auto iter = this->begin();
            for (auto &i: other) {
                *iter = utility::move(i);
                ++iter;
            }

            return *this;
        }

        /**
         * Allow concatenation of two Array of size N and N1
         *
         * @tparam N1 The size of the second array
         * @param other The array to concatenate with current array
         *
         * @return An array of size N + N1, being the concatenation of this array and other
         */
        template<unsigned N1>
        Array<T, N + N1> operator+(const Array<T, N1> &other) const {
            Array<T, N + N1> result;

            auto iter = result.begin();
            for (const auto i: *this) {
                *iter = utility::move(i);
                ++iter;
            }

            for (const auto i: other) {
                *iter = utility::move(i);
                ++iter;
            }

            return result;
        }

        T &operator[](unsigned index) { return _data[index]; }

        const T &operator[](unsigned index) const { return _data[index]; }

        iterator begin() override {
            return iterator(this->_data);
        }

        const_iterator begin() const override {
            return cbegin();
        }

        iterator end() override {
            return iterator(this->_data + N);
        }

        const_iterator end() const override {
            return cend();
        }

        const_iterator cbegin() const override {
            return const_iterator(this->_data);
        }

        const_iterator cend() const override {
            return const_iterator(this->_data + N);
        }

        T *data() const override {
            return const_cast<T *>(this->_data);
        }

        size_type size() const override { return N; };

        /**
         * Construct an element in place of position iter
         *
         * @tparam Args
         * @param position The position at which to construct the element
         * @param args The constructor argument
         *
         * @return An iterator to the constructed element or end() if position does not belong to this array
         */
        template<typename... Args>
        iterator emplace(iterator position, Args &&... args) {
            if (!_validate_position(position))
                return end();

            new(static_cast<T *>(position)) T(utility::move(args)...);
            return position;
        }

        /**
         * Move an element in place of position position
         *
         * @param position The position at which to move the element
         * @param value The element to move
         *
         * @return An iterator to the element or end() if position does not belong to this array
         */
        iterator emplace(iterator position, T &&value) {
            if (!_validate_position(position))
                return end();

            *position = utility::move(value);
            return position;
        }

        iterator insert(iterator position, const T &value) override {
            if (!_validate_position(position))
                return end();

            auto iter = end() - 1;
            while (iter != position) {
                *iter = utility::move(*(iter - 1));
                --iter;
            }

            *iter = value;

            return position;
        }

        iterator insert(iterator position, T &&value) override {
            if (!_validate_position(position))
                return end();

            auto iter = end() - 1;
            while (iter != position) {
                *iter = utility::move(*(iter - 1));
                --iter;
            }

            *position = utility::move(value);

            return position;
        }

        /**
         * Insert the range [_begin, _end[ at position. Elements will be displaced in order to create the place to store
         * the range.
         *
         * @param position
         * @param _begin
         * @param _end
         *
         * @warning Will fail if:
         * - position >= end()
         * - position < begin()
         * - _begin < _end
         * - not enough place to store the range
         *
         * @return An iterator to the inserted elements position or end() in case of failure.
         */
        iterator insert(iterator position, iterator _begin, iterator _end) override {
            if (!_validate_position(position) || _begin > _end || _end - _begin > end() - position)
                return end();

            // different logic if inserting into itself
            if (_own_iterator(_begin) && _own_iterator(_end))
                return _insert_overlap(position, _begin, _end);

            auto remaining_till_end = end() - position; // remaining elements till end from position
            auto new_elems = _end - _begin; // number of new elements to insert
            auto to_displace = remaining_till_end - new_elems; // number of element that will need to be displaced

            // displace elements to make room
            auto iter = end() - 1;
            while (to_displace--) {
                *iter = utility::move(*(iter - new_elems));
                --iter;
            }

            // copy new elements
            iter = position;
            while (_begin != _end) {
                *iter = *_begin;
                ++_begin;
                ++iter;
            }

            return position;
        }

    protected:
        T _data[N];

    private:
        iterator _insert_overlap(iterator position, iterator _begin, iterator _end) {
            auto new_elems = _end - _begin;
            auto distance  = _begin - position;

            auto src_iter = _begin;
            auto dst_iter = src_iter - distance;

            // displace elements
            while (new_elems--) {
                utility::swap(*src_iter, *dst_iter);
                ++src_iter;
                ++dst_iter;
            }

            return position;
        }

        /**
         * Check if the provided iterator is owned by this array
         *
         * @param iter
         *
         * @return true if the iterator is in [begin(), end()], false otherwise
         */
        bool _own_iterator(const_iterator iter) {
            return iter >= begin() && iter <= end();
        }

        /**
         * Check if the provided iterator is a valid position.
         *
         * @param iter
         *
         * @return true if the iterator is in [begin(), end()[, false otherwise
         */
        bool _validate_position(const_iterator iter) const {
            return iter >= begin() && iter < end();
        }
    };
}


#endif // KFS_1_KARRAY_HPP

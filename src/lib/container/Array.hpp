//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_KARRAY_HPP
#define KFS_1_KARRAY_HPP

#include "Container.hpp"
#include "Iterator.hpp"
#include "lib/math/math.hpp"
#include "lib/str/KString.hpp"

namespace container {
    template<typename T, unsigned int N>
    class Array : public Container<T, ContiguousIterator<T>, ContiguousIterator<const T> > {
    public:
        using iterator       = ContiguousIterator<T>;
        using const_iterator = ContiguousIterator<const T>;
        using size_type      = Container<T, iterator, const_iterator>::size_type;

        Array() = default;

        Array(T data[N]) {
            for (unsigned i = 0; i < N; ++i) {
                this->_data[i] = data[i];
            }
        }

        template<typename... Args>
        Array(Args... args) :
            _data{args...} {
        }

        template<unsigned N1>
        Array<T, N + N1> operator+(const Array<T, N1> &other) const {
            Array<T, N + N1> result;

            kstring::memcpy(result.data(), this->data(), this->size() * sizeof(T));
            kstring::memcpy(result.data() + this->size(), other.data(), other.size() * sizeof(T));

            return result;
        }

        T &operator[](unsigned index) { return _data[index]; }

        const T &operator[](unsigned index) const { return _data[index]; }

        iterator begin() override {
            return iterator(this->_data);
        }

        iterator end() override {
            return iterator(this->_data + N);
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

        template<typename... Args>
        void emplace(const iterator &iter, Args &&... args) {
            new(static_cast<T *>(iter)) T(args...);
        }

        iterator insert(iterator iter, T &&value) override {
            if (iter >= end() || iter < begin())
                return end();

            const auto distance = iter - begin();

            memmove(_data + distance + 1, _data + distance, (end() - iter) * sizeof(T));
            *iter = value;

            return iter;
        }

        /**
         * Insert the range [_begin, _end] at position. Elements will be displaced in order to create the place to store
         * the range being deleted when out of bound.
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
            if (position >= end() || position < begin() || _begin > _end)
                return end();

            auto distance           = position - begin();
            auto remaining_till_end = end() - position;
            auto new_elems          = _end - _begin;
            auto to_displace        = remaining_till_end - new_elems;

            // Avoid overflow
            if (new_elems > remaining_till_end)
                return end();

            memmove(_data + distance + new_elems, _data + distance, to_displace * sizeof(T));
            memcpy(_data + distance, static_cast<T *>(_begin), new_elems * sizeof(T));

            return position;
        }

    private:
        T _data[N];
    };
}


#endif // KFS_1_KARRAY_HPP

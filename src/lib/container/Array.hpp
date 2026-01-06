//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_KARRAY_HPP
#define KFS_1_KARRAY_HPP

#include "Container.hpp"
#include "Iterator.hpp"
#include "range.hpp"
#include "lib/math/math.hpp"
#include "lib/str/KString.hpp"
#include "lib/utility.hpp"

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

        Array(iterator _begin, iterator _end) {
            auto i = 0;
            while (_begin < _end) {
                _data[i++] = *(_begin++);
            }
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

        iterator insert(iterator position, T &&value) override {
            if (position >= end() || position < begin())
                return end();

            const auto distance = position - begin();

            if constexpr (__is_trivially_copyable(T)) {
                memmove(_data + distance + 1, _data + distance, (end() - position - 1) * sizeof(T));
            } else {
                auto iter = end() - 1;
                while (iter != position) {
                    *iter = utility::move(*(iter - 1));
                    --iter;
                }
            }

            *position = utility::move(value);

            return position;
        }

        /**
         * Insert the range [_begin, _end[ at position. Elements will be displaced in order to create the place to store
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
            if (position >= end() || position < begin() || _begin > _end || _end - _begin > end() - position)
                return end();

            // different logic if inserting into itself
            if (_begin >= begin() && _begin < end())
                return _insert_overlap(position, _begin, _end);

            auto remaining_till_end = end() - position; // remaining elements till end from position
            auto new_elems = _end - _begin; // number of new elements to insert
            auto to_displace = remaining_till_end - new_elems; // number of element that will need to be displaced

            auto iter = end() - 1;

            while (to_displace--) {
                *iter = utility::move(*(iter - new_elems));
                --iter;
            }

            iter = position;
            while (_begin != _end) {
                *iter = *_begin;
                ++_begin;
                ++iter;
            }

            return position;
        }

    private:
        T _data[N];

        iterator _insert_overlap(iterator position, iterator _begin, iterator _end) {
            Array<T, N> tmp{_begin, _end};

            auto new_elems = _end - _begin;

            // temporarily store elements to be inserted into temp buffer
            for (auto i = 0; i < new_elems; ++i) {
                tmp[i] = utility::move(*(_begin + i));
            }

            if (_begin > position) {
                auto iter = _end - 1;

                // displace elements
                while (iter - new_elems >= begin()) {
                    *(iter) = utility::move(*(iter - new_elems));
                    --iter;
                }

                // reinsert element from temp buffer
                for (auto i = 0; i < new_elems; ++i) {
                    *(position + i) = utility::move(tmp[i]);
                }
            } else {
                return end();
            }

            return position;
        }
    };
}


#endif // KFS_1_KARRAY_HPP

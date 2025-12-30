//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_KARRAY_HPP
#define KFS_1_KARRAY_HPP

#include "Container.hpp"
#include "Iterator.hpp"
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

    private:
        T _data[N];
    };
}


#endif // KFS_1_KARRAY_HPP

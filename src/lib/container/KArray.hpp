//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_KARRAY_HPP
#define KFS_1_KARRAY_HPP

#include "Container.hpp"

namespace container {
    template<typename T, unsigned N>
    class KArray : public Container<T, ContiguousIterator<T>, ContiguousIterator<const T> > {
    public:
        using iterator       = ContiguousIterator<T>;
        using const_iterator = ContiguousIterator<const T>;

        KArray() = default;

        KArray(T data[N]) {
            for (unsigned i = 0; i < N; ++i) {
                this->data[i] = data[i];
            }
        }

        template<unsigned N1>
        KArray<T, N + N1> operator+(const KArray<T, N1> &other) const {
            KArray<T, N + N1> result;

            // copy this
            for (unsigned i = 0; i < N; ++i) {
                result[i] = this->data[i];
            }

            // copy other
            for (unsigned i = 0; i < N1; ++i) {
                result[N + i] = other[i];
            }

            return result;
        }

        T &operator[](unsigned index) { return data[index]; }

        const T &operator[](unsigned index) const { return data[index]; }

        iterator begin() override {
            return iterator(this->data);
        }

        iterator end() override {
            return iterator(this->data + N);
        }

        const_iterator cbegin() const override {
            return const_iterator(this->data);
        }

        const_iterator cend() const override {
            return const_iterator(this->data + N);
        }

    private:
        T data[N];
    };
}


#endif // KFS_1_KARRAY_HPP

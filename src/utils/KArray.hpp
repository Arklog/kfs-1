//
// Created by pierre on 12/17/25.
//

#ifndef KFS_1_KARRAY_HPP
#define KFS_1_KARRAY_HPP

template<typename T, unsigned N>
class KArray
{
private:
    T data[N];

public:
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
            result.data[i] = this->data[i];
        }

        // copy other
        for (unsigned i = 0; i < N1; ++i) {
            result.data[N + i] = other.data[i];
        }

        return result;
    }
};


#endif //KFS_1_KARRAY_HPP
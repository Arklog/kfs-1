//
// Created by pierre on 1/6/26.
//

#ifndef KFS_1_UTILITY_HPP
#define KFS_1_UTILITY_HPP

namespace utility {
    template<typename T>
    struct remove_reference {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T &> {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T &&> {
        using type = T;
    };

    template<typename T>
    typename remove_reference<T>::type &&move(T &&a) {
        return static_cast<remove_reference<T>::type &&>(a);
    }

    template<typename T>
    T &&forward(typename remove_reference<T>::type &a) {
        return static_cast<remove_reference<T>::type &&>(a);
    }

    template<typename T>
    constexpr T &&forward(typename remove_reference<T>::type &&a) {
        return static_cast<remove_reference<T>::type &&>(a);
    }

    template<typename T>
    void swap(T &&a, T &&b) {
        typename remove_reference<T>::type c = utility::move(a);
        a                                    = utility::move(b);
        b                                    = utility::move(c);
    }

    template<typename T>
    void swap(T &a, T &b) {
        T c = utility::move(a);
        a   = utility::move(b);
        b   = utility::move(c);
    }
}

#endif //KFS_1_UTILITY_HPP

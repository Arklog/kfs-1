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
    void swap(typename remove_reference<T>::type &&a, typename remove_reference<T>::type &&b) {
        typename remove_reference<T>::type c = move(a);
        a                                    = move(b);
        b                                    = move(c);
    }
}

#endif //KFS_1_UTILITY_HPP

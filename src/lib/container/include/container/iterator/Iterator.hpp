//
// Created by pierre on 12/29/25.
//

#ifndef KFS_1_ITERATOR_HPP
#define KFS_1_ITERATOR_HPP

namespace container {
    /**
     * Base iterator class
     * @tparam Derived
     * @tparam T The type of data, the iterator point on
     * @tparam Pointer The data pointer type
     * @tparam Reference The data reference type
     */
    template<typename Derived, typename T, typename Pointer, typename Reference>
    class IteratorBase {
    public:
        using value_type = T;
        using pointer_type = Pointer;
        using reference_type = Reference;

        ~IteratorBase() = default;

        virtual Derived& operator=(const Derived& other) = 0;

        virtual bool operator==(const Derived &other) const = 0;

        virtual bool operator!=(const Derived &other) const = 0;

        virtual bool operator==(Pointer other) const = 0;

        virtual bool operator!=(Pointer other) const = 0;

        virtual bool operator >(const Derived &other) const = 0;

        virtual bool operator <(const Derived &other) const = 0;

        virtual bool operator >=(const Derived &other) const = 0;

        virtual bool operator <=(const Derived &other) const = 0;

        virtual Derived &operator++() = 0;

        virtual Derived operator++(int) = 0;

        virtual Derived &operator--() = 0;

        virtual Derived operator--(int) = 0;

        virtual Derived operator+(int) const = 0;

        virtual Derived operator-(int) const = 0;

        virtual int operator-(const Derived &) const = 0;

        virtual Derived& operator+=(int) = 0;

        virtual Derived& operator-=(int) = 0;

        virtual reference_type operator*() const = 0;

        virtual explicit operator pointer_type() const = 0;
    };
} // container

#endif //KFS_1_ITERATOR_HPP

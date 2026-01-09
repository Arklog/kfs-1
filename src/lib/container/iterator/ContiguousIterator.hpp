//
// Created by pierre on 1/8/26.
//

#ifndef KFS_1__CONTIGUOUSITERATOR_HPP
#define KFS_1__CONTIGUOUSITERATOR_HPP
#include "Iterator.hpp"

namespace container {
    template<typename T, typename Pointer, typename Reference>
    class ContiguousIterator;

    template<typename T, typename Pointer = const T *, typename Reference = const T &>
    class ContiguousConstIterator: public IteratorBase<ContiguousConstIterator<T, Pointer, Reference>, const T, Pointer, Reference> {
    private:
        Pointer _item;

    public:
        ContiguousConstIterator() = delete;

        explicit ContiguousConstIterator(Pointer item) :
                _item(item) {
        }

        ContiguousConstIterator(const ContiguousIterator<T, T*, T&> &other): _item{&(*other)} {}

        ContiguousConstIterator(const ContiguousConstIterator &other) : _item(other._item) {}

        ContiguousConstIterator &operator=(const ContiguousConstIterator& other) override {
            _item = other._item;
            return *this;
        }

        bool operator==(const ContiguousConstIterator &other) const override {
            return _item == other._item;
        }

        bool operator!=(const ContiguousConstIterator &other) const override {
            return _item != other._item;
        }

        bool operator==(Pointer other) const override {
            return _item == other;
        }

        bool operator!=(Pointer other) const override {
            return _item != other;
        }

        bool operator>(const ContiguousConstIterator &other) const override {
            return _item > other._item;
        }

        bool operator<(const ContiguousConstIterator &other) const override {
            return _item < other._item;
        }

        bool operator>=(const ContiguousConstIterator &other) const override {
            return _item >= other._item;
        }

        bool operator<=(const ContiguousConstIterator &other) const override {
            return _item <= other._item;
        }

        ContiguousConstIterator &operator++() override {
            ++_item;
            return *this;
        }

        ContiguousConstIterator operator++(int) override {
            ContiguousConstIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        ContiguousConstIterator &operator--() override {
            --_item;
            return *this;
        }

        ContiguousConstIterator operator--(int) override {
            ContiguousConstIterator tmp(*this);
            --(*this);
            return tmp;
        }

        ContiguousConstIterator operator+(int n) const override {
            return ContiguousConstIterator(_item + n);
        }

        ContiguousConstIterator operator-(int n) const override {
            return ContiguousConstIterator(_item - n);
        }

        int operator-(const ContiguousConstIterator &other) const override {
            return _item - other._item;
        }

        ContiguousConstIterator& operator+=(int n) override {
            _item += n;
            return *this;
        }

        ContiguousConstIterator& operator-=(int n) override {
            _item -= n;
            return *this;
        }

        const Reference operator*() const override {
            return *_item;
        }

        explicit operator Pointer() const override {
            return _item;
        }
    };

/**
     * Iterator specialization for contiguous memory area
     * @tparam T
     * @tparam Pointer
     * @tparam Reference
     */
    template<typename T, typename Pointer = T *, typename Reference = T &>
    class ContiguousIterator : public IteratorBase<ContiguousIterator<T, Pointer, Reference>, T, Pointer, Reference> {
    private:
        Pointer _item;

    public:
        ContiguousIterator() = delete;

        explicit ContiguousIterator(Pointer item) :
            _item(item) {
        }

        ContiguousIterator(const ContiguousIterator &other) : _item(other._item) {}

        // explicit ContiguousIterator(const ContiguousIterator<const T>& other) = delete;

        // ContiguousIterator &operator=(const ContiguousIterator<const T>& other) = delete;

        ContiguousIterator &operator=(const ContiguousIterator<T>& other) override {
            _item = other._item;
            return *this;
        }

        operator ContiguousConstIterator<T, const Pointer, const Reference>() const {
            return ContiguousConstIterator<T, const Pointer, const Reference>{_item};
        }

        bool operator==(const ContiguousIterator &other) const override {
            return _item == other._item;
        }

        bool operator!=(const ContiguousIterator &other) const override {
            return !(*this == other);
        }

        bool operator==(Pointer other) const override {
            return _item == other;
        }

        bool operator!=(Pointer other) const override {
            return !(_item == other);
        }

        bool operator>(const ContiguousIterator &other) const override {
            return _item > other._item;
        }

        bool operator<(const ContiguousIterator &other) const override {
            return _item < other._item;
        }

        bool operator>=(const ContiguousIterator &other) const override {
            return _item >= other._item;
        }

        bool operator<=(const ContiguousIterator &other) const override {
            return _item <= other._item;
        }

        ContiguousIterator &operator++() override {
            ++_item;
            return *this;
        }

        ContiguousIterator operator++(int) override {
            ContiguousIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        ContiguousIterator &operator--() override {
            --_item;
            return *this;
        }

        ContiguousIterator operator--(int) override {
            ContiguousIterator tmp(*this);
            --(*this);
            return tmp;
        }

        ContiguousIterator operator+(int n) const override {
            return ContiguousIterator(_item + n);
        }

        ContiguousIterator operator-(int n) const override {
            return ContiguousIterator(_item - n);
        }

        int operator-(const ContiguousIterator &other) const override {
            return _item - other._item;
        }

        ContiguousIterator& operator+=(int n) override {
            _item += n;
            return *this;
        }

        ContiguousIterator& operator-=(int n) override {
            _item -= n;
            return *this;
        }

        Reference operator*() const override {
            return *_item;
        }

        explicit operator Pointer() const override {
            return _item;
        }
    };
} // namespace container

#endif // KFS_1__CONTIGUOUSITERATOR_HPP

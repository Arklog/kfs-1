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
    template<typename Derived, typename T, typename Pointer = T *, typename Reference = T &>
    class IteratorBase {
    public:
        virtual ~IteratorBase() = default;

        virtual bool operator==(const Derived &other) const = 0;

        virtual bool operator!=(const Derived &other) const = 0;

        virtual bool operator==(Pointer other) const = 0;

        virtual bool operator!=(Pointer other) const = 0;

        virtual Derived &operator++() = 0;

        virtual Derived operator++(int) = 0;

        virtual Derived &operator--() = 0;

        virtual Derived operator--(int) = 0;

        virtual Derived operator+(int) const = 0;

        virtual Derived operator-(int) const = 0;

        virtual Reference operator*() = 0;

        virtual explicit operator Pointer() const = 0;
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

        Reference operator*() override {
            return *_item;
        }

        explicit operator Pointer() const override {
            return _item;
        }
    };
} // container

#endif //KFS_1_ITERATOR_HPP

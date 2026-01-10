//
// Created by pierre on 12/29/25.
//

#ifndef KFS_1_CONTAINER_HPP
#define KFS_1_CONTAINER_HPP

namespace container {
    template<typename T, typename IteratorType, typename ConstIteratorType>
    class Container {
    public:
        ~Container() = default;

        using iterator       = IteratorType;
        using const_iterator = ConstIteratorType;
        using size_type      = unsigned int;
        using value_type     = T;

        /**
         * Get an iterator to the beginning of the buffer
         * @return
         */
        virtual iterator begin() = 0;

        virtual const_iterator begin() const = 0;

        /**
         * Get an iterator to the end of the buffer
         * @return
         */
        virtual iterator end() = 0;

        virtual const_iterator end() const = 0;

        /**
         * Get a constant iterator to the beginning of the buffer
         * @return
         */
        virtual const_iterator cbegin() const = 0;

        /**
         * Get a constant iterator to the end of the buffer
         * @return
         */
        virtual const_iterator cend() const = 0;

        /**
         * Get a pointer to the raw container data
         * @return
         */
        virtual T *data() const = 0;

        /**
         * Get the number of allocated object of the container
         * @return
         */
        virtual size_type size() const = 0;

        virtual iterator insert(iterator position, T &value) = 0;

        /**
        * Insert one element at position
        *
        * @param position The position at which to insert
        * @param value The value to be inserted
        *
        * @return The position at which the element have been inserted or end on failure
        */
        virtual iterator insert(iterator position, T &&value) = 0;

        /**
         * Insert at most end() - position elements from the range [_begin, _end] at position position.
         *
         * @param position The position at which to insert
         * @param _begin The start of the range to insert
         * @param _end The end of the range to insert
         *
         * @return The position at which the elements have been inserted or end on failure.
         */
        virtual iterator insert(iterator position, iterator _begin, iterator _end) = 0;
    };
} // container

#endif //KFS_1_CONTAINER_HPP

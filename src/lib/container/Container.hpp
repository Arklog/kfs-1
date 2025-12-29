//
// Created by pierre on 12/29/25.
//

#ifndef KFS_1_CONTAINER_HPP
#define KFS_1_CONTAINER_HPP

#include "Iterator.hpp"

namespace container {
    template<typename T, typename IteratorType, typename ConstIteratorType>
    class Container {
    public:
        virtual ~Container() = default;

        using iterator       = IteratorType;
        using const_iterator = ConstIteratorType;

        /**
         * Get an iterator to the beginning of the buffer
         * @return
         */
        virtual iterator begin() = 0;

        /**
         * Get an iterator to the end of the buffer
         * @return
         */
        virtual iterator end() = 0;

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
    };
} // container

#endif //KFS_1_CONTAINER_HPP

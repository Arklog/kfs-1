//
// Created by pierre on 1/6/26.
//

#ifndef KFS_1_RANGE_HPP
#define KFS_1_RANGE_HPP

namespace container {
    template<typename T>
    struct range {
        T _begin;
        T _end;

        T begin() const {
            return _begin;
        }

        T end() const {
            return _end;
        }
    };
}

#endif //KFS_1_RANGE_HPP

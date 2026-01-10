//
// Created by pierre on 1/9/26.
//

/**
 * @example example.cpp
 */

//! [container_range_example]
#include "range.hpp"
#include "Array.hpp"

auto arr1 = container::Array<int, 5>{1, 2, 3, 4, 5};
auto arr2 = container::Array<int, 6>{1, 2, 3, 4, 5, 6};

for (auto &i: container::range{{arr1.begin(), arr2.begin()}, 5}) {
    // Do something with i
}
//! [container_range_example]
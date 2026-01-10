//
// Created by pierre on 1/9/26.
//

#include <catch2/catch_all.hpp>
#include "lib/container/range.hpp"

#include "StackVector.hpp"

TEST_CASE("basic range", "[container]") {
    container::StackVector<int, 10> v{1, 2, 3, 4};

    int i = 0;
    for (const auto& item: container::range(v.begin(), v.end() - 1)) {
        REQUIRE(item == v[i]);
        ++i;
    }

    REQUIRE(i == 3);
}

TEST_CASE("pair range", "[container]") {
    using namespace container;
    StackVector<int, 10> v{1, 2, 3, 4};
    StackVector<int, 10> v2{1, 2, 3, 4, 5};

    int i = 0;
    int i2 = 1;

    using iter_type = decltype(v)::iterator;

    for (const auto& [iter1, iter2]: dual_range<iter_type, iter_type>({v.begin(), v2.begin() + 1}, 4)) {
        REQUIRE(*iter1 == v[i++]);
        REQUIRE(*iter2 == v2[i2++]);
    }

    REQUIRE(i == 4);
    REQUIRE(i2 == 5);
}
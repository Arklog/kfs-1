//
// Created by pierre on 1/2/26.
//
#include "lib/math/math.hpp"

#include <catch2/catch_all.hpp>

TEST_CASE("math", "[math]") {
    SECTION("min") {
        REQUIRE(math::min(0, 1) == 0);
        REQUIRE(math::min(1, 10) == 1);
    }
}

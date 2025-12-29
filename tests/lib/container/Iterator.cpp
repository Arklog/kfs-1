//
// Created by pierre on 12/29/25.
//
#include <lib/container/Iterator.hpp>
#include <catch2/catch_all.hpp>

TEST_CASE("ContiguousIterator", "[container]") {
    SECTION("Contiguous Memory") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test};

        REQUIRE(iter == test);
        REQUIRE(iter + 1 == test + 1);
    }

    SECTION("operator==") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test};
        auto                               tmp = iter;

        REQUIRE(iter == test);
    }

    SECTION("operator!=") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test};
        container::ContiguousIterator<int> iter2{test + 1};

        REQUIRE(iter != iter2);
    }

    SECTION("operator++") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test};

        ++iter;
        REQUIRE(iter == test + 1);
    }

    SECTION("operator++(int)") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test};
        auto                               iter2 = iter++;

        REQUIRE(iter == test + 1);
        REQUIRE(iter2 != iter);
        REQUIRE(iter2 == test);
    }

    SECTION("operator--") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test + 1};

        --iter;
        REQUIRE(iter == test);
    }

    SECTION("operator--(int)") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test + 1};
        auto                               iter2 = iter--;

        REQUIRE(iter == test);
        REQUIRE(iter2 == test + 1);
        REQUIRE(iter2 != iter);
    }

    SECTION("operator+") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test};

        REQUIRE(iter + 1 == test + 1);
    }

    SECTION("operator-") {
        int                                test[3] = {1, 2, 3};
        container::ContiguousIterator<int> iter{test + 1};

        REQUIRE(iter - 1 == test);
    }
}

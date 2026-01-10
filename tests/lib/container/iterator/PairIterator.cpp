//
// Created by pierre on 1/9/26.
//

#include <catch2/catch_all.hpp>
#include "lib/container/iterator/PairIterator.hpp"
#include "pair.hpp"
#include "iterator/ContiguousIterator.hpp"

TEST_CASE("PairIterator", "[container]") {
    SECTION("CTOR") {
        {
            using iterator_type = container::ContiguousIterator<int>;
            container::PairIterator<container::pair<iterator_type, iterator_type>> t{};
        }

        {
            using iterator_type = container::ContiguousIterator<int>;
            container::PairIterator<container::pair<iterator_type, iterator_type>> t{iterator_type{nullptr}, iterator_type{nullptr}};
        }
    }
}
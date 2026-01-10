//
// Created by pierre on 1/6/26.
//
#include <catch2/catch_all.hpp>
#include "lib/utility/utility.hpp"
#include <type_traits>
#include <string>

TEST_CASE("utility", "[utility]") {
    SECTION("remove_reference") {
        REQUIRE(std::is_same<int, utility::remove_reference<int>::type>::value);
        REQUIRE(std::is_same<int, utility::remove_reference<int&>::type>::value);
        REQUIRE(std::is_same<int, utility::remove_reference<int&&>::type>::value);
    }

    SECTION("move") {
        std::string a{"a"};
        std::string b{"b"};

        a = utility::move(b);
        REQUIRE(a == "b");
        REQUIRE(b == "");
    }

    SECTION("swap") {
        std::string a{"a"};
        std::string b{"b"};

        utility::swap<std::string>(a, b);
    }
}

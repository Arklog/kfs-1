//
// Created by pierre on 12/18/25.
//

#include "catch2/catch_all.hpp"
#include "lib/format/format.hpp"

TEST_CASE("libformat", "[format]") {
    SECTION("format uint32_t") {
        char buffer[20] = {0};
        char *next = format::format(buffer, 4294967295U);
        REQUIRE(next != nullptr);
        REQUIRE(std::string(buffer) == "4294967295");
        REQUIRE(next == buffer + 10);

        std::memset(buffer, 0, 20);
        next = format::format(buffer, 0U);
        REQUIRE(next != nullptr);
        REQUIRE(std::string(buffer) == "0");
        REQUIRE(next == buffer + 1);
    }

    SECTION("format int32_t") {
        char buffer[20] = {0};
        char *next = format::format(buffer, static_cast<int32_t>(-2147483648));
        REQUIRE(next != nullptr);
        REQUIRE(std::string(buffer) == "-2147483648");
        REQUIRE(next == buffer + 11);

        std::memset(buffer, 0, 20);
        next = format::format(buffer, static_cast<int32_t>(0));
        REQUIRE(next != nullptr);
        REQUIRE(std::string(buffer) == "0");
        REQUIRE(next == buffer + 1);

        std::memset(buffer, 0, 20);
        next = format::format(buffer, static_cast<int32_t>(123456789));
        REQUIRE(next != nullptr);
        REQUIRE(std::string(buffer) == "123456789");
        REQUIRE(next == buffer + 9);
    }
}
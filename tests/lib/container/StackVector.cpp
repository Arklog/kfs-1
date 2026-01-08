//
// Created by pierre on 1/7/26.
//
#include <catch2/catch_all.hpp>
#include "lib/container/StackVector.hpp"
#include "static_check.hpp"

TEST_CASE("StackVector", "[container]") {
    SECTION("static check") {
        static_assert(is_basic_container<container::StackVector<int, 80>>, "not a valid container");
    }

    SECTION("CTOR") {
        { // basic
            container::StackVector<int, 80> v{};

            REQUIRE(v.size() == 0);
            REQUIRE(v.begin() == v.end());
        }

        { // elements
            container::StackVector<int, 10> v{1, 2, 3, 4, 5};

            REQUIRE(v.size() == 5);
            REQUIRE(v[0] == 1);
            REQUIRE(v[1] == 2);
            REQUIRE(v[2] == 3);
            REQUIRE(v[3] == 4);
            REQUIRE(v[4] == 5);
        }

        { // iterators
            container::StackVector<std::string, 10> v{"1", "2", "3", "4"};
            container::StackVector<std::string, 10> v2{v.begin() + 1, v.begin() + 3};

            REQUIRE(v2.size() == 2);
            REQUIRE(v2[0] == "2");
            REQUIRE(v2[1] == "3");

            REQUIRE(v[0] == "1");
            REQUIRE(v[1] == "2");
            REQUIRE(v[2] == "3");
            REQUIRE(v[3] == "4");
        }

        { // Copy
            container::StackVector<std::string, 4> v{"1", "2", "3"};
            auto v2{v};

            REQUIRE(v2.size() == 3);
            REQUIRE(v2[0] == "1");
            REQUIRE(v2[1] == "2");
            REQUIRE(v2[2] == "3");
            REQUIRE(v[0] == "1");
            REQUIRE(v[1] == "2");
            REQUIRE(v[2] == "3");
        }

        { // Move
            container::StackVector<std::string, 4> v{"1", "2", "3"};
            container::StackVector<std::string, 4> v2{utility::move(v)};

            REQUIRE(v2.size() == 3);
            REQUIRE(v2[0] == "1");
            REQUIRE(v2[1] == "2");
            REQUIRE(v2[2] == "3");
        }
    }

    SECTION("iterator") {
        container::StackVector<int, 80> v{1};

        REQUIRE(v.size() == 1);
        REQUIRE(*v.begin() == 1);
        REQUIRE(v.begin() == v.data());
        REQUIRE(v.cbegin() == v.data());

        REQUIRE(v.cend() == v.data() + 1);
        REQUIRE(v.cend() == v.cbegin() + 1);
        REQUIRE(v.end() == v.begin() + 1);
    }

    SECTION("insert one") {
        { // Move insert
            container::StackVector<int, 80> v{1};

            auto ret = v.insert(v.begin(), 2);
            REQUIRE(v.size() == 2);
            REQUIRE(v[0] == 2);
            REQUIRE(v[1] == 1);
            REQUIRE(ret == v.begin());

            ret = v.insert(v.end(), 3);
            REQUIRE(v.size() == 3);
            REQUIRE(v[0] == 2);
            REQUIRE(v[1] == 1);
            REQUIRE(v[2] == 3);
            REQUIRE(ret == v.end() - 1);
        }

        {
            container::StackVector<int, 1> v{1};

            auto ret = v.insert(v.begin(), 2);
            REQUIRE(v[0] == 1);
            REQUIRE(ret == v.end());
        }
    }

    SECTION("insert many") {
        { // Non overlap
            container::StackVector<int, 80> v{1};
            container::StackVector<int, 80> v2{2, 3, 4};

            auto ret = v.insert(v.begin(), v2.begin(), v2.end());
            REQUIRE(v.size() == 4);
            REQUIRE(v[0] == 2);
            REQUIRE(v[1] == 3);
            REQUIRE(v[2] == 4);
            REQUIRE(v[3] == 1);
            REQUIRE(ret == v.begin());

            ret = v.insert(v.end(), v2.begin(), v2.end());
            REQUIRE(v.size() == 7);
            REQUIRE(v[0] == 2);
            REQUIRE(v[1] == 3);
            REQUIRE(v[2] == 4);
            REQUIRE(v[3] == 1);
            REQUIRE(v[4] == 2);
            REQUIRE(v[5] == 3);
            REQUIRE(v[6] == 4);
            REQUIRE(ret == v.end() - 3);
        }

        {
            container::StackVector<int, 5> v{1};
            container::StackVector<int, 5> v2{2, 3, 4, 5, 6};

            auto ret = v.insert(v.begin(), v2.begin(), v2.end());
            REQUIRE(v.size() == 1);
            REQUIRE(v[0] == 1);
            REQUIRE(ret == v.end());
        }
    }

    SECTION("push_back") {
        container::StackVector<int, 3> v{1};

        auto ret = v.push_bash(2);
        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(ret == v.end() - 1);

        ret = v.push_bash(3);
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(ret == v.end() - 1);

        ret = v.push_bash(4);
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(ret == v.end());
    }

    SECTION("emplace back") {
        container::StackVector<int, 3> v{1};

        auto ret = v.push_bash(2);
        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(ret == v.end() - 1);

        ret = v.push_bash(3);
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(ret == v.end() - 1);

        ret = v.push_bash(4);
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(ret == v.end());
    }

    SECTION("erase") {
        { // one
            container::StackVector<int, 3> v{1, 2, 3};

            auto ret = v.erase(v.begin());
            REQUIRE(ret == v.begin());
            REQUIRE(v.size() == 2);
            REQUIRE(v[0] == 2);
            REQUIRE(v[1] == 3);

            ret = v.erase(v.end());
            REQUIRE(ret == v.end());
            REQUIRE(v.size() == 2);
            REQUIRE(v[0] == 2);
            REQUIRE(v[1] == 3);
        }

        { // many
            container::StackVector<int, 4> v{1, 2, 3, 4};

            auto ret = v.erase(v.begin() + 1, v.end() - 1);
            REQUIRE(v.size() == 2);
            REQUIRE(v[0] == 1);
            REQUIRE(v[1] == 4);

            ret = v.erase(v.begin(), v.end());
            REQUIRE(v.size() == 0);
        }
    }
}
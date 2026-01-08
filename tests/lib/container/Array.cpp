//
// Created by pierre on 12/17/25.
//
#include <catch2/catch_all.hpp>
#include <lib/container/Array.hpp>
#include <string>
#include "static_check.hpp"

template<typename IterType, typename ValueType>
concept non_const_iterator = requires(IterType it, ValueType val)
{
    *it = val;
};

template<typename IterType, typename ValueType>
concept const_iterator = !non_const_iterator<IterType, ValueType>;

TEST_CASE("KArray", "[KArray]") {
    SECTION("validate container") {
        static_assert(is_basic_container<container::Array<int, 3>>, "non valid container");
    }

    SECTION("CTOR") {
        container::Array<int, 10> arr{};
        REQUIRE(true);
    }

    SECTION("CTOR with data") {
        container::Array<int, 3> arr(1, 2, 3);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
    }

    SECTION("CTOR with data2") {
        container::Array<int, 3> arr(1, 2, 3);

        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
    }

    SECTION("Operator+") {
        container::Array<int, 2> arr1(1, 2);
        container::Array<int, 3> arr2(3, 4, 5);
        auto                     arr3 = arr1 + arr2;

        REQUIRE(arr3.size() == 5);
        REQUIRE(arr3[0] == 1);
        REQUIRE(arr3[1] == 2);
        REQUIRE(arr3[2] == 3);
        REQUIRE(arr3[3] == 4);
        REQUIRE(arr3[4] == 5);
    }

    SECTION("Operator[]") {
        container::Array<int, 3> kArr(10, 20, 30);

        kArr[1] = 0;

        REQUIRE(kArr[0] == 10);
        REQUIRE(kArr[1] == 0);
        REQUIRE(kArr[2] == 30);
    }

    SECTION("range loop") {
        container::Array<int, 3> karr(1, 2, 3);

        for (auto i: karr) {
            continue;
        }
    }

    SECTION("iterator") {
        using arrayclass = container::Array<int, 3>;
        static_assert(non_const_iterator<arrayclass::iterator, int>, "iterator should not be const");
        static_assert(const_iterator<arrayclass::const_iterator, int>, "const iterator should be const");
    }

    SECTION("begin") {
        container::Array<int, 3> karr(1, 2, 3);
        const container::Array<int, 3>arr(1, 2, 3);

        auto iter  = karr.begin();
        auto citer = karr.cbegin();
        REQUIRE(*iter == 1);
        REQUIRE(*citer == 1);
        REQUIRE(*arr.begin() == 1);
    }

    SECTION("end") {
        container::Array<int, 3> karr(1, 2, 3);

        REQUIRE(karr.begin() + 3 == karr.end());
        REQUIRE(karr.cbegin() + 3 == karr.cend());
    }

    SECTION("insert one") {
        auto arr = container::Array<std::string, 3>("aa", "bb", "cc");

        arr.insert(arr.begin(), "dd");
        REQUIRE(arr[0] == "dd");
        REQUIRE(arr[1] == "aa");
        REQUIRE(arr[2] == "bb");

        arr.insert(arr.begin() + 1, "ee");
        REQUIRE(arr[0] == "dd");
        REQUIRE(arr[1] == "ee");
        REQUIRE(arr[2] == "aa");

        arr.insert(arr.end() - 1, "ff");
        REQUIRE(arr[0] == "dd");
        REQUIRE(arr[1] == "ee");
        REQUIRE(arr[2] == "ff");
    }

    SECTION("insert many") {
        auto arr  = container::Array<std::string, 3>("aa", "bb", "cc");
        auto arr2 = container::Array<std::string, 3>("dd", "ee", "ff");

        arr.insert(arr.begin(), arr2.begin(), arr2.end());
        REQUIRE(arr[0] == "dd");
        REQUIRE(arr[1] == "ee");
        REQUIRE(arr[2] == "ff");

        arr2 = container::Array<std::string, 3>("dd", "ee", "ff");
        arr.insert(arr.begin() + 1, arr2.begin(), arr2.begin() + 1);
        REQUIRE(arr[0] == "dd");
        REQUIRE(arr[1] == "dd");
        REQUIRE(arr[2] == "ee");

        arr[0] = "aa";
        arr2   = container::Array<std::string, 3>("dd", "ee", "ff");
        arr.insert(arr.begin(), arr2.begin(), arr2.begin() + 2);
        REQUIRE(arr[0] == "dd");
        REQUIRE(arr[1] == "ee");
        REQUIRE(arr[2] == "aa");

        // overlapping memory
        arr = container::Array<std::string, 3>("a", "b", "c");
        arr.insert(arr.begin(), arr.begin() + 1, arr.end());
        REQUIRE(arr[0] == "b");
        REQUIRE(arr[1] == "c");
        REQUIRE(arr[2] == "a");

        arr = container::Array<std::string, 3>("a", "b", "c");
        arr.insert(arr.begin(), arr.begin() + 1, arr.begin() + 2);
        REQUIRE(arr[0] == "b");
        REQUIRE(arr[1] == "a");
        REQUIRE(arr[2] == "c");
    }

    SECTION("emplace") {
        container::Array<int, 3> arr;
        arr.emplace(arr.begin(), 1);
        REQUIRE(arr[0] == 1);

        arr.emplace(arr.begin(), 2);
        REQUIRE(arr[0] == 2);

        arr.emplace(arr.begin() + 1, 99);
        REQUIRE(arr[1] == 99);
    }
}

//
// Created by pierre on 12/17/25.
//
#include <catch2/catch_all.hpp>
#include <utils/KArray.hpp>

TEST_CASE("KArray", "[KArray]") {
    SECTION("CTOR") {
        KArray<int, 10> arr{};
        REQUIRE(true);
    }

    SECTION("CTOR with data") {
        int data[3] = {1, 2, 3};
        KArray<int, 3> arr(data);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
    }

    SECTION("Operator+") {
        int data1[2] = {1, 2};
        int data2[3] = {3, 4, 5};

        KArray<int, 2> arr1(data1);
        KArray<int, 3> arr2(data2);
        auto arr3 = arr1 + arr2;

        REQUIRE(arr3[0] == 1);
        REQUIRE(arr3[1] == 2);
        REQUIRE(arr3[2] == 3);
        REQUIRE(arr3[3] == 4);
        REQUIRE(arr3[4] == 5);
    }

    SECTION("Operator[]") {
        int arr[3] = {10, 20, 30};
        KArray<int, 3> kArr(arr);

        kArr[1] = 0;

        REQUIRE(kArr[0] == 10);
        REQUIRE(kArr[1] == 0);
        REQUIRE(kArr[2] == 30);
    }
}
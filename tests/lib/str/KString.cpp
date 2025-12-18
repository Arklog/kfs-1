//
// Created by alice on 18/12/2025.
//

#include <catch2/catch_all.hpp>
#include "lib/str/KString.hpp"

TEST_CASE("KString", "[kstring]") {
    SECTION("strlen") {
        const char *str = "strken";
        const char *str2 = "1";
        const char *str3 = "";

        REQUIRE(kstring::strlen(str) == 6);
        REQUIRE(kstring::strlen(str2) == 1);
        REQUIRE(kstring::strlen(str3) == 0);
    }

    SECTION("strcmp") {
        const char *str1 = "str1";
        const char *str2 = "str2";
        const char *str3 = "";
        const char *str4 = "str1";

        REQUIRE(kstring::strcmp(str1, str2) == -1);
        REQUIRE(kstring::strcmp(str1, str1) == 0);
        REQUIRE(kstring::strcmp(str1, str3) == 115);
    }

    //SECTION("strncmp") {
     //   const char *str1 = "str1";
    //    const char *str2 = "str2";
    //    const char *str3 = "";
    //    const char *str4 = nullptr;

        //REQUIRE(kstring::strncmp(str1, str2, 3) == -1);
        //REQUIRE(kstring::strncmp(str1, str2, 2) == 0);
        //REQUIRE(kstring::strncmp(str1, str2, 19) == -1);
        //REQUIRE(kstring::strncmp(str1, str1, 10) == 0);
        //REQUIRE(kstring::strncmp(str1, str3, 1) == 115);
        //REQUIRE(kstring::strncmp(str1, str3, 0) == 115);
    //    REQUIRE(kstring::strncmp(str3, str4, 10) == 0);
//    }

    SECTION("strchr") {
        const char *str1 = "Hello kernel";
        const char *str2 = "";

        REQUIRE(kstring::strchr(str1, 'e') == str1 + 1);
        REQUIRE(kstring::strchr(str1, str2[0]) == nullptr);
        REQUIRE(kstring::strchr(str1, 0) == nullptr);
        REQUIRE(kstring::strchr(str1, str1[9]) == str1 + 9);
    }

    SECTION("strrchr") {
        const char *str1 = "Hello kernel";
        const char *str2 = "";

        REQUIRE(kstring::strcmp(kstring::strrchr(str1, 'e'), "el") == 0);
        REQUIRE(kstring::strrchr(str1, str2[0]) == nullptr);
        REQUIRE(kstring::strrchr(str1, 0) == nullptr);
        REQUIRE(kstring::strrchr(str1, str1[9]) == str1 + 9);
        REQUIRE(kstring::strrchr(str1, str1[2]) == str1 + 11);
    }

    SECTION("strstr") {
        const char *str1 = "Hello ker-kernel";
        const char *str2 = "kern";
        const char *str3 = "kern";
        const char *str4 = "kernek";
        const char *str5 = "";
        const char *str6 = nullptr;
        REQUIRE(kstring::strstr(str1, str2) == str1 + 10);
        REQUIRE(kstring::strstr(str1, str3) == str1 + 10);
        REQUIRE(kstring::strstr(str1, str4) == nullptr);
        REQUIRE(kstring::strstr(str1, str5) == nullptr);
        REQUIRE(kstring::strstr(str1, str6) == nullptr);
    }

    SECTION("safe_atoi") {
        const char *str1 = "332";
        const char *str2 = "-3112";
        const char *str3 = "22222222222222222222222222222222222222222222222";
        const char *str4 = "-2147483648";
        const char *str5 = "2147483647";
        const char *str6 = "";
        const char *str7 = nullptr;
        const char *str8 = "++++-+++2147483647";
        const char *str9 = "2d147483647";
        int res;
        kstring::safe_atoi(str1, &res);
        REQUIRE(res == 332);
        kstring::safe_atoi(str2, &res);
        REQUIRE(res == -3112);
        REQUIRE(kstring::safe_atoi(str3, &res) == 1);
        kstring::safe_atoi(str4, &res);
        REQUIRE(res == -2147483648);
        kstring::safe_atoi(str5, &res);
        REQUIRE(res == 2147483647);
        REQUIRE((kstring::safe_atoi(str6, &res) == 1));
        REQUIRE((kstring::safe_atoi(str7, &res) == 1));
        REQUIRE((kstring::safe_atoi(str8, &res) == 0 && res == 2147483647));
        REQUIRE((kstring::safe_atoi(str9, &res) == 0 && res == 2));
    }
}
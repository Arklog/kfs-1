//
// Created by alice on 18/12/2025.
//

#include <catch2/catch_all.hpp>
#include "lib/str/KString.h"

TEST_CASE("KString", "[kstring]") {
    SECTION("strlen") {
        char *str = "strken";
        char *str2 = "1";
        char *str3 = "";
        char *str4;
        REQUIRE(kstring::strlen(str) == 6);
        REQUIRE(kstring::strlen(str2) == 1);
        REQUIRE(kstring::strlen(str3) == 0);
        REQUIRE(kstring::strlen(str4) == 0);
    }

    SECTION("strcmp") {
        char *str1 = "str1";
        char *str2 = "str2";
        char *str3 = "";
        char *str4;

        REQUIRE(kstring::strcmp(str1, str2) == -1);
        REQUIRE(kstring::strcmp(str1, str1) == 0);
        REQUIRE(kstring::strcmp(str1, str3) == 115);
        REQUIRE(kstring::strcmp(str3, str4) == 0);
    }

    SECTION("strncmp") {
        char *str1 = "str1";
        char *str2 = "str2";
        char *str3 = "";
        char *str4;

        REQUIRE(kstring::strncmp(str1, str2, 4) == -1);
        REQUIRE(kstring::strncmp(str1, str2, 3) == 0);
        REQUIRE(kstring::strncmp(str1, str2, 19) == -1);
        REQUIRE(kstring::strncmp(str1, str1, 10) == 0);
        REQUIRE(kstring::strncmp(str1, str3, 1) == 115);
        REQUIRE(kstring::strncmp(str1, str3, 0) == 115);
        REQUIRE(kstring::strncmp(str3, str4, 10) == 0);
    }

    SECTION("strchr") {
        char *str1 = "Hello kernel";
        char *str2 = "";

        REQUIRE(kstring::strchr(str1, 'e') == str1 + 2);
        REQUIRE(kstring::strchr(str1, str2[0]) == nullptr);
        REQUIRE(kstring::strchr(str1, 0) == nullptr);
        REQUIRE(kstring::strchr(str1, str1[9]) == str1 + 9);
    }

    SECTION("strrchr") {
        char *str1 = "Hello kernel";
        char *str2 = "";

        REQUIRE(kstring::strrchr(str1, 'e') == str1 + 10);
        REQUIRE(kstring::strrchr(str1, str2[0]) == nullptr);
        REQUIRE(kstring::strrchr(str1, 0) == nullptr);
        REQUIRE(kstring::strrchr(str1, str1[9]) == str1 + 9);
        REQUIRE(kstring::strrchr(str1, str1[2]) == str1 + 11);
    }

    SECTION("strstr") {
        char *str1 = "Hello ker-kernel";
        char *str2 = "kern";
        char *str3 = "ke";
        char *str4 = "kernek";
        char *str5 = "";
        char *str6;
        REQUIRE(kstring::strstr(str1, str2) == str1 + 10);
        REQUIRE(kstring::strstr(str1, str3) == str1 + 10);
        REQUIRE(kstring::strstr(str1, str4) == nullptr);
        REQUIRE(kstring::strstr(str1, str5) == nullptr);
        REQUIRE(kstring::strstr(str1, str6) == nullptr);
    }

    SECTION("safe_atoi") {
        char *str1 = "332";
        char *str2 = "-3112";
        char *str3 = "22222222222222222222222222222222222222222222222";
        char *str4 = "-2147483648";
        char *str5 = "2147483647";
        char *str6 = "";
        char *str7;
        char *str8 = "++++-+++2147483647";
        char *str9 = "2d147483647";
        int res;

        REQUIRE((kstring::safe_atoi(str1, &res) == 0 && res == 332));
        REQUIRE((kstring::safe_atoi(str2, &res) == 0 && res == -3112));
        REQUIRE((kstring::safe_atoi(str3, &res) == 1));
        REQUIRE((kstring::safe_atoi(str4, &res) == 0 && res == -2147483648));
        REQUIRE((kstring::safe_atoi(str5, &res) == 0 && res == 2147483647));
        REQUIRE((kstring::safe_atoi(str6, &res) == 1));
        REQUIRE((kstring::safe_atoi(str7, &res) == 1));
        REQUIRE((kstring::safe_atoi(str8, &res) == 0 && res == 2147483647));
        REQUIRE((kstring::safe_atoi(str9, &res) == 0 && res == 2));
    }
}
//
// Created by alice on 18/12/2025.
//

#include <catch2/catch_all.hpp>
#include "lib/str/KString.hpp"

TEST_CASE("KString", "[kstring]") {
    SECTION("strlen") {
        const char *str  = "strken";
        const char *str2 = "1";
        const char *str3 = "";
        const char *str4 = "a\0b";

        REQUIRE(kstring::strlen(str) == 6);
        REQUIRE(kstring::strlen(str2) == 1);
        REQUIRE(kstring::strlen(str3) == 0);
        REQUIRE(kstring::strlen(str4) == 1);
    }

    SECTION("strcmp") {
        const char *str1 = "str1";
        const char *str2 = "str2";
        const char *str4 = "str1\0a";
        const char *str3 = "";

        REQUIRE(kstring::strcmp(str1, str2) == -1);
        REQUIRE(kstring::strcmp(str1, str1) == 0);
        REQUIRE(kstring::strcmp(str1, str3) == 115);
        REQUIRE(kstring::strcmp(str1, str4) == 0);
    }

    SECTION("strncmp") {
        const char *str1 = "str1";
        const char *str2 = "str2";
        const char *str4 = "at";
        const char *str3 = "";

        REQUIRE(kstring::strncmp(str1, str2, 0) == 0);
        REQUIRE(kstring::strncmp(str1, str2, 3) == 0);
        REQUIRE(kstring::strncmp(str1, str2, 4) == -1);
        REQUIRE(kstring::strncmp(str3, str1, 1) == -115);
        REQUIRE(kstring::strncmp(str1, str3, 1) == 115);
        REQUIRE(kstring::strncmp(str1, str4, 1) == 's' - 'a');
        REQUIRE(kstring::strncmp(str1, str2, 10) == '1' - '2');
    }

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

    SECTION("strcpy") {
        char        buffer[128];
        const char *str1 = "Hello kernel";

        kstring::strcpy(buffer, "");
        REQUIRE(std::strcmp(buffer, "") == 0);

        kstring::strcpy(buffer, str1);
        REQUIRE(std::strcmp(buffer, str1) == 0);

        kstring::strcpy(buffer, "a\0b");
        REQUIRE(std::strcmp(buffer, "a") == 0);
        REQUIRE(std::strlen(buffer) == 1);
    }

    SECTION("memcpy") {
        char dest[128];
        char src[128];

        dest[0] = 1;
        kstring::memcpy(dest, src, 0);
        REQUIRE(dest[0] == 1);

        std::memset(src, 1, 128);
        kstring::memcpy(dest, src, 128);
        REQUIRE(std::memcmp(dest, src, 128) == 0);
    }

    SECTION("memmove") {
        char buff[128];

        std::memcpy(buff, "12345", 5);
        memmove(buff, buff + 1, 4);
        REQUIRE(std::memcmp(buff, "23455", 5) == 0);

        std::memcpy(buff, "12345", 5);
        memmove(buff + 1, buff, 4);
        REQUIRE(std::memcmp(buff, "11234", 5) == 0);
    }

    SECTION("memcmp") {
        char b1[128];
        char b2[128];

        // SUCCESS
        std::memset(b1, 0, 128);
        std::memset(b2, 0, 128);
        REQUIRE(kstring::memcmp(b1, b2, 0) == 0);
        REQUIRE(kstring::memcmp(b1, b2, 128) == 0);

        // FAILURE
        b1[0] = 1;
        REQUIRE(kstring::memcmp(b1, b2, 128) == 1);
        b1[0]   = 0;
        b1[127] = 1;
        REQUIRE(kstring::memcmp(b1, b2, 128) == 1);
        b1[127] = 0;
        b2[0]   = 1;
        REQUIRE(kstring::memcmp(b1, b2, 128) == -1);
        b2[0]   = 0;
        b2[127] = 1;
        REQUIRE(kstring::memcmp(b1, b2, 128) == -1);

        // CHECK non power of 4 length
        std::memset(b1, 0, 128);
        std::memset(b2, 0, 128);
        REQUIRE(kstring::memcmp(b1 + 1, b2 + 1, 127) == 0);
        REQUIRE(kstring::memcmp(b1 + 1, b2 + 1, 3) == 0);
    }

    SECTION("safe_atoi") {
        const char *str1 = "920";
        const char *str2 = "-3112";
        const char *str3 = "22222222222222222222222222222222222222222222222";
        const char *str4 = "-2147483648";
        const char *str5 = "2147483647";
        const char *str6 = "";
        const char *str7 = nullptr;
        const char *str8 = "++++-+++2147483647";
        const char *str9 = "2d147483647";

        int value;
        int ret;

        ret = kstring::safe_atoi(str1, &value);
        REQUIRE(ret == 0);
        REQUIRE(value == 920);

        ret = kstring::safe_atoi(str2, &value);
        REQUIRE(ret == 0);
        REQUIRE(value == -3112);

        ret = kstring::safe_atoi(str3, &value);
        REQUIRE(ret == 1);

        ret = kstring::safe_atoi(str4, &value);
        REQUIRE(ret == 0);
        REQUIRE(value == -2147483648);

        ret = kstring::safe_atoi(str5, &value);
        REQUIRE(ret == 0);
        REQUIRE(value == 2147483647);

        ret = kstring::safe_atoi(str8, &value);
        REQUIRE(ret == 0);
        REQUIRE(value == 2147483647);

        ret = kstring::safe_atoi(str9, &value);
        REQUIRE(ret == 0);
        REQUIRE(value == 2);

        REQUIRE((kstring::safe_atoi(str6, &value) == 1));
        REQUIRE((kstring::safe_atoi(str7, &value) == 1));
    }
}

//
// Created by alice on 18/12/2025.
//

#include "KString.hpp"
namespace kstring {
    unsigned int strlen(const char *str) {
        unsigned int len = 0;
        while (str[len]) ++len;
        return len;
    }
    int strcmp(const char *str1, const char *str2) {
        unsigned int i = 0;
        while (str1[i] && str2[i]) {
            if (str1[i] != str2[i]) return str1[i] - str2[i];
            ++i;
        }
        return str1[i] - str2[i];
    }
    int strncmp(const char *str1, const char *str2, const unsigned int n) {
        unsigned int i = 0;
        while (str1[i] && str2[i] && i < n) {
            if (str1[i] != str2[i]) return str1[i] - str2[i];
            ++i;
        }
        return str1[i] - str2[i];
    }
    const char *strchr(const char *str, const char chr) {
        unsigned int i = 0;
        while (str[i]) {
            if (str[i] == chr) return &str[i];
            ++i;
        }
        return nullptr;
    }
    const char *strrchr(const char *str, const char chr) {
        unsigned int i = strlen(str) - 1;
        while (str[i]) {
            if (str[i] == chr) return &str[i];
            --i;
        }
        return nullptr;
    }
    const char *strstr(const char *str, const char *target) {
        for (unsigned int i = 0; str[i]; i++) {
            if (str[i] == target[0]) {
                unsigned int j = 1;
                while (target[j] && str[i + j] && target[j] == str[i + j]) ++j;
                if (j == strlen(target)) return &str[i];
            }
        }
        return nullptr;
    }
    void strcpy(char *dest, const char *str) {
        unsigned int i = 0;
        while (str[i]) {
            dest[i] = str[i];
            ++i;
        }
        dest[i] = '\0';
    }

    void memcpy (void *dest, const void *src, const unsigned len) {
        char    *dst = (char *)dest;
        const char *s = (char *)src;
        unsigned int i = 0;
        while (s[i] && i < len) {
            dst[i] = s[i];
            ++i;
        }
    }

    int safe_atoi(const char *str, int *res) {
        if (!str) return 1;
        unsigned int i = 0;
        int sign = 1;
        *res = 0;

        while (str[i] && (str[i] == '-' || str[i] == '+')) {
            ++i;
            if (str[i] == '-') sign = -1;
            if (str[i] == '+') sign = 1;
        }
        while (str[i]) {
            if (str[i] <= '0' || str[i] >= '9') break;
            if (*res * 10 + str[i] - 48 < *res) return -1;
            *res = *res * 10 + str[i] - 48;
        }
        *res *= sign;
        return 0;
    }
} // kstring
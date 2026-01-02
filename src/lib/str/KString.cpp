//
// Created by alice on 18/12/2025.
//

#include "KString.hpp"
#include "include/stdint.hpp"

namespace kstring {
    unsigned int strlen(const char *str) {
        unsigned int len = 0;
        while (str[len])
            ++len;
        return len;
    }

    int strcmp(const char *str1, const char *str2) {
        unsigned int i = 0;
        while (str1[i] && str2[i]) {
            if (str1[i] != str2[i])
                return str1[i] - str2[i];
            ++i;
        }
        return str1[i] - str2[i];
    }

    int strncmp(const char *str1, const char *str2, const unsigned int n) {
        unsigned int i = 0;
        if (n == 0)
            return 0;

        while (str1[i] && str2[i] && i < n - 1) {
            if (str1[i] != str2[i])
                return str1[i] - str2[i];
            ++i;
        }
        return str1[i] - str2[i];
    }

    const char *strchr(const char *str, const char chr) {
        unsigned int i = 0;
        while (str[i]) {
            if (str[i] == chr)
                return &str[i];
            ++i;
        }
        return nullptr;
    }

    const char *strrchr(const char *str, const char chr) {
        unsigned int i = strlen(str) - 1;
        while (i > 0) {
            if (str[i] == chr)
                return &str[i];
            --i;
        }
        return nullptr;
    }

    const char *strstr(const char *str, const char *target) {
        if (!target)
            return nullptr;
        for (unsigned int i = 0; str[i]; i++) {
            if (str[i] == target[0]) {
                unsigned int j = 1;
                while (target[j] && str[i + j] && target[j] == str[i + j])
                    ++j;
                if (j == strlen(target))
                    return &str[i];
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

    void memcpy(void *dest, const void *src, unsigned len) {
        auto dst = static_cast<uint8_t *>(dest);
        auto s   = static_cast<const uint8_t *>(src);

        // align dest to 4 byte boundary
        while (len && (reinterpret_cast<int32_t>(dst) & 0x00000003)) {
            *(dst++) = *(s++);
            --len;
        }

        // copy 4 bytes at a time
        auto dst_32 = reinterpret_cast<uint32_t *>(dst);
        auto s_32   = reinterpret_cast<const uint32_t *>(s);
        while (len >= 4) {
            *(dst_32++) = *(s_32++);
            len         -= 4;
        }

        // copy remaining bytes
        dst = reinterpret_cast<uint8_t *>(dst_32);
        s   = reinterpret_cast<const uint8_t *>(s_32);
        while (len) {
            *(dst++) = *(s++);
            --len;
        }
    }

    void memmove(void *dest, const void *src, unsigned int len) {
        auto dest8 = static_cast<uint8_t *>(dest);
        auto src8  = static_cast<const uint8_t *>(src);
        auto count = len;

        if (dest < src) {
            // Normal copy
            while (count < len && reinterpret_cast<uint32_t>(dest8 + count) & 0x00000003) {
                dest8[count] = src8[count];
                ++count;
            }
        } else {
            // Reverse copy
            while (count < len && reinterpret_cast<uint32_t>(dest8 + len - count - 1) & 0x00000003) {
                dest8[len - count - 1] = src8[len - count - 1];
                ++count;
            }
        }

        uint32_t *      dest32;
        const uint32_t *src32;
        if (dest < src) {
            dest32 = reinterpret_cast<uint32_t *>(dest8 + count);
            src32  = reinterpret_cast<const uint32_t *>(src8 + count);

            while (len - count >= 4) {
                *(dest32++) = *(src32++);
                count       += 4;
            }
        } else {
            dest32 = reinterpret_cast<uint32_t *>(dest8 + len - count - 1);
            src32  = reinterpret_cast<const uint32_t *>(src8 + len - count - 1);

            while (len - count >= 4) {
                *(dest32--) = *(src32--);
                count       += 4;
            }
        }

        if (dest < src) {
            while (count < len) {
                dest8[count] = src8[count];
                ++count;
            }
        } else {
            while (count < len) {
                dest8[len - count - 1] = src8[len - count - 1];
                ++count;
            }
        }
    }

    int memcmp(const void *b1, const void *b2, unsigned len) {
        auto b1_8 = static_cast<const uint8_t *>(b1);
        auto b2_8 = static_cast<const uint8_t *>(b2);

        // check byte per byte until 4 byte aligned
        while (len && (reinterpret_cast<uint32_t>(b1_8) & 0x00000003)) {
            if (*b1_8 != *b2_8)
                return *b1_8 - *b2_8;
            ++b1_8;
            ++b2_8;
            --len;
        }

        // check 4 byte a time
        auto b1_32 = reinterpret_cast<const uint32_t *>(b1_8);
        auto b2_32 = reinterpret_cast<const uint32_t *>(b2_8);

        while (len >= 4) {
            if (*b1_32 != *b2_32)
                break;
            ++b1_32;
            ++b2_32;
            len -= 4;
        }

        // check 1 byte a time
        b1_8 = reinterpret_cast<const uint8_t *>(b1_32);
        b2_8 = reinterpret_cast<const uint8_t *>(b2_32);

        while (len && *b1_8 == *b2_8) {
            --len;
            ++b1_8;
            ++b2_8;
        }

        return *b1_8 - *b2_8;
    }


    int safe_atoi(const char *str, int *res) {
        if (!str)
            return 1;
        if (strcmp(str, "-2147483648") == 0) {
            *res = -2147483648;
            return 0;
        }
        unsigned int i    = 0;
        int          sign = 1;
        *res              = 0;

        while (str[i] && (str[i] == '-' || str[i] == '+')) {
            if (str[i] == '-')
                sign = -1;
            if (str[i] == '+')
                sign = 1;
            ++i;
        }
        if (!str[i])
            return 1;
        while (str[i]) {
            if (str[i] <= '0' || str[i] >= '9')
                break;
            if (*res * 10 + str[i] - 49 < *res)
                return 1;
            *res = *res * 10 + str[i] - 48;
            ++i;
        }
        *res *= sign;
        return 0;
    }
} // kstring

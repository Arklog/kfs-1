//
// Created by pierre on 12/18/25.
//

#ifndef KFS_1_FORMAT_HPP
#define KFS_1_FORMAT_HPP

#include "include/stdint.hpp"
#include "lib/str/KString.hpp"

namespace format {
    /**
     * Format a 32 bits signed integer into a buffer
     *
     * @param buffer The buffer to write into
     * @param value The integer to format
     *
     * @return NULL on error, otherwise a pointer to the next character after the formatted integer
     */
    char * format(char *buffer, int32_t value);

    /**
     * Format a 32 bits unsigned integer into a buffer
     *
     * @param buffer The buffer to write into
     * @param value The integer to format
     *
     * @return NULL on error, otherwise a pointer to the next character after the formatted integer
     */
    char * format(char *buffer, uint32_t value);

    /**
     * Format a C-string into a buffer
     *
     * @param buffer The buffer to write into
     * @param value The C-string to format
     *
     * @return NULL on error, otherwise a pointer to the next character after the formatted string
     */
    char * format(char *buffer, const char *value);

    inline char * fmt(char *buffer, const char *format_str) {
        // No more format specifier, copy the rest of the string and return
        kstring::memcpy(buffer, format_str, kstring::strlen(format_str) + 1);
        return buffer + kstring::strlen(buffer);
    }

    /**
     * Format the arguments into the buffer according to the format string.
     * The format string uses "{}" as format specifiers for each argument.
     *
     * @tparam T
     * @tparam Args
     * @param buffer
     * @param format_str
     * @param value
     * @param args
     * @return
     */
    template<typename T, typename ... Args>
    char * fmt(char *buffer, const char *format_str, T value, Args ... args) {
        auto next = kstring::strstr(format_str, "{}");

        // No more format specifier, copy the rest of the string and return
        if (next == nullptr) {
            kstring::memcpy(buffer, format_str, kstring::strlen(format_str) + 1);
            return buffer + kstring::strlen(buffer);
        }

        // Copy up to the next format specifier
        kstring::memcpy(buffer, format_str, next - format_str);
        buffer += next - format_str;
        buffer = format(buffer, value);

        // Increment next to skip the "{}"
        next += 2;
        return fmt(buffer, next, args...);
    }

}

#endif //KFS_1_FORMAT_HPP
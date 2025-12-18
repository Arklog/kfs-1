//
// Created by pierre on 12/18/25.
//

#ifndef KFS_1_FORMAT_HPP
#define KFS_1_FORMAT_HPP

#include "include/stdint.hpp"

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

    template<typename ... Args>
    char * format(char *buffer, const char *fmt, Args ... args);
}

#endif //KFS_1_FORMAT_HPP
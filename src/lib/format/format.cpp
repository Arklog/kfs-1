//
// Created by pierre on 12/18/25.
//

#include "format.hpp"

char * format::format(char *buffer, int32_t value) {
    if (value < 0) {
        value = -value;
        *(buffer++) = '-';
    }

    return format(buffer, static_cast<uint32_t>(value));
}

char * format::format(char *buffer, uint32_t value) {
    char buffer_tmp[10] = {};
    char *start = buffer_tmp + 9;

    do {
        *(--start) = '0' + (value % 10);
        value /= 10;
    } while (value != 0);

    while (start < buffer_tmp + 9) {
        *(buffer++) = *(start++);
    }

    return buffer;
}

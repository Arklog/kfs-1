//
// Created by alice on 18/12/2025.
//

#ifndef KFS_1_K_STR_H
#define KFS_1_K_STR_H

namespace k_str {
    unsigned int    strlen(const char *str);
    unsigned int    strcmp(const char *str1, const char *str2);
    unsigned int    strncmp(const char *str1, const char *str2, const unsigned len);
    const char      *strchr(const char *str, const char chr);
    const char      *strrchr(const char *str, const char chr);
    const char      *strstr(const char *str, const char *target);
    void            strcpy(char *dest, const char *src);
    void            memcpy(void *dest, const void *src, unsigned len);
    int             safe_atoi(const char *str, int *res);

}

#endif
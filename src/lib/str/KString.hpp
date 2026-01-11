//
// Created by alice on 18/12/2025.
//

#ifndef KFS_1_K_STR_H
#define KFS_1_K_STR_H

namespace kstring {
    /**
     * Return the length of the c-string pointed to by str, excluding the terminating null byte ('\0').
     *
     * @param str
     * @return The length of the string
     *
     * @warning str must be null-terminated.
     * @warning str must be a valid pointer
     *
     * @snippet KString.cpp strlen
     */
    unsigned int    strlen(const char *str);

    /**
     * Compare the two given string and return the difference between their first different chars. O otherwise.
     *
     * @param str1
     * @param str2
     *
     * @return the difference between the string
     *
     * @warning both str1 and str2 must be null-terminated.
     * @warning both str1 and str2 must be valid pointers
     *
     * @snippet KString.cpp strcmp
     */
    int    strcmp(const char *str1, const char *str2);

    /**
     * compare the two given string until the n-th char, and return the difference between their first different chars. O otherwise.
     *
     * @param str1
     * @param str2
     * @param n The maximum number of character to compare
     *
     * @return The difference between the first non identical byte of str1 and str2. 0 if len is reached.
     *
     * @warning both str1 and str2 must be null-terminated if their length is less than n.
     * @warning both str1 and str2 must be valid pointers
     *
     * @snippet KString.cpp strncmp
     */
    int    strncmp(const char *str1, const char *str2, const unsigned n);

    /**
     * search for the char chr within the given string, from its beginning. return a pointer on the char position or NULL if not found.
     *
     * @param str
     * @param chr char to search for
     *
     * @return The address of the first occurrence of chr in str, or NULL if not found.
     *
     * @warning str must be null-terminated
     * @warning str must be a valid pointer
     *
     * @snippet KString.cpp strchr
     */
    const char      *strchr(const char *str, const char chr);
    /**
     * search for the char chr within the given string, from its end. return a pointer on the char position or NULL if not found.
     *
     * @param str
     * @param chr char to search for
     *
     * @return pointer on chr position or NULL
     *
     * @warning str must be null-terminated
     * @warning str must be a valid pointer
     *
     * @snippet KString.cpp strrchr
     */
    const char      *strrchr(const char *str, const char chr);
    /**
     * search for the substring target within the given string. return a pointer on the substring beginning or NULL if not found.
     *
     * @param str
     * @param target sub string to search for
     *
     * @return Pointer on the first occurence of target in str. NULL if not found.
     *
     * @warning str and target must be null-terminated
     * @warning str and target must be valid pointers
     *
     * @snippet KString.cpp strstr
     */
    const char      *strstr(const char *str, const char *target);

    /**
     * Copy src into dest until a null byte is reached.
     *
     * @param dest string where perform copy
     * @param src string to copy
     *
     * @warning dest and str must be valid pointers
     * @warning str must be null-terminated
     * @warning dest must be able to accommodate src
     *
     * @snippet KString strcpy
     */
    void            strcpy(char *dest, const char *src);

    /**
     * Copy a src memory segment into another until the len index, casting them in char*.
     * @param dest segment where perform the copy
     * @param src segment to copy
     * @param len max index
     */
    void            memcpy(void *dest, const void *src, unsigned len);

    /**
     * Copy n bytes of src into dest, dest and src can overlap
     *
     * @param dest
     * @param src
     * @param len
     */
    void memmove(void *dest, const void *src, unsigned int len);

    /**
     * Compare the first len bytes of b1 and b2. Return the difference of the first non-identical byte or 0 if the
     * buffer are identicals.
     *
     * @param b1
     * @param b2
     * @param len
     *
     * @return 0 if the buffer are identical or the difference of the first non-identical byte.
     */
    int             memcmp(const void *b1, const void *b2, unsigned len);

    /**
     * create an int from a char string. This implementation avoids int overflow and will return 0 if the result is ok, 1 otherwise.
     * @param str string to cast into int
     * @param res address of the int where the result could be find if the return was 0.
     * @return
     */
    int             safe_atoi(const char *str, int *res);

}

#endif
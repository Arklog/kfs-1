/**
* @example KString.cpp
*/

//! [strlen]

#include "lib/str/KString.hpp"

const char *a = "";
const char *b = "Hello, World!";
const char *c = "abc\0def";

kstring::strlen(a); // 0
kstring::strlen(b); // 13
kstring::strlen(c); // 3

char d[4] = {'t', 'e', 's', 't'};

kstring::strlen(d); // Undefined behavior, d is not null-terminated
kstring::strlen(nullptr); // Undefined behavior, str is not a valid pointer

//![strlen]

//! [strcmp]
#include "lib/str/KString.hpp"

kstring::strcmp("apple", "apple"); // 0
kstring::strcmp("apple", "appled"); // -100
kstring::strcmp("appled", "apple"); // 100

char a[4] = {'a', 'b', 'c', 'd'};
kstring::strcmp(a, "apple"); // Undefined behivior, a is not null-terminated
kstring::strcmp(nullptr, ""); // Undefined behavior, both str1 is not a valid pointer

//! [strcmp]
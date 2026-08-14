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

//! [strncmp]
#include "lib/str/KString.hpp"

kstring::strncmp("banana", "bandana", 3); // 0
kstring::strncmp("banana", "bandana", 4); // -3

char a[4] = {'a', 'b', 'c', 'd'};
char b[4] = {'a', 'b', 'c', 'e'};

kstring::strncmp(a, b, 3); // 0
kstring::strncmp(a, b, 4); // -1

kstring::strncmp(a, b, 5); // Undefined behavior, both a and b are not null-terminated
kstring::strncmp(nullptr, "test", 2); // Undefined behavior, str1 is not a valid pointer

//! [strncmp]

//! [strchr]
#include "lib/str/KString.hpp"

const char *str = "abcabc";

kstring::strchr(str, 'a'); // returns pointer "abcabc"
kstring::strchr(str, 'b'); // returns pointer "bcabc"
kstring::strchr(str, 'c'); // returns pointer "cabc"

const char a[2] = {'a', 'v'};

kstring::strchr(nullptr, 'a'); // Undefined behavior, str is not a valid pointer
kstring::strchr(a, 'c'); // Undefined behavior, a is not null-terminated
//! [strchr]

//! [strrchr]
#include "lib/str/KString.hpp"

const char *str = "abcabc";

kstring::strrchr(str, 'a'); // pointer to "abc"
kstring::strrchr(str, 'b'); // pointer to "bc"
kstring::strrchr(str, 'c'); // pointer to "c"

//! [strrchr]

//! [strstr]
#include "lib/str/KString.hpp"

const char *str = "abcabcd";

kstring::strstr(str, "bc"); // pointer to "bcabcd"
kstring::strstr(str, "bcd"); // pointer to "bcd"
//! [strstr]

//! [strcpy]
#include "lib/str/KString.hpp"

char buff[5];

kstring::strcpy(buff, "test"); // buff == "test"

kstring::strcpy(buff + 1, "test"); // buff + 1 == "test" BUT IS NOT NULL-TERMINATED
kstring::strcpy(buff, "Hello World !"); // Undefined behavior, not enough place in dest
//! [strcpy]


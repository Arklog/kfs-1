******************
General Guidelines
******************

Code Style
==========


Case Style
----------

This is the current coding style, there is **not yet a .clang-format file** however we should try to follow those rules.

* **Class Name**: PascalCase
* **Function Name**: snake_case
* **Variable Name**: snake_case
* **Constant**: UPPERCASE


Avoid Indentation
-----------------

If possible we should try to avoid indentation as much as possible in order to improve code readability. We should **not
have more than 3 levels of indent** (function -> loop -> if).

.. code-block:: c++
    :caption: Example
    :linenos:

    // Do not do this
    void not_ok(bool a) {
        if (a) {
            do_something();
        }
    }

    // Do that
    void ok(bool a) {
        if (!a)
            return;

        do_something();
    }

    // That's ok, but another indent level would start to be messy
    void we_dont_have_a_choice(int i) {
        for (int j = 0; j < 100; ++j) {
            if (j == i)
                do_something();
            else
                do_something_else();
        }
    }


Document Your Code
------------------

**Code must be documented**, every function must have a doxygen documentation available and **should provide some
code example** especially if it will be used somewhere else in the code. Documentation must remain clear and free of
doubt for the reader.

.. code-block:: c++
    :caption: Example
    :linenos:

    /**
    * Alphabetical string comparison structure.
    *
    * @code
    * char *a = "a";
    * char *b = "b";
    *
    * string_comparator(a, b); // true
    * string_comparator(b, a); //false
    * @endcode
    */
    struct string_comparator {
        static bool operator() (const char *s1, const char *s2);
    }

    /**
    * Compute the size of the NULL terminated string pointed to by str not accounting for the NULL byte.
    *
    * @return The size of string pointed to by str.
    *
    * @warning:
    *   - str must not be NULL
    *   - str must be NULL-terminated
    *
    * @code
    * char *empty   = "";
    * char *a       = "a";
    * char *aa      = "aa";
    * char not_null_terminated = 'a';
    *
    * strlen(empty); // 0
    * strlen(a); // 1
    * strlen(aa); // 2
    *
    * strlen(NULL); // ERROR: undefined behavior (NULL is NULL)
    * strlen(&not_null_terminated); // ERROR: undefined behavior (not_null_terminated is not NULL-terminated)
    * @endcode
    */
    unsigned int strlen(const char *str);
//
// Created by pierre on 1/13/26.
//

/**
* @example StackVector.cpp
*/

//! [StackVector range constructor]
#include "lib/container/StackVector.hpp"

auto vec1 = container::StackVector<int, 5>{1, 2, 3, 4, 5};
auto vec2 = container::StackVector<int, 5>{vec1.begin(), vec1.end()};

vec1[0] == vec2[0]; // true
vec1[1] == vec2[1]; // true
vec1[2] == vec2[2]; // true
vec1[3] == vec2[3]; // true
vec1[4] == vec2[4]; // true
//! [StackVector range constructor]

//! [StackVector insert]
#include "lib/container/StackVector.hpp"
auto vec = container::StackVector<int, 5>{1, 2, 3};

vec.insert(vec.begin() + 1, 42); // vec is now {1, 42, 2, 3}
vec.insert(vec.end(), 7);      // vec is now {1, 42, 2, 3, 7}
vec.insert(vec.begin(), 0);    // Fails, vec is full
//! [StackVector insert]

//! [StackVector insert range]
#include "lib/container/StackVector.hpp"
auto vec = container::StackVector<int, 5>{1, 2};
auto to_insert = container::StackVector<int, 3>{3, 4, 5};

vec.insert(vec.end(), to_insert.begin(), to_insert.end()); // vec is now {1, 2, 3, 4, 5}
vec.insert(vec.begin(), to_insert.begin(), to_insert.end()); // Fails, vec is full
//! [StackVector insert range]

//! [StackVector push_back]
#include "lib/container/StackVector.hpp"
auto vec = container::StackVector<int, 3>{};

vec.push_back(1); // vec is now {1}
vec.push_back(2); // vec is now {1, 2}
vec.push_back(3); // vec is now {1, 2, 3}
vec.push_back(4); // Fails, vec is full
//! [StackVector push_back]

//! [StackVector emplace_back]
#include "lib/container/StackVector.hpp"
auto vec = container::StackVector<container::pair<int, float>, 2>{};

vec.emplace_back(1, 1.0f); // vec is now {(1, 1.0f)}
vec.emplace_back(2, 2.0f); // vec is now {(1, 1.0f), (2, 2.0f)}
vec.emplace_back(3, 3.0f); // Fails, vec is full
//! [StackVector emplace_back]

//! [StackVector erase]
#include "lib/container/StackVector.hpp"
auto vec = container::StackVector<int, 5>{1, 2, 3};
vec.erase(vec.begin() + 1); // vec is now {1, 3}
vec.erase(vec.begin());     // vec is now {3}
vec.erase(vec.begin() + 5); // Fails, position out of range
//! [StackVector erase]

//! [StackVector erase range]
#include "lib/container/StackVector.hpp"
auto vec = container::StackVector<int, 5>{1, 2, 3, 4, 5};

vec.erase(vec.begin() + 1, vec.begin() + 4); // vec is now {1, 5}
vec.erase(vec.begin(), vec.end());             // vec is now {}
vec.erase(vec.begin(), vec.begin() + 1); // Fails, range out of range
//! [StackVector erase range]
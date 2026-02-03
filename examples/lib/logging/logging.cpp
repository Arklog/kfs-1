//
// Created by pierre on 2/2/26.
//

/**
* @example logging.cpp
*/

//![logging printk]
#include "lib/logging/logging.hpp"

auto v = logging::printk(logging::DEBUG, "{} {}", 0, 1); // will display: [DEBUG]: 0 1
v == 12; //true
//![logging printk]

//![logging debug]
auto v = logging::debug("Hello world !"); // will display: [DEBUG]: Hello world !
v == 22; //true
//![logging debug]

//![logging info]
auto v = logging::info("info message {} {}", 3, "test"); // will display [INFO ]: info message 3 test
v == 28; //true
//![logging info]

//![logging warn]
auto v = logging::warn("warning message {} {}", 3, "test"); // will display [WARN ]: warning message 3 test
v == 31; //true
//![logging warn]

//![logging error]
auto v = logging::error("error message {} {}", 3, "test"); // will display [ERROR]: error message 3 test
v == 29; //true
//![logging error]

//
// Created by pierre on 12/23/25.
//

#ifndef TESTS_LIB_LOG_HPP
#define TESTS_LIB_LOG_HPP
#include <ostream>

#include "arch/i386/vga/VGAStreamModifier.hpp"

std::ostream &operator<<(std::ostream &stream, const vga::modifier::VGAStreamColorModifier &mod);

#endif //TESTS_LIB_LOG_HPP

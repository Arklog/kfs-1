//
// Created by pierre on 12/23/25.
//
#include <fstream>

#include "logging.hpp"
#include "lib/logging/logging.hpp"
#include "catch2/catch_all.hpp"


TEST_CASE("kprint", "[log]") {
    std::ofstream output("kprint.txt", std::ofstream::out);
    std::ifstream input("kprint.txt", std::ifstream::in);

    logging::set_logger(output);
}

std::ostream &operator<<(std::ostream &stream, const vga::modifier::VGAStreamColorModifier &mod) {
    return stream;
}

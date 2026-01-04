//
// Created by pierre on 12/23/25.
//
#include <fstream>

#include "lib/logging/logging.hpp"
#include "catch2/catch_all.hpp"


TEST_CASE("kprint", "[log]") {
    logging::t_logger output("kprint.txt", std::ofstream::out | std::ofstream::trunc);
    const std::string expected{
            "[DEBUG]: \n"
            "[INFO ]: \n"
            "[WARN ]: \n"
            "[ERROR]: \n"
    };

    logging::set_logger(output);
    logging::printk(logging::DEBUG, "");
    logging::printk(logging::INFO, "");
    logging::printk(logging::WARN, "");
    logging::printk(logging::ERROR, "");
    output.close();

    std::ifstream     input("kprint.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    REQUIRE(buffer.str() == expected);
}

TEST_CASE("debug", "[log]") {
    logging::t_logger output("debug.txt", std::ofstream::out | std::ofstream::trunc);
    const std::string expected{
            "[DEBUG]: 1 2 3 test\n"
    };

    logging::set_logger(output);
    logging::debug("{} {} {} test", 1, 2, 3);
    output.close();

    std::ifstream     input("debug.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    REQUIRE(buffer.str() == expected);
}

TEST_CASE("info", "[log]") {
    logging::t_logger output("info.txt", std::ofstream::out | std::ofstream::trunc);
    const std::string expected{
            "[INFO ]: test 12\n"
    };

    logging::set_logger(output);
    logging::info("{} {}", "test", 12);
    output.close();

    std::ifstream     input("info.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    REQUIRE(buffer.str() == expected);
}

TEST_CASE("warn", "[log]") {
    logging::t_logger output("warn.txt", std::ofstream::out | std::ofstream::trunc);
    const std::string expected{
            "[WARN ]: test 12\n"
    };
    logging::set_logger(output);
    logging::warn("{} {}", "test", 12);
    output.close();

    std::ifstream     input("warn.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    REQUIRE(buffer.str() == expected);
}

TEST_CASE("error", "[log]") {
    logging::t_logger output("error.txt", std::ofstream::out | std::ofstream::trunc);
    const std::string expected{
            "[ERROR]: test 12\n"
    };
    logging::set_logger(output);
    logging::error("{} {}", "test", 12);
    output.close();

    std::ifstream     input("error.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    REQUIRE(buffer.str() == expected);
}
